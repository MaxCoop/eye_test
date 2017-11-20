#!/bin/bash

#ensures gpio pins are in correct setting for output
gpio mode 7 out
gpio mode 0 out
gpio mode 1 out

#turn LED on
gpio write 7 1
gpio write 0 1

#ensures neopixels are off before illumintaion starts
sudo python rpi_ws281x/python/examples/turn_light_off.py

DATE=$(date +"%d-%m-%Y_%H%M")

#sets number of frames to capture
NUMBROFFRAMES = 350

#runs illumination setup - NOTE NEEDS TO BE UPDATED WITH SHAETRUNS NEW CODE
#also python script shuld be moved into app (if it still runs)
sudo python rpi_ws281x/python/examples/neopixel_elf.py &

#runs kaps and elf's image processing code
./CCodeVid5 $NUMBEROFFRAMES

#Old code for capturing and converting video
#the capture works but the conversion doesnt
#raspivid -o /home/pi/videoimages/$DATE.h264  -t 10000 -w 640 -h 480
#MP4Box -fps 30 -add /home/pi/videoimages/$DATE.h264 /home/pi/videoimages/$DATE.mp4
#timeout 7 `omxplayer /home/pi/videoimages/$DATE.mp4`
