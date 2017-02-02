import cv2
#import cv2.cv as cv
import numpy as np
import sys
import matplotlib.pyplot as plt

img = cv2.imread(str(sys.argv[1]))

shp = img[:,:,0].shape
print(shp)

'''
##contrast enhance first - using histogram normalization
imgt = cv2.equalizeHist(img[:,:,0])
plt.imshow(imgt, 'gray')
plt.show()
'''

#add Hough circle detection

# Threshold the image to get only black colors
# Convert BGR to HSV
hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)

ranged_image = cv2.inRange(hsv, np.array([0,0,40]), np.array([180,255,70]))
plt.figure(1)
plt.imshow(ranged_image, 'gray')
#plt.show()

##median filter
median = cv2.medianBlur(ranged_image, 5)
plt.figure(2)
plt.imshow(median, 'gray')
#plt.show()

circles = cv2.HoughCircles(ranged_image,cv2.cv.CV_HOUGH_GRADIENT,1.5,1000,
                           param1=30,param2=15,minRadius=5,maxRadius=100)
#1.0 works - but bad fit
#1.1 works reasonably
#1.2 works reasonably
#1.3 doesnt work
#1.4 works reasonably
#1.6 works reasonably

#1.5 works well
#1.9 works exceptionally


#param1 gives results between 5 and 95 (with param2 at 15)
#param2 gives results between 5 and 25 (with param1 at 30)
circles = np.uint16(np.around(circles))

img2 = img
for i in circles[0,:]:
    #ask which circle has the largest number of black pixels and only use that
    # draw the outer circle
    cv2.circle(img2,(i[0],i[1]),i[2],(0,255,0),2)
    # draw the center of the circle
    cv2.circle(img2,(i[0],i[1]),2,(0,0,255),3)
    

#plt.imshow(ranged_image)
plt.figure(3)
plt.title(len(circles[0,:]))
plt.imshow(img2)
plt.show()

cv2.destroyAllWindows()

#cv2.imwrite('out.png', r)
