#!/usr/bin/python

import sys, math
import matplotlib.pyplot as plt
from scipy.signal import savgol_filter 


datafile = sys.argv[1]
data = [[], [], [], []]
ifile=open(datafile, 'rU')
for line in ifile.readlines():
    #format is:
    '''
    Frame 6
    #MedianBlur OFF : NOBP = 6625
    #MedianBlur ON : NOBP = 5971
    Black
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
    #elif 'MedianBlur OFF' in line:
#        line=line.split('=')
#        data[1].append(line[-1])
#    elif 'MedianBlur ON' in line:
#        line=line.split('=')
#        data[2].append(line[-1])
    elif 'Black' in line:
        line=line.split('=')
        data[2].append(line[-1])
    elif 'Time' in line:
        line=line.split(':')
        data[3].append(line[-1])

m = max([float(i) for i in data[2]])
#if max([float(i) for i in data[2]]) > m:
#    m=max([float(i) for i in data[2]])
    
'''
plt.figure(1, figsize=(12,6))
plt.title(datafile)
#plt.plot(data[0],data[1], 'r.-', label='No Median Blur')
plt.plot(data[0],data[2], 'b.-', label='Median Blur: '+datafile.split('_')[3][-2:])
#print(data)
plt.ylim(0, m)
plt.ylabel('Number of Black Pixels')
plt.xlabel('Frame',fontsize=15)
plt.legend(loc='best')
plt.savefig(datafile+'_plot_frames.png')
'''
plt.figure(2, figsize=(12,6))
plt.title(datafile)
#plt.plot([float(i)/1000000 for i in data[3]],data[1], 'ro-', label='No Median Blur')
plt.plot([float(i)/1000000 for i in data[3]],data[2], 'bo-', label='Median Blur: '+datafile.split('_')[3][-2:])

#we filter a filter using a Savitzky-Golay filter for non-periodic signals
#using a polynomial regression over a small window of data [5 datapoint to order 1 polynomial]
#avg_no_blur = savgol_filter(data[1], 5 , 1)
avg_blur = savgol_filter(data[2], 5 , 1)

#plt.plot([float(i)/1000000 for i in data[3]], avg_no_blur,'r.--', label='No Blur filtered')
plt.plot([float(i)/1000000 for i in data[3]], avg_blur,'b.--', label='Blur filtered')

#var_no_blur = []
var_blur = []

#calculating variation measurement
for i in range(len(data[2])):
    #print(data[1][i]) #data
    #print((float(data[1][i]) - float(avg_no_blur[i]))) #displacement
    #dp = (float(data[1][i]) - float(avg_no_blur[i]))**2
    dp1 = (float(data[2][i]) - float(avg_blur[i]))**2

    #print(dp) #displacement squared
    #var_no_blur.append(dp)
    var_blur.append(dp1)

#var_noblur = math.sqrt(sum(var_no_blur)/(len(var_no_blur)-1))#calculate sqrt of sample variance (s^2)
var_blur = math.sqrt(sum(var_blur)/(len(var_blur)-1))#calculate sqrt of sample variance (s^2)

av_f_p_t = 'Average Frame Processing time: '+str(round(float(data[3][-1])/(len(data[3])*1000000),2))+' s/frame'
av_fps = 'Average FPS: '+str(round(1000000*(float(data[0][-1])/float(data[3][-1])),2))
ttl_t = 'Total time: '+str(round(float(data[3][-1])/1000000,2))+' s'
#nb_variance = 'No Blur Variance: '+str(round(var_noblur,2))
b_variance = 'Blur Variance: '+str(round(var_blur,2))

#print(av_f_p_t)
#print(av_fps)
#print(ttl_t)
#print(variance)
      
plt.text(0.45*float(data[3][-1])/1000000,0.1*int(max(data[2])),av_f_p_t, fontsize=15)
plt.text(0.45*float(data[3][-1])/1000000,0.2*int(max(data[2])),av_fps, fontsize=15)
plt.text(0.45*float(data[3][-1])/1000000,0.3*int(max(data[2])),ttl_t, fontsize=15)
#plt.text(0.45*float(data[3][-1])/1000000,0.4*int(max(data[2])),nb_variance, fontsize=15)
plt.text(0.45*float(data[3][-1])/1000000,0.4*int(max(data[2])),b_variance, fontsize=15)


#print(data)
plt.ylim(0, m)
plt.ylabel('Number of Black Pixels')
plt.xlabel('Time / s',fontsize=15)
plt.legend(loc='best')
plt.savefig(datafile+'_plot_time.png')







    
