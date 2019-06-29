import csv
import matplotlib.pyplot as plt
with open('D:\data.csv') as f:
    data = csv.reader(f,delimiter=',')
    y=next(data)
    for i in range(len(y)):
        y[i]=(int(y[i])*5)/1024
    x=[0]
    z=0
for i in range(499):
    z+=1.008
    x.append(z)

plt.plot(x,y)
plt.xlabel(' time (ms) ')
plt.ylabel(' voltage (V) ')
plt.title(' Voltage vs time graph ')
plt.show()
