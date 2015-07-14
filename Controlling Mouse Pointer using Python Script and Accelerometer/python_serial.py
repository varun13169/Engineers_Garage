##################################################################################################################################
#                                                       varun13169                                                               #
##################################################################################################################################

import serial # http://pyserial.sourceforge.net/ , Version: 2.7
import autopy # http://autopy.org , Version: 0.51

ser = serial.Serial('/dev/ttyUSB0',9600) # This is for Linux <ubuntu> for Windows select the respective COM port

# My screen's resolution in pixels,
# you might want to change it.
# 1365x767


while(1):
	try:
		accelerometerReading = map(int,ser.readline().split())
		autopy.mouse.move(accelerometerReading[1],accelerometerReading[0])
		print accelerometerReading
	
	except:
		None

############################################################# END ##################################################################
