#Instructions for setting up the background RPi

* Start with fresh raspian install (we're using 2015-09-24-raspian-jessie.img)
* `sudo raspi-config` + resize SD card partition and enable camera and ssh 
* `sudo apt-get update`
* `sudo apt-get upgrade`
* `sudo apt-get install git-core git`
* `sudo apt-get install libopencv-dev`

Then load code from Arthur's ENGR101 library in the folder ENGR101library folder
* `git clone https://github.com/kaiwhata/eye_test`
* `git status`

To add code to the repo:
* `git push` then enter username and password

To pull new code from the repo:
* `git pull`

