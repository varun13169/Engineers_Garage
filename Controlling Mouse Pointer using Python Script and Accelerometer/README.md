#Controlling Mouse Pointer using Python Script and Accelerometer

##Requirements:
* Arduino with Atmega328p
* Accelerometer ADXL335
* Python 2.7 on your machine
* Python libraries: [Pyserial] and [Autopy]

##Summary:
There are many ways of controlling mouse pointer using atmega328p, and I find using a python script and an arduino best and effective one because of the following reasons:
1. Python is a common language and comes pre-installed in almost all LINUX distros.
2. Using python script makes this project compatible to cross platforms, as no fancy software is needed.
3. Using an arduino saves me from the trouble that goes into making the whole circuit and then connecting it through a USB to TTL converter.

I’ll be using two non-standard libraries viz. Pyserial and Autopy both of them are freely available and easy to install, just like any non-standard library.<br>
Accelerometer that I’m using is ADXL335, it’s a triple axis accelerometer.


##Project's Video:
[https://www.youtube.com/watch?v=O0MqSM-0vxk]

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
For more details and knowledge you can always look up adxl335 [datasheet].
	
###Source Code:
This program is an application of ADC and serial communication.<br>
I already did explain ADC [here], check it before reading this article.<br>
There are few changes that I made in setup_adc() function and ISR() block.<br>

In setup_adc() function I set the MUX1 bit in ADMUX register in order to start the conversion of value at PORTC2.<br>
In ISR() block, I first store 10-bit value from ADC in a variable. Then check four bits in ADMUX, starting from LSB, depending on these four bits I decide whether 10-bit value is for x,y,z axis.<br>
Then I set last four bits in ADMUX for next conversion.<br>
After that a map_constaint() function is called. It is a combination of map() function and constraint function() available in Arduino IDE.<br>
It takes 5 arguments, first is the value to be mapped, second is the lowest value on original scale, third is highest value on original scale, fourth is lowest value on the secondary scale, fifth is highest value on the secondary scale.<br>
Then by using simple maths it linearly maps value from primary scale to secondary scale and then apply constraints on it with respect to the secondary scale.<br>

I’m using uartLibrary.h to send readings from accelerometer to my laptop using serial communication. I build this library referring this [article]. After including this library I can use printf() function from stdio.h to send strings from Atmega358p to my laptop.<br>
For detailed information please check the Source Code it’s well documented.<br>

###Explanation of Python Script:
I’m using two libraries [Pyserial] and [Autopy] both of them are freely available.<br>
First I created an object “ser” of “Serial” class and gave two arguments in it
1. Serial Port: In my case it is '/dev/ttyUSB1'
2. Baud rate: I my case it’s 9600

Then in an infinite loop I put a try & except block because initially trash values are send from atmega328p.<br> 
In try block I read data being send over serial port then break it and convert it to integer and store it in an array.<br>
Next I feed these values from array to autopy.mouse.move(), it takes two input 1st is width and 2nd is height of your screen both of them in pixels.<br>
Then I print these values on terminal for debugging purposes.<br>

###Explanation of Circuit:
As can be seen in images, my accelerometer module don't have a header pin for ST, and all other i/o pins are in straight line. So instead of using a breadboard for connections I simply placed accelerometer on Analog pins of Arduino which maps to PORTC on atmega328p.<br>
For Vcc and GND I declared PORTC1 and PORTC5 as output and pulled down PORTC1 for GND, pulled up PORTC5 for Vcc.<br>
Now I can simply measure acceleration from x,y,z axis on PORTC2,3,4 respectively.<br>




##Getting started with this Project
There are three files:
1. main.c contains the source code for atmega328p side of this application.
2. uartLibrary.h contains definition of all the functions necessary for serial communication
3. python_serial.py it reads data from serial port and controls the mouse pointer

Place main.c and uartLibrary.h in same directory, and upload the code to atmega328p.<br>
Now, run the python script and BAAMMM!! you are ready to go. Just move accelerometer and you pointer will start moving.<br>


[Pyserial]: http://pyserial.sourceforge.net/
[Autopy]: http://autopy.org
[datasheet]: https://www.sparkfun.com/datasheets/Components/SMD/adxl335.pdf
[here]: https://github.com/varun13169/Engineers_Garage/tree/master/ADC%20in%20Atmega328p
[article]: http://www.appelsiini.net/2011/simple-usart-with-avr-libc

[https://www.youtube.com/watch?v=O0MqSM-0vxk]: https://www.youtube.com/watch?v=O0MqSM-0vxk

[circuit diagram]: https://github.com/varun13169/Engineers_Garage/blob/master/Controlling%20Mouse%20Pointer%20using%20Python%20Script%20and%20Accelerometer/circuit%20diagram.jpg "circuit diagram"

[Image_1]: https://github.com/varun13169/Engineers_Garage/blob/master/Controlling%20Mouse%20Pointer%20using%20Python%20Script%20and%20Accelerometer/Project_image001.jpg "Image_1"
[Image_2]: https://github.com/varun13169/Engineers_Garage/blob/master/Controlling%20Mouse%20Pointer%20using%20Python%20Script%20and%20Accelerometer/Project_image002.jpg "Image_2"
[Image_3]: https://github.com/varun13169/Engineers_Garage/blob/master/Controlling%20Mouse%20Pointer%20using%20Python%20Script%20and%20Accelerometer/Project_image003.jpg "Image_3"









