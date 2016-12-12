#!/usr/bin/python

import matplotlib.pyplot as plt

def upload(filename):
    data = []
    ifile=open(filename, 'rU')
    for line in ifile.readlines():
        line=line.strip()
        line=line.split(',')
        data.append(line)
    return data

R = upload('red_spectrum.txt')
G = upload('green_spectrum.txt')
B = upload('blue_spectrum.txt')

Rmax = max([float(i[1]) for i in R])
Gmax = max([float(i[1]) for i in G])
Bmax = max([float(i[1]) for i in B])

Rmin = min([float(i[1]) for i in R])
Gmin = min([float(i[1]) for i in G])
Bmin = min([float(i[1]) for i in B])

plt.figure(1, figsize=(12,6))
plt.plot([i[0] for i in R],[(float(i[1])-Rmin)/(Rmax-Rmin) for i in R], 'r.-', label='Red LED')
plt.plot([i[0] for i in G],[(float(i[1])-Gmin)/(Gmax-Gmin) for i in G], 'g.-', label='Green LED')
plt.plot([i[0] for i in B],[(float(i[1])-Bmin)/(Bmax-Bmin) for i in B], 'b.-', label='Blue LED')

plt.xlim(300, 800)
plt.ylabel('Normalised Irradiance')
plt.xlabel('Wavelength / nm',fontsize=15)
plt.legend(loc='best')
plt.savefig('plot.png')
    
