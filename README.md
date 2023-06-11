# convnet-thermal-cpu

This is a CNN model that classifies between 11 different CPU activities: AES and RSA encryptions, analog and serial writes, analog and serial reads, brute force, Standby mode, Sleep mode, delay, and Wordlist generation.

## Creating a CSV file with images and corresponding labels

To create a CSV file with images and corresponding labels, first run the following command (don't forget to change the path to the directory with `in_data`):

```sh
$ python PrepareCSV.py
```

### Creating two CSV files mapping paths for images and their labels

To create two CSV files mapping paths for images and their labels, run the following command:

```sh
$ python Splitdata.py --input [path to your saved data.csv] --output [path to where you want to save Train.csv/Val.csv files]
```

If you create a new `data.csv`, resolve slicing depending on how many items you have in the dataset and what proportions you want to use for training and validation.

## Training

To train the model, run the following command:

```sh
$ python Train.py
```

You can change the default paths to CSV files inside the script. The location by default is the home directory for the project.

## Testing

To test the model, run the following command:

```sh
$ python Test.py --checkpoint [path to checkpoint you want to test with]
```

The default directory for checkpoints is `./checkpoints/`.

## Resuming training from a checkpoint

To resume training from a checkpoint `n` (number of epochs), run the following command:

```sh
$ python resumeTrain.py --resume_from_checkpoint [path to checkpoint]
```

Don't forget to set the `start_epoch` variable to `n+1`.

## Visualizing logs

To visualize logs, run the following command:

```sh
$ tensorboard --logdir=./logs/
```

`./logs/` is the default directory for logs.
