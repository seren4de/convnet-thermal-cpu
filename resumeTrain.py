import argparse
import os
from datetime import datetime

import torch
import torchvision.transforms as transforms
from Dataset import cpuDataset, AttributesDataset, mean, std
from Model import SingleOutputModel
from Test import visualize_grid
from Helpers import calculate_metrics,validate,checkpoint_load
from torch.utils.data import DataLoader
from torch.utils.tensorboard import SummaryWriter


def get_cur_time():
    return datetime.strftime(datetime.now(), '%Y-%m-%d_%H-%M')


def checkpoint_save(model, name, epoch):
    f = os.path.join(name, 'checkpoint-{:06d}.pth'.format(epoch))
    torch.save(model.state_dict(), f)
    print('Saved checkpoint:', f)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Training pipeline')
    parser.add_argument('--attributes_file', type=str, default='./data.csv',
                        help="Path to the file with attributes")
    parser.add_argument('--device', type=str, default='cuda', help="Device: 'cuda' or 'cpu'")
    parser.add_argument('--resume_from_checkpoint', type=str, default=None,
                        help="Path to the checkpoint you want to load")
    args = parser.parse_args()

    #change start_epoch , set it number of loaded epochs+1
    start_epoch = 101
    N_epochs = 150
    batch_size = 16
    num_workers = 12  # number of processes to handle dataset loading
    device = torch.device("cuda" if torch.cuda.is_available() and args.device == 'cuda' else "cpu")

    # attributes variable contains labels for the categories in the dataset and mapping between string names and IDs
    attributes = AttributesDataset(args.attributes_file)

    # specify image transforms for augmentation during training
    train_transform = transforms.Compose([
        transforms.RandomHorizontalFlip(p=0.5),
        transforms.ColorJitter(brightness=0.3, contrast=0.3, saturation=0.3, hue=0),
        transforms.RandomAffine(degrees=20, translate=(0.1, 0.1), scale=(0.8, 1.2),
                                shear=None, resample=False, fillcolor=(255, 255, 255)),
        transforms.ToTensor(),
        transforms.Normalize(mean, std)
    ])

    # during validation we use only tensor and normalization transforms
    val_transform = transforms.Compose([
        transforms.ToTensor(),
        transforms.Normalize(mean, std)
    ])

    train_dataset = cpuDataset('./train.csv', attributes, train_transform)
    train_dataloader = DataLoader(train_dataset, batch_size=batch_size, shuffle=True, num_workers=num_workers)

    val_dataset = cpuDataset('./val.csv', attributes, val_transform)
    val_dataloader = DataLoader(val_dataset, batch_size=batch_size, shuffle=False, num_workers=num_workers)

    model = SingleOutputModel(n_cpu_classes=attributes.num_cpuAct).to(device)

    optimizer = torch.optim.Adam(model.parameters())

    logdir = os.path.join('./logs/', get_cur_time())
    savedir = os.path.join('./checkpoints/', get_cur_time())
    os.makedirs(logdir, exist_ok=True)
    os.makedirs(savedir, exist_ok=True)
    logger = SummaryWriter(logdir)

    n_train_samples = len(train_dataloader)

    # Uncomment rows below to see example images with ground truth labels in val dataset and all the labels:
    # visualize_grid(model, val_dataloader, attributes, device, show_cn_matrices=False, show_images=True,
    #                checkpoint=None, show_gt=True)
  
    checkpoint_load(model,args.resume_from_checkpoint)

    print("Continuing training ...")

    for epoch in range(start_epoch, N_epochs + 1):
        total_loss = 0
        accuracy_cpuAct = 0


        for batch in train_dataloader:
            optimizer.zero_grad()

            img = batch['img']
            target_labels = batch['labels']
            target_labels = {t: target_labels[t].to(device) for t in target_labels}
            output = model(img.to(device))

            loss_train, losses_train = model.get_loss(output, target_labels)
            total_loss += loss_train.item()
            batch_accuracy_cpuAct = calculate_metrics(output, target_labels)

            accuracy_cpuAct += batch_accuracy_cpuAct


            loss_train.backward()
            optimizer.step()

        print("epoch {:4d}, loss: {:.4f}, cpuAct: {:.4f}".format(
            epoch,
            total_loss / n_train_samples,
            accuracy_cpuAct / n_train_samples))

        logger.add_scalar('train_loss', total_loss / n_train_samples, epoch)

        if epoch % 5 == 0:
            validate(model, val_dataloader,device, logger, epoch)

        if epoch % 25 == 0:
            checkpoint_save(model, savedir, epoch)