##################################################################################################################################
#                                                       varun13169                                                               #
##################################################################################################################################

import serial # http://pyserial.sourceforge.net/ , Version: 2.7
import subprocess
import sys


ser = serial.Serial('/dev/ttyUSB0',9600) # This is for Linux <ubuntu> for Windows select the respective COM port


try:
	bashCommand = "wmctrl -d"
	process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE)
	output = process.communicate()[0]
	print output
except:
	print '''The program 'wmctrl' is currently not installed. You can install it by typing:
sudo apt-get install wmctrl'''

	sys.exit()


while(1):
	try:
		
		readingFromArduino = map(int,ser.readline().split())
		
		if readingFromArduino[2]==1:
			bashCommand= 'wmctrl -o 0,0'
		if readingFromArduino[2]==2:
			bashCommand= 'wmctrl -o 1366,0'
		if readingFromArduino[2]==3:
			bashCommand= 'wmctrl -o 0,768'
		if readingFromArduino[2]==4:
			bashCommand= 'wmctrl -o 1366,768'
		else:
			None
		
		print readingFromArduino
		process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE)
		output = process.communicate()[0]
		
	
	except:
		#print 'Check Some error is there ......'
		None
		
############################################################# END ###########################################################		
