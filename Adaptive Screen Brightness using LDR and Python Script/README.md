#Adaptive Screen Brightness using LDR and Python script

##Requirements:
* Arduino with Atmega328p
* LDR
* Python 2.7 on your machine
* Python libraries: [pyserial]


##Summary:
Every wondered how useful is the automatic brightness feature on phones, quickly adapting screen’s brightness according to the surrounding light intensity.<br>
In this project I try to create something similar for any PC or Laptop running on Linux(preferably Ubuntu 14.04).<br>
My goal was to keep it cheap and simple as much as possible.<br>
So to make a prototype of it I used LDR to measure light intensity and an arduino communicate with my machine. On my machine I used a python script  to communicate over USB with arduino and to edit the file which is responsible for the brightness of screen.<br>
This project cost around Rs 300 just because of microcontroller that is being used(needless to say it’s a prototype).<br>
It has got very high utility specially for PC users.<br>
To get more detailed information on controlling brightness using terminal, you can checkout this [link].<br>
And to get more detailed references on atmega328p you can checkout [Atmega328p documentation].<br>


##Project's Video:
[https://www.youtube.com/watch?v=n7Pn08Q-GM8]

##Circuit Diagram:
![alt text][circuit diagram]


##Project Images
![alt text][Image_1]
![alt text][Image_2]


##Description:

###How I am uploading code into arduino
Download and install AVR toolchain, for Linux [avr­libc] and for windows [winAVR].<br>
Then, just type these three commands, in the same order, on your terminal / cmd.

```sh
$ avr-gcc -g -mmcu=atmega328p -Wall -Os main.c -o main.elf
$ avr-objcopy -j .text -j .data -O ihex main.elf main.hex
$ sudo avrdude -F  -V -c arduino -p m328p  -P /dev/ttyUSB* -b 57600 -e -U flash:w:main.hex
```

First command is used to convert source code to .elf file, second command is used to convert that .elf file to .hex file which can be uploaded on atmega328p, third command is used to upload that .hex file.


###Little bit about LDR that is being used
LDR stands for Light Dependent Resistor. It’s resistance has an inverse relationship with luminous intensity, ie, its resistance tends to decrease with increase in light intensity. Generally, it has very high resistance somewhere around 1000 Kohms but when light falls on it, its resistance decreases dramatically to few hundred ohms.<br>
LDR is a very cheap device which finds its way in many of our day to day applications.<br>

###Explaination of Source Code
This program is an application of ADC and serial communication.<br>
I already did explain ADC [here], check it before reading this article.<br>
There are few changes that I made in setup_adc() function and ISR() block.<br>
In setup_adc() function I set the MUX1 bit in ADMUX register in order to start the conversion of value at PORTC2.<br>

In ISR() block, I first store 10-bit value from ADC in a variable(ldrValue). Then using conditional statements I map “ldrValue” to three levels of brightness:<br>
a. minimum_brightness = 500
b. medium_brightness = 2500
c. maximum_brightness = 4880
*You might need to change them according to your machine.<br>

I’m using uartLibrary.h to send brightness value and ldr value to my laptop using serial communication. I build this library referring this [article]. After including this library I can use printf() function from stdio.h to send strings from atmega328p to my laptop.<br>

For detailed information please check the Source Code it’s very well documented.<br>


###Explanation of Python Script
I’m using [pyserial]  libraries for serial communication, it’s freely available.<br>
Python script need root permission to run properly, else it will display an error message and exit.<br>

Once it gets the root permission it creates an object “ser” of “Serial” class and take two arguments in it:<br>
a. Serial Port: In my case it is '/dev/ttyUSB0'
b. Baud rate: I my case it is 9600
then, it sets the file path in a variable(path).<br>
*You might need to edit them according to your machine.<br>

Then in an infinite loop I put a try & except block Just to take care of initial garbage values.<br>
In try block, a variable(value) stores the list of two strings one is the brightness value other is the ldr value.<br>
After that it opens the file given in “path” variable in write mode and writes the brightness value in it, then it saves and close the file.<br>
And for debugging purpose, it prints the list with brightness and ldr value.<br>

For more information, you can also check this link on [changing brightness through terminal].<br>


###Explanation of Circuit
Circuit is fairly simple, as can be seen in image and circuit diagram, I build a potential divider using a 330 ohm resistor and LDR.<br>
One terminal of LDR is connected to PORTC1 and other to PORTC2, PORTC1 is pulled up to provide Vcc, similar thing is done with resistor, one terminal is connected to PORTC2 and other one to PORTC3, PORTC3 is pulled down to provide Gnd.<br>
Analog values are read at PORTC2, which is the junction of resistor and LDR.<br>


###Getting started with this Project:
There are three files:
1. main.c contains the source code for atmega328p side of this application.
2. uartLibrary.h contains definition of all the functions necessary for serial communication
3. python_serial.py it reads data from serial port and controls the mouse pointer

Make nesseary changes in main.c and python_serial.py according to your machine and LDR.
Place main.c and uartLibrary.h in same directory, and upload the code to atmega328p.<br>
Now, run the python script with root permission and BAAMMM!! you are ready to go. Just cover LDR with your hand and brightness of your screen will decrease or put a flashlight on LDR and brightness will increase.<br>


##Published on Engineer's Garage
[http://www.engineersgarage.com/contribution/adaptive-screen-brightness-using-ldr-and-python-script]


[pyserial]: http://pyserial.sourceforge.net/
[link]: http://askubuntu.com/questions/56155/how-can-i-change-brightness-through-terminal
[Atmega328p documentation]: http://www.atmel.com/Images/doc8161.pdf

[https://www.youtube.com/watch?v=n7Pn08Q-GM8]: https://www.youtube.com/watch?v=n7Pn08Q-GM8

[circuit diagram]:  https://github.com/varun13169/Engineers_Garage/blob/master/Adaptive%20Screen%20Brightness%20using%20LDR%20and%20Python%20Script/cicuit%20diagram.jpg
[Image_1]:  https://github.com/varun13169/Engineers_Garage/blob/master/Adaptive%20Screen%20Brightness%20using%20LDR%20and%20Python%20Script/Project_image001.jpg
[Image_2]:  https://github.com/varun13169/Engineers_Garage/blob/master/Adaptive%20Screen%20Brightness%20using%20LDR%20and%20Python%20Script/Project_image002.jpg


[here]: https://github.com/varun13169/Engineers_Garage/tree/master/ADC%20in%20Atmega328p
[article]: http://www.appelsiini.net/2011/simple-usart-with-avr-libc
[changing brightness through terminal]: http://askubuntu.com/questions/56155/how-can-i-change-brightness-through-terminal
[http://www.engineersgarage.com/contribution/adaptive-screen-brightness-using-ldr-and-python-script]: http://www.engineersgarage.com/contribution/adaptive-screen-brightness-using-ldr-and-python-script














