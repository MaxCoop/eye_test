#!/usr/bin/env python
"""Program for handling server requests"""

import os
import re
import threading
#import time
#import subprocess
#import json

from flask import Flask, Response, request, send_from_directory

# Raspberry Pi camera module (requires picamera package)
from camera_pi import Camera

APP = Flask(__name__, static_url_path='')
PROTOCOL = 0
TIME = 2
COLOR = 000033
TUB = 002233

@APP.route('/', methods=['POST', 'GET'])
def index():
    """Website home page """
    if request.method == 'POST':
        measure()
    #loaded=True
    return send_from_directory('templates', 'index.html')
    #render_template('index.html')


#@APP.route('/measure')
def measure():
    """Runs in response to measure button being presssed"""
    #usr = request.form['nm']
    if 'measure' in request.form:
        print 'Measure button pushed'
        print request.form
        lights = threading.Thread(name='firethelights', target=firethelights)
        runner = threading.Thread(name='runmecall', target=runmecall)
        runner.start()
        lights.start()
        #firethelights()
	#os.system('sudo /home/pi/flask-video-streaming-v1.5/RunMe.sh')
	#os.system('sudo python /home/pi/rpi_ws281x/python/examples/neopixel_args.py '+)
	#os.system('ls ../e2ye_test')
        #os.system('/home/pi/kapzdircopy/CCodeVid4')
    elif 'display' in request.form:
        print 'Display button pushed'
        os.system('ls')
    else:
        print 'Alternative Case Chosen'
        #session['arrayObject'] = request.form.getlist('arrayObject[][]')
        preparethelights(request.json)
    print 'Measuring pupil please wait'
    return 'Measuring... please wait'

def runmecall():
    """calls the 'RunMe.sh script"""
    os.system('sudo /home/pi/flask-video-streaming-v1.5/RunMe.sh')

@APP.route('/video_feed')
def video_feed():
    """Video streaming route. Put this in the src attribute of an img tag."""
    return Response(gen(Camera()),
                    mimetype='multipart/x-mixed-replace; boundary=frame')
def gen(camera):
    """Video streaming generator function."""
    #time.sleep(3)
    while True:
        frame = camera.get_frame()
        yield (b'--frame\r\n'
               b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')

def hextorgb(value):
    """Converts from NEX value to RGB"""
    colrgb = tuple(int(value[i:i+2], 16) for i in (0, 2, 4))
    print('RGB =', colrgb)
    return colrgb

def firethelights():
    """Fires up the lights using a modified neopixel.py method"""
    for i in enumerate(PROTOCOL):
        elem = []
        elem = PROTOCOL[i]
        colsend = elem[0]
        timer = elem[1]
        commandstring = "sudo python /home/pi/rpi_ws281x/python/examples/neopixel_args.py "
        commandstring = commandstring+str(colsend[1])+" "+str(colsend[0])+" "+str(colsend[2])+" "
        os.system(commandstring+str(timer))
    os.system(commandstring+"0 0 0 1")
    print "End of Protocol"

def preparethelights(value):
    """Prepares the lights for firing"""
    print "These shouldn't be empty ---> "+str(TIME)+" and "+str(COLOR)
    stringvals = value
    global TIME
    TIME = None
    global COLOR
    COLOR = None
    global TUB
    TUB = None
    global PROTOCOL
    PROTOCOL = []
    print "These should be empty ---> "+str(TIME)+" and "+str(COLOR)
    for stringvalue in stringvals:
        TUB = str(stringvalue)
        print TUB
        COLOR = str(TUB[TUB.index('#')+1:TUB.index('#')+7])
        timeholder = str(TUB[TUB.index('e')+3:len(TUB)-1])
        TIME = re.sub("[^0-9.]", "", timeholder)
        rgbcol = hextorgb(COLOR)
        print COLOR+' '+TIME
        PROTOCOL.append([rgbcol, TIME])
    print PROTOCOL

if __name__ == '__main__':
    """This script instantiates the webserver app for the OpenPupil server"""
    APP.run(host='192.168.42.1', port=5000, debug=True)
    #APP.run(host='0.0.0.0')
