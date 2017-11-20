#!/bin/bash

gpio mode 7 out
gpio mode 0 out
gpio mode 1 out

#turn LED on
gpio write 7 1
gpio write 0 1

#sudo python rpi_ws281x/python/examples/turn_light_off.py

DATE=$(date +"%d-%m-%Y_%H%M")

#sudo python rpi_ws281x/python/examples/neopixel_elf.py &

raspivid -o /home/pi/videoimages/$DATE.h264  -t 10000 -w 640 -h 480

MP4Box -fps 30 -add /home/pi/videoimages/$DATE.h264 /home/pi/videoimages/$DATE.mp4

#./CCodeVid4

timeout 7 `omxplayer /home/pi/videoimages/$DATE.mp4`