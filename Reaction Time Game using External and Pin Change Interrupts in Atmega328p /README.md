#Reaction Time Game using External and Pin Change Interrupts in Atmega328p 

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


##What my project is about:
My project is inspired from fastest finger first game.<br>
In which there are two players and both get four chances and reaction time of all four chances are summed up, one who have the minimum reaction time wins the game.<br>

Game starts with the display on LCD which reads “Reaction Time Game” and then “Push Button To Start”.<br>
When the push button is pressed, game starts in 3.5secs.<br>
Then one out of four LED glows Player1 is expected to press  corresponding button to that LED, time is recorded for the same, if Player1 presses another button that does not correspond to that specific LED than a penalty of 1000ms is imposed along with the recorded time.<br>
Score after each turn is displayed on LCD and this thing is repeated for four times.<br>
After that Player2 begins and same thing is repeated.<br>
Then score of both the players are compared and fastest one is declared winner.<br>
After around two seconds latter “Push Button To Play Again” is displayed on LCD.<br>


##Project's Video:
[https://www.youtube.com/watch?v=fMYVjDvXV7Y]


##Circuit Diagram:
![alt text][circuit diagram]


##Project Images
![alt text][Image_1]
![alt text][Image_2]





##Description:


###How I am uploading code into arduino
```sh
$ f = <source_code’s_file_name>
$ h = <header_file_name>
$ avr-gcc -g -mmcu=atmega328p -Wall -Os $(h).c $(f).c -o $(f).elf
$ avr-objcopy -j .text -j .data -O ihex $(f).elf $(f).hex
$ sudo avrdude -F  -V -c arduino -p m328p  -P /dev/ttyUSB* -b 57600 -e -U flash:w:$(f).hex
```


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
<br>
<br>


###Little bit of description about registers that are being used:
![alt text][reg1]
* Bit 7..4 – Res: Reserved Bits<br>
These bits are unused bits in the ATmega48PA/88PA/168PA/328P, and will always read as zero.<br>
* Bit 3, 2 – ISC11, ISC10: Interrupt Sense Control 1 Bit 1 and Bit 0<br>
Used for Interrupt 1 Sense Control, check the table below<br>
* Bit 1, 0 – ISC01, ISC00: Interrupt Sense Control 0 Bit 1 and Bit 0<br>
Used for Interrupt 0 Sense Control, check the table below<br>

![alt text][reg2]
* Bit 7:2 – Reserved<br>
These bits are unused bits in the ATmega48A/PA/88A/PA/168A/PA/328/P, and will always read as zero.<br>
* Bit 1 – INT1: External Interrupt Request 1 Enable<br>
When the INT1 bit is set (one) and the I-bit in the Status Register (SREG) is set (one), the external pin interrupt is enabled.<br>
* Bit 0 – INT0: External Interrupt Request 0 Enable<br>
When the INT0 bit is set (one) and the I-bit in the Status Register (SREG) is set (one), the external pin interrupt is enabled.<br>

![alt text][reg3]
* Bit 7:3 – Reserved<br>
These bits are unused bits in the ATmega48A/PA/88A/PA/168A/PA/328/P, and will always read as zero.<br>
* Bit 2 – PCIE2: Pin Change Interrupt Enable 2<br>
When the PCIE2 bit is set (one) and the I-bit in the Status Register (SREG) is set (one), pin change interrupt 2 is enabled. Any change on any enabled PCINT[23:16] pin will cause an interrupt.<br>
* Bit 1 – PCIE1: Pin Change Interrupt Enable 1<br>
When the PCIE1 bit is set (one) and the I-bit in the Status Register (SREG) is set (one), pin change interrupt 1 is enabled. Any change on any enabled PCINT[14:8] pin will cause an interrupt.<br>
* Bit 0 – PCIE0: Pin Change Interrupt Enable 0<br>
When the PCIE0 bit is set (one) and the I-bit in the Status Register (SREG) is set (one), pin change interrupt 0 is enabled. Any change on any enabled PCINT[7:0] pin will cause an interrupt.<br>

![alt text][reg4]
* Bit 7 – Reserved<br>
This bit is an unused bit in the ATmega48A/PA/88A/PA/168A/PA/328/P, and will always read as zero.<br>
* Bit 6:0 – PCINT[14:8]: Pin Change Enable Mask 14...8<br>
Each PCINT[14:8]-bit selects whether pin change interrupt is enabled on the corresponding I/O pin. If PCINT[14:8] is set and the PCIE1 bit in PCICR is set, pin change interrupt is enabled on the corresponding I/O pin. If PCINT[14:8] is cleared, pin change interrupt on the corresponding I/O pin is disabled.<br>
<br>
<br>


##Published on Engineer's Garage
[http://www.engineersgarage.com/contribution/external-and-pin-change-interrupts-atmega328p-reaction-time-game]





[https://www.youtube.com/watch?v=fMYVjDvXV7Y]: https://www.youtube.com/watch?v=fMYVjDvXV7Y

[circuit diagram]: https://github.com/varun13169/Engineers_Garage/blob/master/External%20and%20Pin%20Change%20Interrupts%20in%20Atmega328p:%20Reaction%20Time%20Game/circuit%20diagram.jpg "circuit diagram"
[Image_1]: https://github.com/varun13169/Engineers_Garage/blob/master/External%20and%20Pin%20Change%20Interrupts%20in%20Atmega328p:%20Reaction%20Time%20Game/Project_image001.jpg "Image_1"
[Image_2]: https://github.com/varun13169/Engineers_Garage/blob/master/External%20and%20Pin%20Change%20Interrupts%20in%20Atmega328p:%20Reaction%20Time%20Game/Project_image002.jpg "Image_2"

[reg1]: https://github.com/varun13169/Engineers_Garage/blob/master/External%20and%20Pin%20Change%20Interrupts%20in%20Atmega328p:%20Reaction%20Time%20Game/Reg1.png
[reg2]: https://github.com/varun13169/Engineers_Garage/blob/master/External%20and%20Pin%20Change%20Interrupts%20in%20Atmega328p:%20Reaction%20Time%20Game/Reg2.png
[reg3]: https://github.com/varun13169/Engineers_Garage/blob/master/External%20and%20Pin%20Change%20Interrupts%20in%20Atmega328p:%20Reaction%20Time%20Game/Reg3.png
[reg4]: https://github.com/varun13169/Engineers_Garage/blob/master/External%20and%20Pin%20Change%20Interrupts%20in%20Atmega328p:%20Reaction%20Time%20Game/Reg4.png


[http://www.engineersgarage.com/contribution/external-and-pin-change-interrupts-atmega328p-reaction-time-game]: http://www.engineersgarage.com/contribution/external-and-pin-change-interrupts-atmega328p-reaction-time-game 













