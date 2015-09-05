#External and Pin Change Interrupts in Atmega328p: Reaction Time Game

##Requirements:
* Arduino with Atmega328p
* Jumper wires
* Bread Board
* Push Buttons
* 1k Resistors
* LEDs


##Summary:
This game test reaction time of two players, and declare the fastest one as winner. To do this I am using external interrupts and pin change interrupts in atmega328p. It gives four chance to each play, time of each chance is summed up and then player with minimum time is declared as the winner.<br>
For the demo purpose, I’ll be using pseudo random function in it, just to keep track.<br>
This game has precision of 1ms and accuracy of about +/- 4ms.<br>
It also displays the concept of debouncing.<br>
This game’s main motive is to show the beauty of external interrupts over polling and to show the how to reduce debouncing effect using software modifications.<br>


##Project's Video:
[https://www.youtube.com/watch?v=fMYVjDvXV7Y]


##Circuit Diagram:
![alt text][circuit diagram]


##Project Images
![alt text][Image_1]
![alt text][Image_2]
![alt text][Image_3]

##Description:

###How I am uploading code into arduino
'''sh
$ f = <source_code’s_file_name>
$ h = <header_file_name>
$ avr-gcc -g -mmcu=atmega328p -Wall -Os $(h).c $(f).c -o $(f).elf
$ avr-objcopy -j .text -j .data -O ihex $(f).elf $(f).hex
$ sudo avrdude -F  -V -c arduino -p m328p  -P /dev/ttyUSB* -b 57600 -e -U flash:w:$(f).hex
 '''
    Just type these four commands, in the same order, in your terminal and remember to put the source code’s filename in variable “f” and header filename in variable “h”. These command are for Linux users only.<br>
    First command stores the filename in variable “f”, second command is used to convert source code to .elf file, third command is used to convert that .elf file to .hex file which can be uploaded on atmega328p, fourth command is used to upload that .hex file.<br>


###What are External Interrupts:
External interrupts are very useful to interact with physical world, because of its unpredictable nature.<br>
There are two ways of sensing data from different pins, one is polling other is using interrupts. Both polling and interrupts have pros and cons associated with them.<br>
In polling you check status of each and every pin in a sequential manner:<br>
pros:<br>
1) Everyone one gets a fair chance<br>
cons:<br>
1) Inefficient, can’t do some other activity in between, specially have to go and check<br>
2) Loss of data might occur in an unpredictable scenario.<br>

Whereas, in interrupts you let your microcontroller do some other important stuff and whenever an interrupt is generated you stop the normal working of microcontroller and change its behavior accordingly.<br>
pros:<br>
1) Efficient, can do some other work in between<br>
2) No loss of data<br>
cons:<br>
1) Extra resources on hardware level are required<br>



###Little bit of description about timer being used:



###What my project is:
My project is inspired from fastest finger first game.<br>
In which there are two players and both get four chances and reaction time of all four chances are summed up, one who have the minimum reaction time wins the game.<br>

Game starts with the display on LCD which reads “Reaction Time Game” and then “Push Button To Start”.<br>
When the push button is pressed, game starts in 3.5secs.<br>
Then one out of four LED glows Player1 is expected to press  corresponding button to that LED, time is recorded for the same, if Player1 presses another button that does not correspond to that specific LED than a penalty of 1000ms is imposed along with the recorded time.<br>
Score after each turn is displayed on LCD and this thing is repeated for four times.<br>
After that Player2 begins and same thing is repeated.<br>
Then score of both the players are compared and fastest one is declared winner.<br>
After around two seconds latter “Push Button To Play Again” is displayed on LCD.<br>



##Published on Engineer's Garage
[engine.com]



[https://www.youtube.com/watch?v=fMYVjDvXV7Y]: https://www.youtube.com/watch?v=fMYVjDvXV7Y

[circuit diagram]:  "circuit diagram"
[Image_1]:  "Image_1"
[Image_2]:  "Image_2"
[Image_3]:  "Image_3"
[engine.com]













