import cv2
#import cv2.cv as cv
import numpy as np
import sys

img = cv2.imread(str(sys.argv[1]))

print(img.shape)

#only take r/IR channel
#b,g,r = cv2.split(img)

#faster
r = img[:,:,2]
g = img[:,:,1]
b = img[:,:,0]

bc = img[:,:,0]

for i in range(img.shape[0]):
	for j in range(img.shape[1]):
		if bc[i,j] == 0:
			bc[i,j] = 1


#scaling for IR only - from infragram website requires blue filter
#(r-b)/(r+b)

ir = (r-bc)/(r+bc)

#drawcentre
#cv2.circle(gimg, (i, i), 2, (0,0,255), 3) #image, centre x/y, radius, color, ?? 

'''
cv2.imshow('Stuff', r)
cv2.waitKey(0)
'''

cv2.imwrite('outr.png', r)
cv2.imwrite('outg.png', g)
cv2.imwrite('outb.png', bc)

cv2.imwrite('outir.png', ir)

cv2.destroyAllWindows()
