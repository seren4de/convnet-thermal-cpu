import argparse
import csv
import os

import numpy as np
from PIL import Image
from tqdm import tqdm


def save_csv(data, path, fieldnames=['image_path', 'cpuAct']):
    with open(path, 'w', newline='') as csv_file:
        writer = csv.DictWriter(csv_file, fieldnames=fieldnames)
        writer.writeheader()
        for row in data:
            writer.writerow(dict(zip(fieldnames, row)))


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Split data for the dataset')
    parser.add_argument('--input', type=str, required=True, help="Path to annotation file")
    parser.add_argument('--output', type=str, required=True, help="Path to the working folder")

    args = parser.parse_args()
    input_folder = args.input
    output_folder = args.output
    annotation = os.path.join(input_folder, 'data.csv')

    # open annotation file
    all_data=[]
    #ll_data = [17611]
    #all_data = np.empty(17611)
    #ll_data=[None]*17611
    with open(annotation) as csv_file:
        # parse it as CSV
        reader = csv.DictReader(csv_file)
        # tqdm shows pretty progress bar
        # each row in the CSV file corresponds to the image
        for row in tqdm(reader, total=reader.line_num):
            # we need image ID to build the path to the image file
            img_id = row['img_name']
            # we're going to use only 3 attributes
            cpuAct = row['cpuAct']
            img_name = os.path.join(input_folder ,"in_data/"+ str(img_id))
            
            # check if file is in place
            #print(img_name)

            if os.path.exists(img_name):
                #print("ok1")
                # check if the image has 80*60 pixels with 3 channels
                img = Image.open(img_name)
                if img.size == (315, 240) or img.size == (320, 240):
                    img1= img.resize((315,234))
                    img1.save(img_name)
                img2 = Image.open(img_name)
                if img2.size == (315, 234):
                    #print("ok")
                    all_data.append([img_name, cpuAct])
    

    # set the seed of the random numbers generator, so we can reproduce the results later
    np.random.seed(42)
    # construct a Numpy array from the list
    all_data = np.asarray(all_data)
    # Take 17611 samples in random order
    inds = np.random.choice(34667, 34667, replace=False)
    # split the data into train/val and save them as csv files
    #print(all_data[1][1])
    #all_data[inds][:14087]
    save_csv(all_data[inds][:27332], os.path.join(output_folder, 'Train.csv'))
    save_csv(all_data[inds][27332:34667], os.path.join(output_folder, 'Val.csv'))
