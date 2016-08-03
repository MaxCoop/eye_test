import cv2
#import cv2.cv as cv
import numpy as np
import sys
import matplotlib.pyplot as plt

img = cv2.imread(str(sys.argv[1]))

shp = img[:,:,0].shape
print(shp)

print(img[0][0][0]) #Red
#print(img[0][0][1]) #Green
#print(img[0][0][2]) #Blue

#simple contrast enhancement
#multiplier = 2
#ones_array = np.ones((shp[0], shp[1]), np.uint8)
#multiple_array = multiplier*ones_array
#arrays mist be same type to be multiplied
#print(img[:,:,0].dtype)
#print(multiple_array.dtype)
#imgt = cv2.multiply(img[:,:,0], multiple_array)

##contrast enhance first - using histogram normalization
imgt = cv2.equalizeHist(img[:,:,0])
plt.imshow(imgt, 'gray')
plt.show()

#from http://docs.opencv.org/3.1.0/d5/daf/tutorial_py_histogram_equalization.html#gsc.tab=0
#adaptive histogram normalised
# create a CLAHE object (Arguments are optional).
#clahe = cv2.createCLAHE(clipLimit=2.0, tileGridSize=(8,8))
#cl1 = clahe.apply(img)


##noise reduction
##normalised block
#blur = cv2.blur(imgt, (5,5))
##GaussianBlur
#gaussian = cv2.GaussianBlur(imgt, (5,5), 0)
##BilateralBlur
#bilateral = cv2.bilateralFilter(imgt, 9, 75, 75)
##median filter
median = cv2.medianBlur(imgt, 5)


##dilation and erosion
kernel = np.ones((11,11),np.uint8) 

dilated = cv2.dilate(im, kernel)
eroded = cv2.erode(img,kernel,iterations = 1)


##thresholding??
threshold = 50
ret, thresh_img = cv2.threshold(median, threshold,255 ,cv2.THRESH_BINARY)

##note that adaptive thresholding will likely give better results
#http://docs.opencv.org/3.1.0/d5/daf/tutorial_py_histogram_equalization.html#gsc.tab=0
#AND
#http://docs.opencv.org/3.0-beta/doc/py_tutorials/py_imgproc/py_thresholding/py_thresholding.html

th2 = cv2.adaptiveThreshold(median,255,cv2.ADAPTIVE_THRESH_MEAN_C,cv2.THRESH_BINARY,11,2)
th3 = cv2.adaptiveThreshold(median,255,cv2.ADAPTIVE_THRESH_GAUSSIAN_C,cv2.THRESH_BINARY,11,2)

'''
for i in range(0,255, 20):
        print(i)
        threshold = i
        ret, thresh_img = cv2.threshold(median, threshold,255 ,cv2.THRESH_BINARY)
        plt.imshow(thresh_img, 'gray')
        plt.show()
'''

#NOTICE THAT PUPIL IS ALWAYS RIGHT Centre OF IMAGE
'''
o_img = thresh_img
#draw line across image centre
cv2.line(o_img, (0, 0), (shp[1], shp[0]), (100,100,100), 3) #image, centre x/y, radius, color,  
cv2.line(o_img, (0, shp[0]), (shp[1], 0), (100,110,100), 3) #image, centre x/y, radius, color,  

plt.imshow(o_img, 'gray')
plt.show()
'''

####Create a whitemask for the left side of the image
mask_array = np.zeros((shp[0], shp[1]), np.uint8)
mask_array[:, shp[1]/2:] +=255
plt.imshow(mask_array, 'gray')
plt.show()

masked_img = cv2.multiply(thresh_img, mask_array)
masked_img[:, :shp[1]/2] +=255
plt.imshow(masked_img)
plt.show()

##now simply calculate pixel area of non-white pixels
#faster opencv version
#(images, channels, mask, histSize (i.e. bin count), ranges
hist = cv2.calcHist([masked_img], [0], None, [256], [0,256])
#plt.plot(hist)
#plt.show()
##nb mask allows calculation using only part of image
'''
masked_img2 = cv2.bitwise_and(thresh_img, thresh_img, mask=mask_array)
masked_hist = cv2.calcHist([masked_img2], [0], None, [256], [0,256])
plt.plot(masked_hist)

#numpy method
#hist, bins = np.histogram(masked_img, 256, [0,256])
#plt.hist(masked_img.ravel(), 256, [0,256])
plt.show()

plt.imshow(masked_img2)
plt.show()
'''
#print(hist)
no_of_black_pixels = hist[0]
print('Number of Black pixels: '+str(no_of_black_pixels))
print('Number of White pixels: '+str(hist[-1]))


#trying to position and measurem pupil
res = 10

#print(range(0, shp[1],res))
#print number of black pixels for each row of pixels
#across
ac = []
for i in range(0, shp[1], res):
	s = sum(masked_img[:,i])
	ac.append(s)
	#print(str(i)+": "+str(s))
#down
dw = []
for i in range(0, shp[0], res):
	s = sum(masked_img[i,:])
        dw.append(s)
        #print(str(i)+": "+str(s))

plt.plot(range(len(ac)), ac, 'k.')
plt.plot(range(len(dw)), dw, 'r.')

plt.plot(ac.index(min(ac)), min(ac), 'ko')
plt.plot(dw.index(min(dw)), min(dw), 'ro')
'''
#centre ac
acf = np.polyfit(range(len(ac)),ac, 2)
dwf = np.polyfit(range(len(dw)),dw, 2)
f1 = np.poly1d(acf)
f2 = np.poly1d(dwf)

# calculate new x's and y's
plt.plot(range(len(ac)), f1(range(len(ac))), 'k-')
plt.plot(range(len(dw)), f2(range(len(dw))), 'r-')
'''

plt.show()

#attemp to draw a circle around pupil
#calculate radius from number of black pixels
rd = np.sqrt(no_of_black_pixels/np.pi)

#drawcentre
cv2.circle(masked_img, (ac.index(min(ac))*res, dw.index(min(dw))*res), rd, (100,100,100), 3) #image, centre x/y, radius, color, ?? 
#this could be improved by fitting for the minima rather than just selecting the minima

plt.imshow(masked_img, 'gray')
plt.show()

#drawcentre
#cv2.circle(gimg, (i, i), 2, (0,0,255), 3) #image, centre x/y, radius, color, ?? 

cv2.destroyAllWindows()

#plt.imshow(imgt, 'gray')
#plt.imshow(img[:,:,0])
#plt.plot([j*res for j in range(len(ac))], ac, 'ko-')

#plt.xlim(0,2500)
#plt.ylim(0,2000)
#plt.ylabel('Whiteness across image')
#plt.show()

#cv2.imwrite('out.png', r)
