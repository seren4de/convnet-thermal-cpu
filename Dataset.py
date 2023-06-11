import csv

import numpy as np
from PIL import Image
from torch.utils.data import Dataset

mean = [0.485, 0.456, 0.406]
std = [0.229, 0.224, 0.225]


class AttributesDataset():
    def __init__(self, annotation_path):
        cpu_act_labels = []

        with open(annotation_path) as f:
            reader = csv.DictReader(f)
            for row in reader:
                cpu_act_labels.append(row['cpuAct'])

        self.cpu_act_labels = np.unique(cpu_act_labels)
    
        self.num_cpuAct = len(self.cpu_act_labels)

        self.cpuAct_id_to_name = dict(zip(range(len(self.cpu_act_labels)), self.cpu_act_labels))
        self.cpuAct_name_to_id = dict(zip(self.cpu_act_labels, range(len(self.cpu_act_labels))))


class cpuDataset(Dataset):
    def __init__(self, annotation_path, attributes, transform=None):
        super().__init__()

        self.transform = transform
        self.attr = attributes

        # initialize the arrays to store the ground truth labels and paths to the images
        self.data = []
        self.cpu_act_labels = []

        # read the annotations from the CSV file
        with open(annotation_path) as f:
            reader = csv.DictReader(f)
            for row in reader:
                self.data.append(row['image_path'])
                self.cpu_act_labels.append(self.attr.cpuAct_name_to_id[row['cpuAct']])
              
    def __len__(self):
        return len(self.data)

    def __getitem__(self, idx):
        # take the data sample by its index
        img_path = self.data[idx]

        # read image
        img = Image.open(img_path)

        # apply the image augmentations if needed
        if self.transform:
            img = self.transform(img)

        # return the image and all the associated labels
        dict_data = {
            'img': img,
            'labels': {
                'cpu_act_labels': self.cpu_act_labels[idx],
            }
        }
        return dict_data
