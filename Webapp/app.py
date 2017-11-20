
#!/usr/bin/env python
import time
from flask import Flask, render_template, Response, request, send_from_directory
import os
import json
import re
import subprocess
import threading

# emulated camera
#from camera import Camera

# Raspberry Pi camera module (requires picamera package)
from camera_pi import Camera

app = Flask(__name__, static_url_path='')
protocol = 0
time = 2
color = 000033
tub = 002233

        
##global loaded=False
##loaded=None
@app.route('/', methods=['POST', 'GET'])
def index():
    """Video streaming home page."""
    if request.method == 'POST':
        measure()
    #loaded=True

    return send_from_directory('templates','index.html')
    #render_template('index.html')


#@app.route('/measure')
def measure():
    #usr = request.form['nm']
    if 'measure' in request.form:
        print('Measure button pushed')
        print(request.form)
        lights = threading.Thread(name='fireTheLights', target=fireTheLights)
        runner = threading.Thread(name='runmecall', target=runmecall)
        runner.start()
        lights.start()
##       fireTheLights()
        
##        os.system('sudo /home/pi/flask-video-streaming-v1.5/RunMe.sh')
        #os.system('sudo python /home/pi/rpi_ws281x/python/examples/neopixel_args.py '+)
        #os.system('ls ../e2ye_test')
        #os.system('/home/pi/kapzdircopy/CCodeVid4')
    elif 'display' in request.form:
        print('Display button pushed')
        os.system('ls')
    else:
        print('Alternative Case Chosen')
        #session['arrayObject'] = request.form.getlist('arrayObject[][]')
        prepareTheLights(request.json)
        
    print('Measuring pupil please wait')
    return 'Measuring... please wait'

def runmecall():
    os.system('sudo /home/pi/flask-video-streaming-v1.5/RunMe.sh')

@app.route('/video_feed')
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
	colrgb = tuple(int(value[i:i+2], 16) for i in (0, 2 ,4))
	print('RGB =', colrgb)
	return colrgb

def fireTheLights():
    for i in range(len(protocol)):
        elem = []
        elem = protocol[i]
        colsend = elem[0]
        timer = elem[1]
        os.system("sudo python /home/pi/rpi_ws281x/python/examples/neopixel_args.py "+str(colsend[1])+" "+str(colsend[0])+" "+str(colsend[2])+" "+str(timer))
    os.system("sudo python /home/pi/rpi_ws281x/python/examples/neopixel_args.py 0 0 0 1")
    print("End of Protocol")
    
    
def prepareTheLights(value):
        print("These shouldn't be empty ---> "+str(time)+" and "+str(color))
	stringvals = value
	global time
	time = None
	global color
	color = None
	global tub
	tub = None
	global protocol
	protocol = []
        print("These should be empty ---> "+str(time)+" and "+str(color))
##        print("These should be empty ---> "+time+" and "+color)
	for x in stringvals:
		tub = str(x)
		print(tub)
		color = str(tub[tub.index('#')+1:tub.index('#')+7])
		timeholder = str(tub[tub.index('e')+3:len(tub)-1])	
		time = re.sub("[^0-9.]", "",timeholder)	
		rgbcol = hextorgb(color)
		print(color+' '+time)
		protocol.append([rgbcol, time])
        print(protocol)

if __name__ == '__main__':
    app.run(host='192.168.42.1',port=5000, debug=True)
#    app.run(host='0.0.0.0')


