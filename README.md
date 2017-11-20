# Pupil measurement device

# System description

Our system uses a RPi 2 B+ as a base along with a NoIR camera to recieve images of teh pupil illuminated under IR light.
We use neopixel rings to illuminate the eye with visible light and them image process the camera frame stream to measure the pupil size based of several different algorithms (listed below). The Rpi acts as its own wifi hotspot for the 'Openpupil' network. Once connected to the network, the device is controlled by a python flask webapp acessible through a browser at the ip address `192.168.42.1:5000/`. The flask webapp code is contained within the `app.py` file, whereas site dynamics are controlled via javascript in the `index.html` and calls some additional javascript functions from the `extra.js` file. The webapp can be launched by running the command `sudo python app.py` from inside the webapp directory. We also use `supervisor-ctl` to run this app at boot by default.  

# Software process

## Supervisor
We use supervisor-ctl to launch the flask webserverapp at boot.
Scripts are called automatically from the `supervisord.conf` file and running the `supervisorctl status all` command will show what scripts/p[rograms are currently known by and teh status of them under supervior.

## Scripts
Main script is `RunMe.sh` which currently uses the `/CCodeVid5` command for ?? fps image capture and generates datafiles in teh data directory based on time and date. Illumintation is controlled by and calling the script `neopixel_elf.py` from the neopixel driver directory to perform the specific light sequences. 

## Video frame processing
Currently frames are parsed directly from the rpi camers by the CCodeVid5.cpp method  
The process sequence is performed using OpenCV methods:
  - extract red channel
  - binary thresholding - `threshold(50)` but dynamically calculated from the darkest 6000 pixels
  - count number of black pixels after thresholding (analog of pupil area)
  - estimate centre location of pupil and pupil width and height each frame based of x and y intensity histograms
  - in the past we have also attempted canny edge detction followed by hough circle fitting
  - ultimately we will also implements Kaps' spiral edge following code for higher resolution and faster measurement 

# Hardware System description
System designs and code for a cheap pupil measurement device that is capable of fabrication and use by non-technical people.
Current system design uses a 3D printed google (the OpenSCAD files), and a 16 neopixel ring for colour specific illumination, two wide angle IR LEDs controlled using a transistor and a 15 Ohm resistor.  IR LED is driven by GPIO pin 4, Neopixels are driven from GPIO 18. The google also contains the lens from a Google cardboard and photographic negative film to block visible light to the NoIR camera used for image capture.

Neopixels used in this project have the datasheet from here - https://cdn-shop.adafruit.com/datasheets/WS2812.pdf

Intensity measurement for blue light = 200-400 mCD (milliCandela) according to the Neopixel datasheet

3D Model for Neopixel used in this project can be found here: https://grabcad.com/library/neopixelring-16x-1/details?folder_id=1182174

3D Model for Eyepiece used in this project can be found here: https://grabcad.com/library/eyecup

3D Model for Raspberry Pi used in Assembly can be found here: https://grabcad.com/library/raspberry-pi-model-b-2

System uses Raspberry PI 2 B. Pinout used here -> http://pi4j.com/images/j8header-2b-large.png



### To Do
 - fix security an permissions (sudo) issues
 - improve javascript app load time by caching
 - upgrades to binocularity via multiplexer and multiple neopixel rings
 - implement spiral edge detection alcorithing for `CCodeVid6.cpp`
 - fix bug where preview button locks camera process
 - the 'measure' button needs 'close preview' functionality added to it so that it frees the camera for CCodeVid analysis
 
Credit to Dr. Jesse Gale for original concept and implementation idea. To Kapetini Polutea for the image processing code and algorithims. To Shaetrun Pathmanathan for the electronics and hardware redesign and for the web interface and javascript.
