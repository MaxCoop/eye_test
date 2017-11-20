print("Program Start")
import seabreeze.spectrometers as sb
import pylab as plt
import matplotlib.animation as animation
import matplotlib.widgets as Button
import numpy as np
import time
import math

print("Setting up spec")
# setup the spectrometer
devices = sb.list_devices()
print(devices)
spec = sb.Spectrometer(devices[0])
print("Reading data set")
#read first data set
global waves
waves = spec.wavelengths()
intensity = spec.intensities()

print("Setting up plot")
fig = plt.figure(1)

global ax1,ref,data,t,logt
axl = fig.add_subplot(1,1,1)


def save(name, wavess, intes):
    ar3 = zip(wavess,intes)
    with open(name,'w') as file_:
	file_.write("\n".join(["{},{}".format(z[0],z[1]) for z in ar3]))   
    
    
def animate(i):
    waves = spec.wavelengths()
    intensity = spec.intensities()
    axl.clear()
    axl.plot(waves,intensity)

class Index(object): 
    indC =0
    indT = 0
    def __init__(self):
        self.indR = 0
        
    def ref(self, event):
        global refpy
        self.indR+=1
        ref = spec.intensities()
        waves = spec.wavelengths()
        save("ref{}.txt".format(self.indR),waves,ref)
        print("Taken ref")

    def capture(self,event):
        global data
        data = spec.intensities()
        waves = spec.wavelengths()
        fig4 = plt.figure()
        ax4 = fig4.add_subplot(1,1,1) 
        ax4.plot(waves,data)
        self.indC+=1
        save("cap{}.txt".format(self.indC),waves,data)
        print("Taken Capture")

    #def trans(self,event):
     #   global t
      #  t = data/ref
       # waves = spec.wavelengths()
        #fig2 = plt.figure()
        #ax2 = fig2.add_subplot(1,1,1)
        #ax2.plot(waves,t)
        #plt.show()
        #print("Taken Trans")


   # def aborbs(self,event):
    #    global logt,ax3,fig
     #   logt = - np.log10(t)
      #  fig3 = plt.figure()
       # ax3 = fig3.add_subplot(1,1,1)
        #ax3.plot(waves,logt)
        #plt.show()
        #print("Taken absorption")



callback = Index()


axref = plt.axes([0.5,0.05,0.1,0.075])
axcap = plt.axes([0.61,0.05,0.1,0.075])
#axtrans = plt.axes([0.72,0.05,0.1,0.075])
#axabsobs = plt.axes([0.83,0.05,0.1,0.075])

refs = Button.Button(axref,'Ref')
refs.on_clicked(callback.ref)

captures = Button.Button(axcap,'Capture')
captures.on_clicked(callback.capture)

#transs = Button.Button(axtrans,'Calculate transmission')
#transs.on_clicked(callback.trans)

#aborbss = Button.Button(axabsobs,'Calculate absorption')
#aborbss.on_clicked(callback.aborbs)

#Need to store graph to keep it alive
ani = animation.FuncAnimation(fig,animate, interval=100)
plt.show()

spec.close()
