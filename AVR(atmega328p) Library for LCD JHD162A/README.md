#AVR(atmega328p) Library for LCD JHD162A

##Requirements:
* Bread Board
* Arduino Uno with Atmega328p
* LCD JHD162A
* Push Button
* 1k Resistor
* Jumper Wires


##Summary:
Liquid Crystal Displays are important in projects where interaction with Human is involved. LCD JHD162A is a small LCD which can be used with atmega328p. It has 16 columns and 2 row, therefore 32 segments. Each segment is composed of 8 rows of 5 dots.<br>
     Although this module is very versatile and handy but it’s very tricky to use. Arduino IDE has a library which contain important functions to get this module up and running.<br>
    I wanted to build a library for Atmega328p which does almost similar functions as [LiquidCrystal Library] in Arduino IDE. Interfacing with LCD is a task in itself one has to learn and understand the working of LCD in order to use it even for a simple project.<br>
    This library don’t require any in depth knowledge of LCD JHD162A and it’s working.<br>
Just include lcd.h in your source code and you are ready to go.<br>



##Project's Video:
[https://www.youtube.com/watch?v=AQ7CQQZPDSY]

##Circuit Diagram:
![alt text][circuit diagram]


##Project Images
![alt text][Image_1]
![alt text][Image_2]



##Description:
###How I am uploading code into arduino:

```sh
f = <source_code’s_file_name>
h = <header_file_name>
avr-gcc -g -mmcu=atmega328p -Wall -Os $(h).c $(f).c -o $(f).elf
avr-objcopy -j .text -j .data -O ihex $(f).elf $(f).hex
sudo avrdude -F  -V -c arduino -p m328p  -P /dev/ttyUSB* -b 57600 -e -U flash:w:$(f).hex
```
Just type these four commands, in the same order, in your terminal and remember to put the source code’s filename in variable “f” and header filename in variable “h”. These command are for Linux users only.<br>
First command stores the filename in variable “f”, second command is used to convert source code to .elf file, third command is used to convert that .elf file to .hex file which can be uploaded on atmega328p, fourth command is used to upload that .hex file.<br>

###Interfacing LCD JHD162A:

So, LCD JHD162A can be used in either 8-bit mode or in 4-bit mode. As we are using Atmega328p, I prefer not to waste precious input/output pin on LCD, so I’ll be using 4-bit mode to interface with LCD. Although interfacing in 4-bit mode comes with a cost, cost of time. Same 8-bit data takes twice the time in 4-bit mode than in 8-bit mode but this difference in time is in milliseconds and  most of our application require more i/o pins over that millisecond difference.<br>

Input can be classified into two types:<br>
1. command: These are instructions given to LCD, to initialize and manipulate data.<br>
2. data: As the name suggest, this can be any thing which user wants to display.<br>

Both commands and data are of 8-bits, therefore, to complete a single transmission two 4-bit cycles are required.
To distinguish whether 1 byte of data is transmitted or 1 byte of command is being transmitted, one more input is used, that is Register Select bit. Whenever Register Select bit is set transmitted 8-bits are interpreted as data and whenever Register Select bit is cleared(not set)transmitted 8-bits are interpreted as commands.<br>
Now, LCD is lot slower than our microcontroller, therefore, we need to check whether lcd is free and can take input from our microcontroller, for this Read/Write bit is used. Whenever R/W bit is set we can read LCD busy status on pin D7, if D7 is High then LCD is busy in processing some stuff and if D7 is low then LCD is ready to accept new instructions or data, we can clear R/W bit to initialize writing process.<br>
&lt;--------------------------------------------------OR------------------------------------------&gt; <br>
As can be seen above usage R/W pin is very complex, what we can do is instead of reading LCD’s status we can permanently clear R/W bit (ie, connect R/W pin to ground) and give substantial amount of delay in which any instruction can be processed. In this way we are again compromising in terms of time but complexity of our code decreases with huge factor, with respect to the extra time (generally it's in microseconds).<br>
Again most of our applications don’t even require this amount of precision in terms time.<br>
We need to tell lcd whenever we want to transmit a command or data. This is done using enable bit. Whenever enable bit set, LCD is able to see the data present on data lines in our case data line is 4-bit wide.<br>


**So, now sequence of transmitting a 4-bit Data* will be:**<br>
1. Put the information on the Data* line<br>
2. Select whether its a command or data<br>
3. Tell LCD Data* is ready to read(by setting enable bit)<br>
4. Give sufficient amount of time to read<br>
5. Clear enable bit<br>
6. Give sufficient amount of time to process<br>

\*I have used Data* to represent  data+command combined<br>
For more information you can refer the [Datasheet] of JHD162A.<br>




##Explanation of Functions in this Library:
I tried to keep library similar to LiquidCrystal library in Arduino IDE. I included some function from my side too.<br>

1. command(): Takes in an 8-bit command breaks it in chunks of 4-bit and transmit it to LCD.<br>
2. data(): Takes in an 8-bit data(generally ASCII characters) breaks it in chunks of 4-bit and transmit it to LCD.<br>
3. start(): It initializes the LCD with most suitable configuration
	* LCD in 5x8 and 4-bit mode
	* Display ON cursor OFF
	* Increment cursor by one after every byte of data
	* Don't shift display after every byte of data
	* no auto scrolling
4. Send_A_String(): Takes a string that is to be displayed as an input, breaks it and then transmit each character using data(). **NOTE:-** maximum character in a string should be less than 16, after 16th character everything will be ignored.<br>
5. cut(): Works same as Send_A_String(), except maximum number of character is 32. After 16th character, 17th character starts from second row.<br>
6. Send_An_Integer(): Takes input an integer of long type, converts it into a string and then displays it on LCD. It use Send_A_String() for displaying.<br>
7. setCursor(): Indexing starts from 0. Therefore, 0<=row<=1 and 0<=column<=15. If arguments are outside the the specified range, then function will not work and ignore the values.<br>
8. clearScreen(): Clears the screen and returns cursor to (0,0) position.<br>
9. home(): Returns cursor to (0,0) position.<br>
10. cursor(): Shows cursor as an underscore.<br>
11. noCursor(): Hides the cursor.<br>
12. blink(): Shows cursor as a blinking black spot.<br>
13. noBlink(): Hides the cursor.<br>
14. display(): Turns ON the display with cursor OFF.<br>
15. noDisplay(): Turns display OFF.<br>
16. scrollDisplayLeft(): Scrolls the contents of the display(text and cursor) one space to the left.<br>
17. scrollDisplayRight(): Scrolls the contents of the display(text and cursor) one space to the right.<br>
18. autoscroll(): This causes each character output to the display to push previous characters over by one space in right to left direction.<br>
19. noAutoscroll(): Turns off automatic scrolling of the LCD.<br>
20. changeChar(): Takes input two arguments
	* 1st is a number between 0-7, which maps to seven base addresses
	* 2nd is an array of 8 integers, each integer is formed by 5 bits which determine the pixels in the row same as the index of that integer.

**NOTE:-** Before printing the character, one must set cursor else cursor won't get printed.<br>
To print Created Character, one can use data() function. Just pass a number between 0-7 as an argument in data() function.<br>

*Example:* To print value stored at zero<br>
data(0);        CORRECT<br>
data('0');      INCORRECT<br>


##Getting started with this Library:
There are three files:<br>
1. main.c contains the source code of your application(In this case this example).<br>
2. lcd.c contains definition of all the functions that are included in the library.<br>
3. lcd.h contains prototype of the functions in lcd.c.<br>
For my source code to work, one need to put all three file in same directory. You can modify it and put these three files anywhere you want.<br>
**Connections:**<br>
In this example i’ve added a push button as can be seen in circuit diagram, you can remove it and add anything depending on your application.<br>





[LiquidCrystal Library]: http://www.arduino.cc/en/Reference/LiquidCrystal
[Datasheet]: http://www.itron.com.cn/PDF_file/JHD162A%20SERIES.pdf
[https://www.youtube.com/watch?v=AQ7CQQZPDSY]: https://www.youtube.com/watch?v=AQ7CQQZPDSY

[circuit diagram]: "circuit diagram"

[Image_1]: "Image_1"
[Image_2]: "Image_2"




