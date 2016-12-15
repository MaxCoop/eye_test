# Pupil measurement device

#Dec 2016 update

#Software process

Experimentation has shown that for low resolution videos (480p, 720p, 1080p) the number of black pixels is a slow and innacurate method of pupil mesurement. Whilst improvments to the eyepiece (specifically the addition of another IR led) has improved thresholding it appears very noisy compared to full resolution data.

Current experiments have implemented the Hough circle dection algorithm 9using canny edge detection) to detect a single circle in our original image (code in `measure_pupil_hough.py`). We expect this to be unusably slow on the Rpi.

Kaps has implemented image capture and near real-time processing on 480p video `CCodeVid2.cpp`. OUr current pupil detection algotithim has an unacceptable signal to noise ratio in these low resolution videos. 

# Image processing
Currently images are parsed by the `measure_pupil_hough.py` script [`python measure_pupil_hough.py Handsomebroscaled.png`] 
The `Handsomebroscaled.png` file is an example input for processing
The process sequence is performed using OpenCV methods:
  - extract black pixels band using `cv2.inRange()`
  - [median blur appears unncesessary here median filter (5) - `medianBlur()` , gaussian blur gives worse results]
  - Hough circle matching with initial parameters [1.5, 1000, 30, 15, 5, 100]
  - this currently omits image normalisation equaliseHist() 

#Hough parameters
A `dp` of 1.5 or 1.9 appears optimimal for early testing. Higher and lower values (with the exception of 1.3) give reasonable resukts but a worse fit. The circle distance parameter has no clear effect (so 1000 is fine for the moment).                        param1=30,param2=15,minRadius=5,maxRadius=100.

## To Do
 - [ ] Test Hough algorthim speed on RPi and vary parameters for performance.
 - [ ] Test hough algorthim for noise in 480p videi on RPi
 - [ ] Gather reproducibility data using python video processing code
 - [ ] Multithreaded image processing and capture


--------

#Current Process
Capture on rpi with `flash.sh` using protocol defined in `neopixel.py` in the comms subdirectory to generate a .h264 type video file. Convert to .m4v type using VLC on OSX and then process using the `video_process.py` script with an estimated threshold of 50.

# System description
System designs and code for a cheap pupil measurement device that is capable of fabrication and use by non-technical people.
Current system design uses a 3D printed google (the OpenSCAD files), and two neopixels for colour specific illumination, an IR LED controlled using a transistor and a 15 Ohm resistor.  IR LED is driven by GPIO pin 4, Neopixels are driven from GPIO 18. The google also contains the lens from a Google cardboard and photographic negative film to block visible light to the NoIR camera used for image capture.

Neopixels used in this project have the datasheet from here - https://cdn-shop.adafruit.com/datasheets/WS2812.pdf

Intensity measurement for blue light = 200-400 mCD (milliCandela) according to the Neopixel datasheet


# Scripts
Main script is `flash.sh` which currently uses the `raspivid` command for 24 fps image capture to `outvid.h264` and calls the script `neopixel.py` from the `` directory to perform the specific light sequences. 

# Image processing
Currently images are parsed by the `measure_pupil.py` script [`python measure_pupil.py elf.jpg`] 
The `elf.jpg` file is an example input for processing
The process sequence is performed using OpenCV methods:
  - extract red channel
  - histogram normalisation - `equalizeHist()`
  - median filter (5) - `medianBlur()`
  - binary thresholding - `threshold(50)`
  - discarding the left half of the image (this should be done earlier)

Then black pixels from individual images are counted using `calcHist()`. This script also tries to identify the location of the pupil by returning the indexes of the maximum black pixel for image rows and columns and then plotting an area equivalent circle at that location. This will systematically overestimate the pupil measurement due to black pixel noise.

# Video processing
Videos are processed using the same process, but via the `video_process.py` script [`python video_process.py inputvid.hm4v thresholdvalue`]. This script also writes the processed frames to an m4v file for later inspection and produces a plot of the number of frames vs the number of black pixels in each.

# Mobile device testing
We also examine the potential of using a mobile camera without the IR filter removed. 
Following standard methods for nightvision (RBG averages, min/max colour values) we may be able to replicate the NoIR camera results using a cheaper setup. This is currently accessed via the:
`python iphone_image_process.py image.jpg`

Credit to Dr. Jesse Gale for original concept and implementation idea.

#Other file notes
eye_image_process.py - an early test script attempting to normalise the image as one would for an infragram

python_image_grabber.py - a script for rapidly capturing video from the Rpi camera. This can be used in conjunction with the `flash.sh` script in place of the raspivid command however it currently does not yeild results comparable to that of the existing setup. It should provide higher framerates and closer to real-time resolution however. 
