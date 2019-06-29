import matplotlib.pyplot as plt
import csv
import numpy as np
import matplotlib.mlab as mlb
with open('D:\data.csv') as f:
    data = csv.reader(f,delimiter=',')
    y=next(data)
for i in range(len(y)):
    y[i]=int(y[i])
myarray = np.asarray(y)
plt.psd(myarray, Fs=992, detrend=mlb.detrend_mean) 
plt.show()
