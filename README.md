# convnet-thermal-cpu

This is a CNN model that classifies between 11 different CPU activities: AES and RSA encryptions, analog and serial writes, analog and serial reads, brute force, Standby mode, Sleep mode, delay, and Wordlist generation.

## Creating a CSV file with images and corresponding labels

To create a CSV file with images and corresponding labels, first run the following command (don't forget to change the path to the directory with `in_data`):
```sh
python initcsv.py
```

### Creating two CSV files mapping paths for images and their labels
To create two CSV files mapping paths for images and their labels, run the following command:
```sh
python spltdata.py --input path/to/in.csv --output path/to/out.csv
```
**Note**: If you are plannign to use a new `data.csv`, you should resolve slicing and choose what proportions you want to use for training and validation.

## Training
train the model with:
```sh
python train.py --attributes_file path/to/data.csv
#python train.py --resume --resume_from_checkpoint path/to/checkpoint.pth
```
**Note** when resuming the training, set the `start_epoch` variable to the past `n+1`.

## Testing
test the model with:
```sh
python Test.py --checkpoint path/to/checkpoint
```

## Visualizing logs
visualize logs with:
```sh
tensorboard --logdir=./logs/
```
