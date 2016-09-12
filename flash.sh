#!/bin/bash

gpio mode 4 out

#turn LED on
gpio write 4 1 &
#start video capture
raspivid -o outvid.h264 -t 60000 &
#flash neopixel for appropriate time
sudo python rpi_ws281x/python/examples/neopixel_elf.py &

wait
#gpio write 4 0
echo 'Complete'
#now call  image processing script on the generated file
MP4Box -add outvid.h264 outvid.mp4
