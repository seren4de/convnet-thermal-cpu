import warnings
from sklearn.metrics import confusion_matrix, ConfusionMatrixDisplay, accuracy_score
import matplotlib.pyplot as plt
import torch
import os

def calculate_metrics(output, target):
    _, predicted_cpuAct = output['cpuAct'].cpu().max(1)
    gt_cpuAct = target['cpu_act_labels'].cpu()

    with warnings.catch_warnings():  # sklearn may produce a warning when processing zero row in confusion matrix
        warnings.simplefilter("ignore")
        accuracy_cpuAct = accuracy_score(y_true=gt_cpuAct.numpy(), y_pred=predicted_cpuAct.numpy())
        
    return accuracy_cpuAct


def visualize_gt_data(dataset, attributes):
    imgs = []
    gt_labels = []

    n_cols = 5
    n_rows = 3

    # store the original transforms from the dataset
    transforms = dataset.transform
    # and not use them during visualization
    dataset.transform = None

    for img_idx in range(n_cols * n_rows):
        sample = dataset[img_idx]
        img = sample['img']
        labels = sample['labels']
        gt_cpuAct = attributes.color_id_to_name[labels['cpu_act_labels']]
     
        imgs.append(img)
        gt_labels.append("{}".format(gt_cpuAct))

    title = "Ground truth labels"

    fig, axs = plt.subplots(n_rows, n_cols, figsize=(10, 10))
    axs = axs.flatten()
    for img, ax, label in zip(imgs, axs, gt_labels):
        ax.set_xlabel(label, rotation=0)
        ax.get_xaxis().set_ticks([])
        ax.get_yaxis().set_ticks([])
        ax.imshow(img)
    plt.suptitle(title)
    plt.tight_layout()
    plt.show()

    # restore original transforms
    dataset.transform = transforms


def checkpoint_load(model, name):
    print('Restoring checkpoint: {}'.format(name))
    model.load_state_dict(torch.load(name, map_location='cpu'))
    epoch = int(os.path.splitext(os.path.basename(name))[0].split('-')[1])
    return epoch


def net_output_to_predictions(output):
    _, predicted_cpuAct = output['cpuAct'].cpu().max(1)

    return predicted_cpuAct.numpy().tolist()


def validate(model, dataloader, device, logger=None, epoch=None, checkpoint=None):
    if checkpoint is not None:
        checkpoint_load(model, checkpoint)

    model.eval()
    cpuAct_predictions = []

    with torch.no_grad():
        avg_loss = 0
        accuracy_cpuAct = 0

        for batch in dataloader:
            img = batch['img']
            target_labels = batch['labels']
            target_labels = {t: target_labels[t].to(device) for t in target_labels}
            output = model(img.to(device))

            val_train, val_train_losses = model.get_loss(output, target_labels)
            avg_loss += val_train.item()
            batch_accuracy_cpuAct = \
                calculate_metrics(output, target_labels)

            accuracy_cpuAct += batch_accuracy_cpuAct
     

            batch_cpuAct_predictions = net_output_to_predictions(output)

            cpuAct_predictions.extend(batch_cpuAct_predictions)
         

    n_samples = len(dataloader)
    avg_loss /= n_samples
    accuracy_cpuAct /= n_samples
 
    print('-' * 72)
    print("Validation  loss: {:.4f}, cpuAct: {:.4f}\n".format(
        avg_loss, accuracy_cpuAct))

    if logger is not None and epoch is not None:
        logger.add_scalar("val_loss", avg_loss, epoch)
        logger.add_scalar("val_accuracy/cpuAct", accuracy_cpuAct, epoch)
        
    model.train()

    return cpuAct_predictions