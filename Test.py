import argparse
import os
import warnings

import matplotlib.pyplot as plt
import numpy as np
import torch
import torchvision.transforms as transforms
from Dataset import cpuDataset, AttributesDataset, mean, std
from Model import SingleOutputModel
from Helpers import checkpoint_load,calculate_metrics
from sklearn.metrics import confusion_matrix, ConfusionMatrixDisplay, balanced_accuracy_score
from torch.utils.data import DataLoader




def visualize_grid(model, dataloader, attributes, device, show_cn_matrices=True, show_images=True, checkpoint=None,
                   show_gt=False):
    if checkpoint is not None:
        checkpoint_load(model, checkpoint)
    model.eval()

    imgs = []
    labels = []
    gt_labels = []
    gt_cpuAct_all = []
    predicted_cpuAct_all = []
  
    accuracy_cpuAct = 0


    with torch.no_grad():
        for batch in dataloader:
            img = batch['img']
            gt_cpuAct = batch['labels']['cpu_act_labels']

            output = model(img.to(device))

            batch_accuracy_cpuAct = calculate_metrics(output, batch['labels'])

            accuracy_cpuAct += batch_accuracy_cpuAct


            # get the most confident prediction for each image
            _, predicted_cpuAct = output['cpuAct'].cpu().max(1)

            #print(predicted_cpuAct[0])

            #print(img.shape[0])

            #print(attributes.cpuAct_id_to_name[predicted_cpuAct.numpy()[0]])
            #print(gt_cpuAct)

            numpy_pr = predicted_cpuAct.numpy()
            numpy_prr = gt_cpuAct.numpy()


            for i in range(img.shape[0]):

                image = np.clip(img[i].permute(1, 2, 0).numpy() * std + mean, 0, 1)

                #print(type(numpy_pr[i]))
                #print(attributes.cpuAct_id_to_name[numpy_prr[i]])

                predicted_cpuAct = attributes.cpuAct_id_to_name[numpy_pr[i]]

                gt_cpuAct = attributes.cpuAct_id_to_name[numpy_prr[i]]


                gt_cpuAct_all.append(gt_cpuAct)

                predicted_cpuAct_all.append(predicted_cpuAct)
 
                imgs.append(image)
                labels.append("{}\n".format(predicted_cpuAct))
                gt_labels.append("{}\n".format(gt_cpuAct))
            
    if not show_gt:
        n_samples = len(dataloader)
        print("\nAccuracy:\ncpuAct: {:.4f}".format(accuracy_cpuAct / n_samples))

    # Draw confusion matrices
    if show_cn_matrices:
        # cpuAct
        cn_matrix = confusion_matrix(
            y_true=gt_cpuAct_all,
            y_pred=predicted_cpuAct_all,
            labels=attributes.cpu_act_labels,
            normalize='true')

        ConfusionMatrixDisplay(cn_matrix).plot(
            include_values=True, xticks_rotation='vertical')
        plt.title("cpuAct")

        plt.tight_layout()
        #plt.show()

        # Uncomment code below to see the article confusion matrix (it may be too big to display)
        plt.rcParams.update({'font.size': 1.8})
        plt.rcParams.update({'figure.dpi': 300})
        plt.rcParams.update({'figure.dpi': 100})
        plt.rcParams.update({'font.size': 5})
        plt.show()

    if show_images:
        labels = gt_labels if show_gt else labels
        title = "Ground truth labels" if show_gt else "Predicted labels"
        n_cols = 10
        n_rows = 10
        fig, axs = plt.subplots(n_rows, n_cols, figsize=(10, 10))
        axs = axs.flatten()
        for img, ax, label in zip(imgs, axs, labels):
            ax.set_xlabel(label, rotation=0)
            ax.get_xaxis().set_ticks([])
            ax.get_yaxis().set_ticks([])
            ax.imshow(img)
        plt.suptitle(title)
        plt.tight_layout()
        plt.show()

    model.train()




if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Inference pipeline')
    parser.add_argument('--checkpoint', type=str, required=True, help="Path to the checkpoint")
    parser.add_argument('--attributes_file', type=str, default='./data.csv',
                        help="Path to the file with attributes")
    parser.add_argument('--device', type=str, default='cuda',
                        help="Device: 'cuda' or 'cpu'")
    args = parser.parse_args()

    device = torch.device("cuda" if torch.cuda.is_available() and args.device == 'cuda' else "cpu")
    # attributes variable contains labels for the categories in the dataset and mapping between string names and IDs
    attributes = AttributesDataset(args.attributes_file)

    # during validation we use only tensor and normalization transforms
    val_transform = transforms.Compose([
        transforms.ToTensor(),
        transforms.Normalize(mean, std)
    ])

    test_dataset = cpuDataset('./Val.csv', attributes, val_transform)
    test_dataloader = DataLoader(test_dataset, batch_size=64, shuffle=False, num_workers=12)

    model = SingleOutputModel(n_cpu_classes=attributes.num_cpuAct).to(device)

    # Visualization of the trained model
    visualize_grid(model, test_dataloader, attributes, device, checkpoint=args.checkpoint)