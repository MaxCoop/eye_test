# Instructions for setting up the background RPi

* Start with fresh raspian install (we're using 2015-09-24-raspian-jessie.img for the RPi 2B+)
* Start with fresh raspian install (we're using 2017-09-07-raspian-jessie.img for the RPi 3)

* `sudo raspi-config` + resize SD card partition and enable camera and ssh 
* `sudo apt-get update`
* `sudo apt-get upgrade`
* `sudo apt-get install git-core git`
* `sudo apt-get install libopencv-dev cmake`
* if using the multiplexer run  `sudo apt-get install i2c-tools python-smbus`
* if not using the multiplexer run `sudo apt-get install python-picamera`
* `sudo apt-get upgrade`

For the cpp code to work
* download the raspicam library [here](https://sourceforge.net/projects/raspicam/files/?)
* then run the following commands:
  * `tar xvzf raspicamxx.tgz`
  * `cd raspicamxx`
  * `mkdir build`
  * `cd build`
  * `cmake ..`
  * `make`
  * `sudo make install`
  * `sudo ldconfig`

Then install supervisor
 * `pip install supervisor`
 * Then create `/etc/supervisord.conf` and populate appropriately

Then install flask
 * `pip install flask`

Then clone code from repo
* `git clone https://github.com/kaiwhata/eye_test`
* `git status`

You will also need to get teh neopixel control library downloaded and working by following instructions here:
* https://learn.adafruit.com/neopixels-on-raspberry-pi/overview
* and make sure to install the python wrappers so that the example neopixel.py command works

To add code to the repo:
* `git push` then enter username and password

To pull new code from the repo:
* `git pull`

To use the camera from C programs the `camera.h` file must be in the same directory as the script runs from.
* `#include "camera.h"` this is the camera import line.

Once you're ready to have the pi as it's own wifi hotspo follow the setup instructions here.
 * https://learn.adafruit.com/setting-up-a-raspberry-pi-as-a-wifi-access-point/overview
 * ONLY DO THIS ONCE YOU ALREADY HAVE EVERYTHING YOU NEED FROM THE INTERNET IF YOU ARE NOT USING AN ETHERNET CONNECTION
 (not that it's hard to undo - it's just a pain to constantly reconfigure your `/etc/network/interfaces` files
 
## Additional Python Libraries (optional for development)
* `sudo apt-get install python-opencv python-scipy python-numpy ipython python-setuptools python-matplotlib python-picamera`
