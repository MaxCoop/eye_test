import cv2, cv
#import cv2.cv as cv
import numpy as np
import sys
import matplotlib.pyplot as plt

ignore = 0.1 #in seconds
cap = cv2.VideoCapture(str(sys.argv[1]))
threshold = int(sys.argv[2])

##can we write a function to better guess the threshold value

num_frames = int(cap.get(cv.CV_CAP_PROP_FRAME_COUNT))
width = int(cap.get(cv.CV_CAP_PROP_FRAME_WIDTH))
height = int(cap.get(cv.CV_CAP_PROP_FRAME_HEIGHT))
fps = cap.get(cv.CV_CAP_PROP_FPS)

print(num_frames, width, height, fps)

mask_array = np.zeros((height, width), np.uint8)
mask_array[:, width/2:] +=255

#we want to visually inspect the output
fourcc = cv2.cv.CV_FOURCC('m', 'p','4','v')
vout = cv2.VideoWriter()
success = vout.open(sys.argv[1]+'T'+sys.argv[2]+'_processed.m4v', fourcc, fps, (width, height), True)


data = []

while(cap.isOpened()):
    #empty frame
    empty = np.zeros((height, width, 3), np.uint8)
    
    ret, frame = cap.read()

    #gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    #shp = frame[:,:,0].shape
    #print(shp)
    #cv2.imshow('frame', frame)

    if type(frame) == type(None):
        break

    #check frame exists
    #if not frame is None:
    #current image processing regime
    imgt = cv2.equalizeHist(frame[:,:,0])
    median = cv2.medianBlur(imgt, 5)
    ret, thresh_img = cv2.threshold(median, threshold,255 ,cv2.THRESH_BINARY)
    masked_img = cv2.multiply(thresh_img, mask_array)
    masked_img[:, :width/2] +=255

    '''
    cv2.imshow('frame', masked_img)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
    '''
    
    #out.write(frame)
    empty[:,:,0] = masked_img
    vout.write(empty)
    
    hist = cv2.calcHist([masked_img], [0], None, [256], [0,256])
    #no of black pixels
    data.append(hist[0])
    print(len(data))
    
cap.release()
vout.release()
cv2.destroyAllWindows()

plt.plot(range(len(data))[int(ignore*fps):], data[int(ignore*fps):], 'ko-')
plt.show()

