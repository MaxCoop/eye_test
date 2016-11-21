import matplotlib.pyplot as plt


ifile = open('outvid_Sept9.m4v_50_data.txt', 'r')
datalist=[]
for line in ifile.readlines():
    datalist.append(line.strip())    

plt.figure(1, figsize=(12,6))
plt.plot(range(len(datalist)),datalist, 'ko-')

#plt.xlim([0, 600])
#plt.xlim([600, 1200])
plt.xlim([1200, 1800])
plt.ylim([0, 125000])
plt.xlabel('Frames')
plt.ylabel('Number of black pixels')
plt.show()
