#!/usr/bin/python

import sys, math, os
import matplotlib.pyplot as plt
from scipy.signal import savgol_filter 


datadirectory = sys.argv[1]

home = '/Users/kaiwhata/Git/eye_test/Data/'
contents=os.listdir(home+datadirectory)
ms = []

for datafile in contents:
    if datafile[-4:] == '.txt':
        data = [[], [], [], []]
        ifile=open(datafile, 'rU')
        for line in ifile.readlines():
            #format is:
            '''
            Frame 6
            Black : 34698
            Time :378620

            Frame 7
            Black : 89746
            Time :389131
            '''
            line=line.strip()
            if 'Frame' in line:
                line=line.split(' ')
                data[0].append(line[-1])
            elif 'Black' in line:
                line=line.split('=')
                data[2].append(line[-1])
            elif 'Time' in line:
                line=line.split(':')
                data[3].append(line[-1])

        m = max([float(i) for i in data[2]])
        ms.append(m)

        plt.figure(1, figsize=(12,6))
        plt.title(datadirectory)

        plt.plot([float(i)/1000000 for i in data[3]],[float(j) for j in data[2]], label=datafile.split('_')[0]+' '+datafile.split('_')[1][:-15], marker='o') # 'bo-',
        #normalised
        #plt.plot([float(i)/1000000 for i in data[3]],[float(j)/m for j in data[2]], label=datafile.split('_')[0]+' '+datafile.split('_')[1][:-15], marker='o') # 'bo-',

        #we filter a filter using a Savitzky-Golay filter for non-periodic signals
        #using a polynomial regression over a small window of data [5 datapoint to order 1 polynomial]
        avg_blur = savgol_filter(data[2], 5 , 1)

        #plt.plot([float(i)/1000000 for i in data[3]], [float(j)/m for j in avg_blur],'k.--')

        var_blur = []

        #calculating variation measurement
        for i in range(len(data[1])):
            dp1 = (float(data[2][i]) - float(avg_blur[i]))**2

            #print(dp) #displacement squared
            var_blur.append(dp1)

        var_blur = math.sqrt(sum(var_blur)/(len(var_blur)-1))#calculate sqrt of sample variance (s^2)

        av_f_p_t = 'Average Frame Processing time: '+str(round(float(data[3][-1])/(len(data[3])*1000000),2))+' s/frame'
        av_fps = 'Average FPS: '+str(round(1000000*(float(data[0][-1])/float(data[3][-1])),2))
        ttl_t = 'Total time: '+str(round(float(data[3][-1])/1000000,2))+' s'
        b_variance = 'Blur Variance: '+str(round(var_blur,2))

        #print(av_f_p_t)
        #print(av_fps)
        #print(ttl_t)
        #print(variance)
              
        #plt.text(0.45*float(data[3][-1])/1000000,0.1*int(max(data[2])),av_f_p_t, fontsize=15)
        #plt.text(0.45*float(data[3][-1])/1000000,0.2*int(max(data[2])),av_fps, fontsize=15)
        #plt.text(0.45*float(data[3][-1])/1000000,0.3*int(max(data[2])),ttl_t, fontsize=15)
        #plt.text(0.45*float(data[3][-1])/1000000,0.4*int(max(data[2])),b_variance, fontsize=15)

#print(data)
        
plt.ylim(0, 1.1*max(ms))
#plt.ylim(0, 1.1)
plt.xlim(0, 7)

#labels
plt.axvline(x=5, linestyle='--', color='k') #red light on
plt.axvline(x=15.5, linestyle='--', color='k')#blue light
plt.axvline(x=26, linestyle='--', color='k')#end of expt 

plt.ylabel('Number of Black Pixels')
plt.xlabel('Time / s',fontsize=15)
plt.legend(loc='best')
plt.savefig(datadirectory+'_plot.png')







    
