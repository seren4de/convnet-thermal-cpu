import pandas as pd
import os
import torch

device = ("cuda" if torch.cuda.is_available() else "cpu")
print(device)

train_df = pd.DataFrame(columns=["img_name","cpuAct"])
train_df["img_name"] = os.listdir("./in_data/")
for idx, i in enumerate(os.listdir("./in_data/")):
    if "AES" in i:
        train_df["cpuAct"][idx] = "AES_encrypt"
    if "AR" in i:
        train_df["cpuAct"][idx] = "Analog_Read"
    if "AW" in i:
        train_df["cpuAct"][idx] = "Analog_Write"
    if "BF" in i:
        train_df["cpuAct"][idx] = "Brute_Force"
    if "Delay" in i:
        train_df["cpuAct"][idx] = "Delay"
    if "RSA" in i:
        train_df["cpuAct"][idx] = "RSA_encrypt"
    if "SR" in i:
        train_df["cpuAct"][idx] = "Serial_Read"
    if "SW" in i:
        train_df["cpuAct"][idx] = "Serial_Write"
    if "SM" in i:
        train_df["cpuAct"][idx] = "Sleep_Mode"
    if "SBM" in i:
        train_df["cpuAct"][idx] ="Stand_By_Mode"
    if "WL" in i:
        train_df["cpuAct"][idx] = "Word_List"
    
    

train_df.to_csv (r'data.csv', index = False, header=True)
