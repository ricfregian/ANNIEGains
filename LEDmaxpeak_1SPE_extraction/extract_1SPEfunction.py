import json
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np
import scipy
##import scipy.integrate as integrate
import scipy.integrate
##from numpy import exp

sns.set_context('poster')
sns.set(font_scale=1.4)


with open("LEDmaxpeak_2runs/LEDmaxpeak_2runs_combined.json","r") as f:
    dat = json.load(f)
pdf = pd.DataFrame(dat["EXP2SPE"])
print(dat["EXP2SPE"].keys())


#with open("../../gains_json_files/Ambe_gains/AmBe_gains_src_Gauss1_10hits_3pC_fitrng.json","r") as f:
with open("../../gains_json_files/LEDthr_gains/LEDthr_gains_Gauss1_fitrng_5Runs.json","r") as f:
    dat = json.load(f)
pdf_AmBe = pd.DataFrame(dat["Gauss1"])
print(dat["Gauss1"].keys())

off_list_database=[333,346,349,352,431,444]
nogains_list = [343,337,342,345,359,416,445]

fig1, ax1 = plt.subplots()
#TUBES = np.arange(332,464,1)
#TUBES = np.arange(332,336,1)
#TUBES = [335]
ETEL_list = [350,351,353,354,355,356,357,358,359,360,361,362,363,364,365,366,367,368,369,370,371,372,373,374,375]
ETEL_list = np.setdiff1d(ETEL_list,off_list_database)
ETEL_list = np.setdiff1d(ETEL_list,nogains_list)
#ETEL_list = [350]
for cnum in ETEL_list:
        if ((cnum not in list(pdf["Channel"]))):
            print("DID NOT FIND CHANNELNUM %i "%(cnum) )
            continue
        #print("Integrating CHANNELNUM %i "%(cnum))
        m1 = pdf.loc[((pdf["Channel"] == cnum)), "c1Mu"].values
        C1 = pdf.loc[((pdf["Channel"] == cnum)), "c1Height"].values
        s1 = pdf.loc[((pdf["Channel"] == cnum)), "c1Sigma"].values 
        m1_AmBe = pdf_AmBe.loc[((pdf["Channel"] == cnum)), "c1Mu"].values
        C1_AmBe = pdf_AmBe.loc[((pdf["Channel"] == cnum)), "c1Height"].values
        s1_AmBe = pdf_AmBe.loc[((pdf["Channel"] == cnum)), "c1Sigma"].values 
        #print("m1_AmBe")
        #print(str(m1_AmBe))
        #print("m1")
        #print(str(m1))
        x = np.linspace(0,0.006,200)
       	gauss1= lambda x: C1*np.exp(-(1./2.)*((x-m1)**2)/s1**2)
       	gauss1_AmBe= lambda x: C1_AmBe*np.exp(-(1./2.)*((x-m1_AmBe)**2)/s1_AmBe**2)
        #i = scipy.integrate.quad(gauss1, 0.004127197265625, np.inf)
        area = scipy.integrate.quad(gauss1, -np.inf, np.inf)
        area_AmBe = scipy.integrate.quad(gauss1_AmBe, -np.inf, np.inf)
        y  = [gauss1(val) for val in x]	
        y_AmBe  = [gauss1_AmBe(val_AmBe) for val_AmBe in x]	
        plt.plot(x,y,"r")
        plt.plot(x,y_AmBe,"b")
        plt.savefig('fits_%i.png'%(cnum))
        plt.show()
        #plt.savefig('fits_%i.png'%cnum)
        #print("Integrattion = " )
        #print(i[0])
        #print(j[0])
        
	#plt.plot(gauss1)
        #ax1.errorbar(cnum,i[0]/j[0],alpha=1.0,label="%i Data"%cnum,linestyle='None',marker='o',markersize=8)

#plt.close()
#plt.axline((0.0002, 0.0002), slope=1.0, color="black", linestyle=(0, (5, 5)))

#plt.xlabel("Channel")
#plt.ylabel("SPE Efficiency")
#plt.title("")
#plt.show()
