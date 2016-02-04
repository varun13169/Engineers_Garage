#Swapping Workspace in Ubuntu using Accelerometer and Python Script

##Requirements:
* Arduino with Atmega328p<br>
* Accelerometer ADXL335<br>
* Ubuntu 14.04 and Python 2.7 on your machine<br>
* Python libraries [Pyserial], subprocess and sys<br>
* Wmctrl installed on your ubuntu, use ”sudo apt-get install wmctrl”<br> 

##Summary:
In this project I’ll demonstrate swapping of workspace in ubuntu using accelerometer and python script. I am using [wmctrl] command that will take arguments according to the accelerometer values.<br>
On hardware level this project is similar to [Controlling Mouse Pointer using Python Script and Accelerometer].<br>
Python libraries that are being used are [Pyserial], subprocess and sys. Pyserial is used to communicate between arduino and my machine. Subprocess is used to execute bash commands in python script and sys is used to exit program using try and except block.<br>
[Pyserial] is a freely available non-standard library that is easy to install, just like any non-standard library.
Accelerometer that I’m using is ADXL335, it’s a triple axis accelerometer.<br>


##Project's Video:
[https://www.youtube.com/watch?v=Et3rpa4WQI8]

##Circuit Diagram:
![alt text][circuit diagram]


##Project Images
![alt text][Image_1]
![alt text][Image_2]
![alt text][Image_3]


##Description:

###How I am uploading code into arduino:
```sh
$ f = <source_code’s_file_name>
$ avr-gcc -g -mmcu=atmega328p -Wall -Os $(f).c -o $(f).elf
$ avr-objcopy -j .text -j .data -O ihex $(f).elf $(f).hex
$ sudo avrdude -F  -V -c arduino -p m328p  -P /dev/ttyUSB* -b 57600 -e -U flash:w:$(f).hex
```
Just type these four commands, in the same order, in your terminal and remember to put the source code’s filename in variable “f”. These command are for Linux users only.<br>
    First command stores the filename in variable “f”, second command is used to convert source code to .elf file, third command is used to convert that .elf file to .hex file which can be uploaded on atmega328p, fourth command is used to upload that .hex file.<br>


###Little bit about accelerometer being used:
I’m using adxl335 it’s a triple axis accelerometer. It can measure acceleration with a minimum full scale range of +-3g. It can used to measure tilt by measuring static acceleration of gravity or it can measure impact from shock and vibration by measuring dynamic acceleration.<br>
For more details and knowledge you can always look up adxl335 [datasheet].<br>

###Explanation of Source Code:

This program is an application of ADC and serial communication.<br>
I already did explain ADC [here], check it before reading this article.<br>
There are few changes that I made in setup_adc() function and ISR() block.<br>

In setup_adc() function I set the MUX1 bit in ADMUX register in order to start the conversion of value at PORTC2.<br>
In ISR() block, I first store 10-bit value from ADC in a variable. Then check four bits in ADMUX, starting from LSB, depending on these four bits I decide whether 10-bit value is for x,y,z axis.<br>
Then I set last four bits in ADMUX for next conversion.<br>

After that a workspace() function is called.<br>
It takes no argument but uses two globally defined variables viz. xRaw and yRaw.<br>
As I’m using four workspaces, so the values of xRaw and yRaw will decide whether to swap to workspace1, workspace2, workspace3 or workspace4.<br>
	
I’m using uartLibrary.h to send readings from accelerometer to my laptop using serial communication. I build this library referring this [article] . After including this library I can use printf() function from stdio.h to send strings from Atmega358p to my laptop.<br>

For detailed information please check the Source Code it’s very well documented.<br>



###Explanation of Python Script:
I’m using three libraries [Pyserial], subprocess and sys. Only [Pyserial] is the one that is not preinstalled with python2.7 but its freely available and very easy to install.<br>
First I created an object “ser” of “Serial” class and gave two arguments in it<br>
1. Serial Port: In my case it is '/dev/ttyUSB1'<br>
2. Baud rate: I my case it’s 9600<br>

Then I created a try and except block to check whether [wmctrl] is installed on your machine or not. If not it will display the warning and exit the program.<br>
Then in an infinite loop I put a try & except block because initially trash values are send from atmega328p.<br>
In try block I read data that is being send over serial port then break it and convert it to integer and store it in a list. Then save the command in a variable(bashCommand)  accordingly.<br>
Then command which is stored in that variable(bashCommand) is executed.<br>
Then I print these values on terminal for debugging purposes.<br>
For detailed information please check the Python Script it’s well documented.<br>


###Explanation of Circuit:
As can be seen in images, my accelerometer module don't have a header pin for ST, and all other i/o pins are in straight line. So instead of using a breadboard for connections I simply placed accelerometer on Analog pins of Arduino which maps to PORTC on atmega328p.<br>
For Vcc and GND I declared PORTC1 and PORTC5 as output and pulled down PORTC1 for GND, pulled up PORTC5 for Vcc.<br>
Now I can simply measure acceleration from x,y,z axis on PORTC2,3,4 respectively.<br>




##Getting started with this Project
There are three files:<br>
1. main.c contains the source code for atmega328p side of this application.<br>
2. uartLibrary.h contains definition of all the functions necessary for serial communication.<br>
3. python_serial.py it reads data from serial port and controls the mouse pointer.<br>

Place main.c and uartLibrary.h in same directory, and upload the code to atmega328p.<br>
Now, run the python script and BAAMMM!! you are ready to go. Just move accelerometer and accordingly your workspace will swap.<br>




##Published on Engineer's Garage
[http://www.engineersgarage.com/contribution/swapping-workspace-ubuntu-using-accelerometer-and-python-script]

[Pyserial]: http://pyserial.sourceforge.net/
[datasheet]: https://www.sparkfun.com/datasheets/Components/SMD/adxl335.pdf
[Controlling Mouse Pointer using Python Script and Accelerometer]: https://github.com/varun13169/Engineers_Garage/tree/master/Controlling%20Mouse%20Pointer%20using%20Python%20Script%20and%20Accelerometer
[here]: https://github.com/varun13169/Engineers_Garage/tree/master/ADC%20in%20Atmega328p
[article]: http://www.appelsiini.net/2011/simple-usart-with-avr-libc

[wmctrl]: http://askubuntu.com/questions/41093/is-there-a-command-to-go-a-specific-workspace

[https://www.youtube.com/watch?v=Et3rpa4WQI8]: https://www.youtube.com/watch?v=Et3rpa4WQI8

[circuit diagram]: https://github.com/varun13169/Engineers_Garage/blob/master/Swapping%20Workspace%20in%20Ubuntu%20using%20Accelerometer%20and%20Python%20Script/circuit%20diagram.jpg "circuit diagram"

[Image_1]: https://github.com/varun13169/Engineers_Garage/blob/master/Swapping%20Workspace%20in%20Ubuntu%20using%20Accelerometer%20and%20Python%20Script/Project_image001.jpg "Image_1"
[Image_2]: https://github.com/varun13169/Engineers_Garage/blob/master/Swapping%20Workspace%20in%20Ubuntu%20using%20Accelerometer%20and%20Python%20Script/Project_image002.jpg "Image_2"
[Image_3]: https://github.com/varun13169/Engineers_Garage/blob/master/Swapping%20Workspace%20in%20Ubuntu%20using%20Accelerometer%20and%20Python%20Script/Project_image003.jpg "Image_3"

[http://www.engineersgarage.com/contribution/swapping-workspace-ubuntu-using-accelerometer-and-python-script]: http://www.engineersgarage.com/contribution/swapping-workspace-ubuntu-using-accelerometer-and-python-script
