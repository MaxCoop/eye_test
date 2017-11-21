"""
NeoPixel library strandtest example
Author: Elf Eldridge
Direct port of the Arduino NeoPixel library strandtest example. 
Flashes 2 neopixels specific colours for a set length of time
"""
import time
from neopixel import *

# LED strip configuration:
LED_COUNT = 18 # Number of LED pixels.
LED_PIN = 18 # GPIO pin connected to the pixels (must support PWM!).
LED_FREQ_HZ = 800000# LED signal frequency in hertz (usually 800khz)
LED_DMA = 5 # DMA channel to use for generating signal (try 5)
LED_BRIGHTNESS = 125 # Set to 0 for darkest and 255 for brightest
LED_INVERT = False # True to invert the signal (when using NPN transistor level shift)


# Define functions which animate LEDs in various ways.
def colorwipe(strip, color, wait_ms=1):
    """Wipe color across display a pixel at a time."""
    for k in range(strip.numPixels()):
        strip.setPixelColor(k, color)
        strip.show()
        time.sleep(wait_ms/1000.0)
        strip.setPixelColor(k, color)
        strip.show()
        time.sleep(wait_ms/1000.0)

# Main program logic follows:
if __name__ == '__main__':
	# Create NeoPixel object with appropriate configuration.
    STRIP = Adafruit_NeoPixel(LED_COUNT, LED_PIN, LED_FREQ_HZ, LED_DMA, LED_INVERT, LED_BRIGHTNESS)
	# Intialize the library (must be called once before other functions).
    STRIP.begin()
    
    #wait for use to place eye on device
    time.sleep(2.5)
    
    #time to between cycles at end
    NADAWAIT = 5 #Seconds
    
    REDON = 2#0.5
    BLUEON = 0.5#0.5
    NUMBEROFCYCLES = 1

	#setup number of cycles
    for i in range(0, NUMBEROFCYCLES, 1):
        print "Off for "+str(NADAWAIT)+" seconds" 
        #for i in range(10):
        colorwipe(STRIP, Color(0, 0, 0))
        time.sleep(NADAWAIT)
        #print("Red on for "+str(REDON)+" seconds")
        #colorwipe(STRIP, Color(0, 0, 255))
        #time.sleep(REDONon)
        print "Blue on for "+str(BLUEON)+" seconds" 
        colorwipe(STRIP, Color(0, 255, 0))
        time.sleep(BLUEON)
        print "Off for "+str(NADAWAIT)+" seconds" 
        #for i in range(10):
        colorwipe(STRIP, Color(0, 0, 0))
        time.sleep(NADAWAIT)

    print "All Neos off"
    #wait for 5 seconds
    colorwipe(STRIP, Color(0, 0, 0))
    time.sleep(NADAWAIT)