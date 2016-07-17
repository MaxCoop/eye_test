import cv2
#import cv2.cv as cv
import numpy as np
import sys
import matplotlib.pyplot as plt

img = cv2.imread(str(sys.argv[1]))

res = 100

shp = img.shape
print(shp)

print(img[0][0][0])
#print(img[0][0][1])
#print(img[0][0][2])


##contract enhance first

##thresholding??
ret, imgt = cv2.threshold(img[:,:,0], 100,255 ,cv2.THRESH_BINARY)
##histogram normalization
#imgt = cv2.equalizeHist(img[:,:,0])



print(range(0, shp[1],res))
#print number of black pixels for each row of pixels
#across
ac = []
for i in range(0, shp[1], res):
	s = sum(img[:,i,0])
	ac.append(s)
	#print(str(i)+": "+str(s))


#down
dw = []
for i in range(0, shp[0], res):
	s = sum(img[i,:,0])
        dw.append(s)
        #print(str(i)+": "+str(s))


#drawcentre
#cv2.circle(gimg, (i, i), 2, (0,0,255), 3) #image, centre x/y, radius, color, ?? 

'''
cv2.imshow('Stuff', r)
cv2.waitKey(0)
'''

cv2.destroyAllWindows()

plt.imshow(imgt, 'gray')
#plt.imshow(img[:,:,0])
#plt.plot([j*res for j in range(len(ac))], ac, 'ko-')

plt.xlim(0,2500)
plt.ylim(0,2000)
#plt.ylabel('Whiteness across image')
plt.show()

#cv2.imwrite('out.png', r)
