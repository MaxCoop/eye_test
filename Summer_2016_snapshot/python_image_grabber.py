import time
import picamera
import picamera.array
import numpy as np
import RPi.GPIO as GPIO
import cv2

height = 1080
width = 1920
fps = 30

#we want to convert output to video
fourcc = cv2.cv.CV_FOURCC('m','j','p','g')
vout = cv2.VideoWriter()
success = vout.open('captured_video.avi', fourcc, fps, (width, height), True)

class AnalysisClass(picamera.array.PiYUVAnalysis):
   def analyse(self,array):
     #does the processing
     #line = array[height/2,:,0]<100
     #if np.any(line):
     #   err = np.dot(line,discr)
     #calls some additional method
     vout.write(array)


with picamera.PiCamera() as camera:
  with picamera.array.PiYUVAnalysis(camera) as output:
    camera.resolution = (height,width) 
    camera.framerate = fps

    output = AnalysisClass(camera)
    camera.start_recording(output,format='yuv')
    #while (time.time() - start_time)<30: 
    #   camera.wait_recording(1000)
    #pass #print('run')
  
    camera.stop_recording()

vout.release()
