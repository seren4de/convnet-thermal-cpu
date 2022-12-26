# convnet-thermal-cpu

CNN model that cassifyes between 11 different CPU activities; AES and RSA encryptions - analog and serial writes - analog and serial reads - brute force - Standby mode - Sleep mode - delay - Wordlist generation.

### to create a CSV file with images and corresponding labels 
(don't forget to change path to the directory with in_data)
First run $ python PrepareCSV.py 


### to create two CSV files mapping paths for images and their labels
second run $ python Splitdata.py --input "path to you saved data.csv"  --output "path to where you want to save Train.csv /Val,csv files"
### if you create a new data.csv, resolv slicing depending on how much items you in the dataset and what proportions you want to use for train and validation


## for training 
run $ python Train.py 
## you can change the default paths to csv files inside the script location by default is the home directory for the project


## for testing 
run $ python Xtest.py --checkpoint "path to checkpoint you to test with"
## default dir for checkpoints is ./checkpoints/


## to resume training from a checkpoint n (number of epochs)
run $ python resumeTrain,py --resume_from_checkpoint "path to checkpoint"
## don't forget to set start_epoch variable to n+1


## to visualize logs
run $ tensorboard --logdir=./logs/ 

./logs/ is the default dir for logs 
