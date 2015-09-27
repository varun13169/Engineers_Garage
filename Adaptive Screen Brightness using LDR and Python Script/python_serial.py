##################################################################################################################################
#                                                       varun13169                                                               #
##################################################################################################################################

import serial # http://pyserial.sourceforge.net/ , Version: 2.7
import sys

ser = serial.Serial('/dev/ttyUSB0',9600) # This is for Linux <ubuntu> for Windows select the respective COM port

path='/sys/class/backlight/intel_backlight/brightness' # This is the path to the file from where I can adjust the brightness
# you can also check this link for more information:
# http://askubuntu.com/questions/56155/how-can-i-change-brightness-through-terminal



while(1):
	try:
		value = map(str,ser.readline().split())
		f = open(path,'w')       # Open the file
		f.write(value[0])        # Edit it by writing in the value
		f.close()                # Save it by closing it
		print value              # prints the list for debugging purpose
	
	except:
		None
		# Just to take care of initial garbage values

		
############################################################# END ##################################################################
