# NeoPixel library strandtest example
# Author: Elf Eldridge

# Direct port of the Arduino NeoPixel library strandtest example. 
# Flashes 2 neopixels specific colours for a set length of time
import time

from neopixel import *

# LED strip configuration:
LED_COUNT      = 2      # Number of LED pixels.
LED_PIN        = 18      # GPIO pin connected to the pixels (must support PWM!).
LED_FREQ_HZ    = 800000  # LED signal frequency in hertz (usually 800khz)
LED_DMA        = 5       # DMA channel to use for generating signal (try 5)
LED_BRIGHTNESS = 255     # Set to 0 for darkest and 255 for brightest
LED_INVERT     = False   # True to invert the signal (when using NPN transistor level shift)


# Define functions which animate LEDs in various ways.
def colorWipe(strip, color, wait_ms=50):
	"""Wipe color across display a pixel at a time."""
	for i in range(strip.numPixels()):
		strip.setPixelColor(i, color)
		strip.show()
		time.sleep(wait_ms/1000.0)

# Main program logic follows:
if __name__ == '__main__':
	# Create NeoPixel object with appropriate configuration.
	strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, LED_FREQ_HZ, LED_DMA, LED_INVERT, LED_BRIGHTNESS)
	# Intialize the library (must be called once before other functions).
	strip.begin()


	#colorWipe(strip, Color(255, 0, 0))  # Green wipe
        #colorWipe(strip, Color(0, 0, 255))  # Blue wipe
        #colorWipe(strip, Color(0, 255, 0))  # Red wipe

	print ('Intialising colour.')
	colorWipe(strip, Color(0, 0, 0))
	time.sleep(0.1)

	print('Testing White levels')
	#increasing 0.5 s white flashes
	for i in range(0,255, 20):
		print(i)
		colorWipe(strip, Color(i, i, i))
		time.sleep(0.5)
		colorWipe(strip, Color(0, 0, 0))
		time.sleep(0.5)

	print('Control Dark')
	#5s of dark
	colorWipe(strip, Color(0, 0, 0))
        time.sleep(5)

	#0.5s flash of red
	colorWipe(strip, Color(0, 255, 0))  # Red wipe
	time.sleep(0.5)
	
	print('Red Dark')
	#5s of dark
	colorWipe(strip, Color(0, 0, 0))
        time.sleep(5)

	#0.5s flash of blue
	colorWipe(strip, Color(0, 0, 255))  # Red wipe
        time.sleep(0.5)

	print('Blue Dark')
	#5s of dark
        colorWipe(strip, Color(0, 0, 0))
        time.sleep(5)

