import numpy as np
import scipy as sp
import scipy.optimize as scp
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
import glob
import json

FILEPATH = "combined_all.json"
CHANSTOREMOVE = [341, 383, 355, 394, 420]

if __name__=='__main__':
    with open(FILEPATH,"r") as f:
        dat = json.load(f)
    df = pd.DataFrame(dat)
    for chan in CHANSTOREMOVE:
        todrop = df[df['Channel'] == chan].index
        df.drop(todrop, inplace=True)
    
    with open("combined_all_readytobeadded.json","w") as f:
        json.dump(df.to_dict('list'),f,indent=4)
