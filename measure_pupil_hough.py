import cv2
#import cv2.cv as cv
import numpy as np
import sys
import matplotlib.pyplot as plt

img = cv2.imread(str(sys.argv[1]))

shp = img[:,:,0].shape
print(shp)

##contrast enhance first - using histogram normalization
imgt = cv2.equalizeHist(img[:,:,0])
plt.imshow(imgt, 'gray')
plt.show()

#add Hough circle detection

# Threshold the image to get only black colors
# Convert BGR to HSV
hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
'''
for j in range(10,80,10):
        ranged_image = cv2.inRange(hsv, np.array([0,0,0]), np.array([180,255,j]))
        plt.title(j)
        plt.imshow(ranged_image)
        plt.show()
'''
#40, 60
ranged_image = cv2.inRange(hsv, np.array([0,0,40]), np.array([180,255,70]))

##GaussianBlur
#gaussian = cv2.GaussianBlur(imgt, (5,5), 0)- might be faster??

##median filter
median = cv2.medianBlur(ranged_image, 5)

circles = cv2.HoughCircles(median,cv2.cv.CV_HOUGH_GRADIENT,1.2,1000,
                           param1=30,param2=15,minRadius=15,maxRadius=100)

circles = np.uint16(np.around(circles))

#rd = img[:,:,0]
for i in circles[0,:]:
    #ask which circle has the largest number of black pixels and only use that
    # draw the outer circle
    cv2.circle(img,(i[0],i[1]),i[2],(0,255,0),2)
    # draw the center of the circle
    cv2.circle(img,(i[0],i[1]),2,(0,0,255),3)

#plt.imshow(ranged_image)
plt.imshow(img)

plt.show()

cv2.destroyAllWindows()

#cv2.imwrite('out.png', r)
