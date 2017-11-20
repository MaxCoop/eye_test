import cv2
#import cv2.cv as cv
import numpy as np
import sys
from matplotlib import pyplot as plt

img = cv2.imread(str(sys.argv[1]))

print(img.shape)

#only take r/IR channel
#b,g,r = cv2.split(img)

#faster
r = img[:,:,2]
g = img[:,:,1]
b = img[:,:,0]

#contract enhance methods
#RGB average
#min/max rgb colour values
#individual color values

##gradient
#laplacian = cv2.Laplacian(img, cv2.CV_64F)
#sobel_x = cv2.Sobel(img, cv2.CV_64F, 1, 0, ksize=5)
#sobel_y = cv2.Sobel(img, cv2.CV_64F, 0, 1, ksize=5)

r_imgt = cv2.equalizeHist(r)
g_imgt = cv2.equalizeHist(g)
b_imgt = cv2.equalizeHist(b)

r_median = cv2.medianBlur(r_imgt, 5)
g_median = cv2.medianBlur(g_imgt, 5)
b_median = cv2.medianBlur(b_imgt, 5)

threshold = 50
ret, r_thresh_img = cv2.threshold(r_median, threshold,255 ,cv2.THRESH_BINARY)
ret, g_thresh_img = cv2.threshold(g_median, threshold,255 ,cv2.THRESH_BINARY)
ret, b_thresh_img = cv2.threshold(b_median, threshold,255 ,cv2.THRESH_BINARY)


#hist = cv2.calcHist([thresh_img], [0], None, [256], [0,256])

plt.subplot(331)
plt.imshow(r, 'gray')
plt.subplot(332)
plt.imshow(g, 'gray')
plt.subplot(333)
plt.imshow(b, 'gray')
plt.subplot(334)
plt.imshow(r_imgt, 'gray')
plt.subplot(335)
plt.imshow(g_imgt, 'gray')
plt.subplot(336)
plt.imshow(b_imgt, 'gray')
plt.subplot(337)
plt.imshow(r_thresh_img, 'gray')
plt.subplot(338)
plt.imshow(g_thresh_img, 'gray')
plt.subplot(339)
plt.imshow(b_thresh_img, 'gray')

#plt.subplot(335)
#plt.imshow(thresh_img, 'gray')
plt.show()

'''
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
diff = r-b
cv2.imshow('Stuff', diff)
cv2.waitKey(0)


'''
plt.subplot(221),plt.imshow(img),plt.title('ORIGINAL')
plt.subplot(222),plt.imshow(r, 'gray'),plt.title('RED')
plt.subplot(223),plt.imshow(g, 'gray'),plt.title('GREEN')
plt.subplot(224),plt.imshow(b, 'gray'),plt.title('BLUE')
plt.show()
'''
'''
cv2.imwrite('iphoner.png', r)
cv2.imwrite('iphoneg.png', g)
cv2.imwrite('iphoneb.png', b)
#cv2.imwrite('outb.png', bc)

#cv2.imwrite('outir.png', ir)
'''
cv2.destroyAllWindows()
