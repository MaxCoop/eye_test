# Pupil measurement device

## To Do
 - [ ] Improve video processing speed
 - [ ] Real time pupil detection
 - [ ] Multithreaded image processing and capture
 - [ ] Evaluation on different image processing techniques
 - [ ] Evaluation of lighting methodologies

# System description
System designs and code for a cheap pupil measurement device that is capable of fabrication and use by non-technical people.
Current system design uses a 3D printed google (the OpenSCAD files), and two neopixels for colour specific illumination, an IR LED controlled using a transistor and a 15 Ohm resistor.  IR LED is driven by GPIO pin 4, Neopixels are driven from GPIO 18. The google also contains the lens from a Google cardboard and photographic negative film to block visible light to the NoIR camera used for image capture.


# Scripts
Main script is `flash.sh` which currently uses the `raspivid` command for 24 fps image capture to `outvid.h264` and calls the script `neopixel.py` from the `` directory to perform the specific light sequences. 

# Image processing
Currently images are parsed by the `measure_pupil.py` script [`python measure_pupil.py inputimage.jpg`] 
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
We also examin the potential of using a mobile camera without the IR filter removed. 
Following standard methods for nightvision (RBG averages, min/max colour values) we may be able to replicate the NoIR camera results using a cheaper setup. This is currently accessed via the:
`python iphone_image_process.py image.jpg`


Credit to Dr. Jesse Gale for original concept and implementation idea.

#Other file notes
eye_image_process.py - an early test script attempting to normalise the image as one would for an infragram

python_image_grabber.py - a script for rapidly capturing video from the Rpi camera. This can be used in conjunction with the `flash.sh` script in place of the raspivid command however it currently does not yeild results comparable to that of the existing setup. It should provide higher framerates and closer to real-time resolution however. 
