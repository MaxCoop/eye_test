#!/usr/bin/python

import sys
import matplotlib.pyplot as plt
from scipy.signal import savgol_filter 


datafile = sys.argv[1]
data = [[], [], [], []]
ifile=open(datafile, 'rU')
for line in ifile.readlines():
    #format is:
    '''
    Frame 6
    MedianBlur OFF : NOBP = 6625
    MedianBlur ON : NOBP = 5971
    Time :378620

    Frame 7
    MedianBlur OFF : NOBP = 6061
    MedianBlur ON : NOBP = 5409
    Time :389131
    '''
    line=line.strip()
    if 'Frame' in line:
        line=line.split(' ')
        data[0].append(line[-1])
    elif 'MedianBlur OFF' in line:
        line=line.split('=')
        data[1].append(line[-1])
    elif 'MedianBlur ON' in line:
        line=line.split('=')
        data[2].append(line[-1])
    elif 'Time' in line:
        line=line.split(':')
        data[3].append(line[-1])

m = max([float(i) for i in data[1]])
if max([float(i) for i in data[2]]) > m:
    m=max([float(i) for i in data[2]])
    

plt.figure(1, figsize=(12,6))
plt.title(datafile)
plt.plot(data[0],data[1], 'r.-', label='No Median Blur')
plt.plot(data[0],data[2], 'b.-', label='Median Blur: '+datafile.split('_')[3][-2:])
#print(data)
plt.ylim(0, m)
plt.ylabel('Number of Black Pixels')
plt.xlabel('Frame',fontsize=15)
plt.legend(loc='best')
plt.savefig(datafile+'_plot_frames.png')

plt.figure(2, figsize=(12,6))
plt.title(datafile)
plt.plot([float(i)/1000000 for i in data[3]],data[1], 'r.-', label='No Median Blur')
plt.plot([float(i)/1000000 for i in data[3]],data[2], 'b.-', label='Median Blur: '+datafile.split('_')[3][-2:])

#we filter a filter using a Savitzky-Golay filter for non-periodic signals
#using a polynomial regression over a small window of data [5 datapoint to order 1 polynomial]
plt.plot([float(i)/1000000 for i in data[3]], savgol_filter(data[1], 5 , 1),'r--', label='No Blur filtered')
plt.plot([float(i)/1000000 for i in data[3]], savgol_filter(data[2], 5 , 1),'b--', label='Blur filtered')

#print(data)
plt.ylim(0, m)
plt.ylabel('Number of Black Pixels')
plt.xlabel('Time / s',fontsize=15)
plt.legend(loc='best')
plt.savefig(datafile+'_plot_time.png')

print('Average Frame Processing time: '+str(float(data[3][-1])/(len(data[3])*1000000)))+' s/frame'
print('Average FPS: '+str(1000000*(float(data[0][-1])/float(data[3][-1]))))

#print('Range No Median Blur: '+str(max(data[1])-min(data[1])))
#print('Range with Median Blur: '+str(max(data[2])-min(data[2])))





    
