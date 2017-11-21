"""Automatically plots data and calculates FPS from gathered data"""
#import math
import sys
import matplotlib.pyplot as plt
#from scipy.signal import savgol_filter, medfilt
import numpy as np

def find_nearest(array, value):
    """finds the nearest value in an array of elements and returns index of nearnest value"""
    array = np.array(array)
    idx = (np.abs(array-value)).argmin()
    return idx

def upload(datafile):
    """Datafile format is
	Frames,ThresholdValue,BlackPixels,PupilCenterX,PupilCenterY,PupilWid,PupilLen,Time
	40,22,3129,-1,-1,-1,-1,535041
    """
    ifile = open(datafile, 'rU')
    data = []
    for line in ifile.readlines():
        line = line.strip()
        data.append(line.split(','))
    return data

def plot_data(datafile):
    """takes strings and plots data from given datafile in expected format"""
    #datafile = 'Test1/frames100Median5_Thresh50BlackPixels.txt'
    data = upload(datafile)
    data = np.array(data)

    #m = max([float(i) for i in data[2]])
    #m = 15000
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
    plt.figure(2, figsize=(12,6))
    plt.title(datafile)
    plt.plot([float(i)/1000000 for i in data[3]],data[2], 'k.-', label='Black Pixels')

    #we filter a filter using a Savitzky-Golay filter for non-periodic signals
    #using a polynomial regression over a small window of data [5 datapoint to order 1 polynomial]
    avg_blur = savgol_filter(data[2], 5 , 1)
    plt.plot([float(i)/1000000 for i in data[3]], avg_blur,'r--', label='No Blur filtered')

    var_blur = []

    #calculating variation measurement
    for i in range(len(data[2])):
        dp1 = (float(data[2][i]) - float(avg_blur[i]))**2
        var_blur.append(dp1)

    var_blur = math.sqrt(sum(var_blur)/(len(var_blur)-1))#calculate sqrt of sample variance (s^2)

    av_f_p_t = 'Average Frame Processing time: '+str(round(float(data[3][-1])/(len(data[3])*1000000),2))+' s/frame'
    av_fps = 'Average FPS: '+str(round(1000000*(float(data[0][-1])/float(data[3][-1])),2))
    ttl_t = 'Total time: '+str(round(float(data[3][-1])/1000000,2))+' s'
    b_variance = 'Variance: '+str(round(var_blur,2))

    print(av_f_p_t)
    print(av_fps)
    print(ttl_t)
    print(b_variance)
    
    #plt.text(0.45*float(data[3][-1])/1000000,0.1*m,av_f_p_t, fontsize=15)
    #plt.text(0.45*float(data[3][-1])/1000000,0.2*m,av_fps, fontsize=15)
    #plt.text(0.45*float(data[3][-1])/1000000,0.3*m,ttl_t, fontsize=15)
    #plt.text(0.45*float(data[3][-1])/1000000,0.4*m,b_variance, fontsize=15)

    #plt.ylim(0, m)
    plt.ylabel('Number of Black Pixels')
    plt.xlabel('Time / s',fontsize=15)
    #plt.legend(loc='best')
    #plt.savefig(datafile+'_plot_time.png')

    figure(3, figsize=(12,6))
    plt.plot([float(i)/1000000 for i in data[3]],data[4], 'b.-', label='Hough Radius')
    plt.ylabel('Hough Radius / px')
    plt.xlabel('Time / s',fontsize=15)
    #plt.legend(loc='best')
    
    figure(4, figsize=(12,6))
    plt.plot([float(i)/1000000 for i in data[3]],data[9], 'r.-', label='Width')
    plt.plot([float(i)/1000000 for i in data[3]],data[10], 'k.-', label='Length')
    plt.plot([float(i)/1000000 for i in data[3]],[(float(data[9][i])+float(data[10][i]))/2.0 for i in range(len(data[10]))], 'b.-', label='Average')
    plt.ylim(0, max([float(i) for i in data[10]]))
    plt.ylabel('Pixel Size / px')
    plt.xlabel('Time / s',fontsize=15)
    plt.legend(loc='best')
    '''

    plt.figure(0, figsize=(12, 6))
    #black pixels vs frames
    plt.plot(data[1:, 0], data[1:, 2], 'b.-', label='BlackPixels')
    #black pixels vs time
    #plt.plot(data[1:, -1],data[1:, 2], 'b.-', label='BlackPixels')
    av_fps = float(data[-1][0])/(float(data[-1][-1])/1000000)
    plt.text(float(data[-1][0])*0.1, 200, 'FPS:'+str(round(av_fps, 1)), fontsize=15)
    #plt.ylim(0, max([float(i) for i in data[10]]))
    plt.ylabel('Number of Black Pixels / ', fontsize=15)
    plt.xlabel('Frame / s', fontsize=15)
    #plt.legend(loc='best')
    plt.savefig(datafile[:-4]+".png")
    #plt.show()

plot_data(sys.argv[1])
