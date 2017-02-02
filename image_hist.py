import cv2, cv
#import cv2.cv as cv
from numpy import diff
import sys
import matplotlib.pyplot as plt

ignore = 0.1 #in seconds
frame = cv2.imread(str(sys.argv[1]))

plt.figure(1)
hist_data = plt.hist(frame[:,:,0].ravel(), 256, [0,256])

plt.axvline(int(sys.argv[2]), linestyle='--', color='k')

print(hist_data[0])#frequency
print(hist_data[1])#values

#guess threshold at 5000 pixels
px_num = 0.015*640*480
print(px_num)

t = 0
for j in range(len(hist_data[0])):
    if sum(hist_data[0][:j]) > px_num:
        t = hist_data[1][j]
        break

plt.axvline(int(t), linestyle='--', color='r')


plt.figure(2)
plt.subplot(211)
plt.plot(range(len(hist_data[0])), hist_data[0], 'ko-')

dx = 1.0
dy = diff(hist_data[0])/dx
print(dy)
plt.subplot(212)
plt.plot(range(len(dy)), dy, 'ko-')

##cdf
plt.figure(3)
plt.plot(range(len(hist_data[0])), [sum(hist_data[0][:i]) for i in range(len(hist_data[0]))], 'ko-')
plt.axhline(y = px_num, linestyle='--', color='r')

#median = cv2.medianBlur(frame[:,:,0], 5)
   
#plt.figure(2)
#plt.hist(median.ravel(), 256, [0,256])
plt.show()




