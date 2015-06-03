#ADC in Atmega328p

##Requirements:
* Bread Board
* Arduino Uno with atmega328p
* LDR
* NTC
* Two LEDs
* Jumper Wires


##Summary:
I made this to get power and control of every register using AVR-C and the ease of Arduino’s premade circuit along with FTDI chip. I used few simple commands to compile and upload the AVR-C code on my Arduino. By using Arduino I didn’t had worry about FTDI chip, reference for ADC voltage and other peripheral circuitry and by using AVR-C I had control over each and every register which isn’t possible while working with Arduino IDE.

This circuit demonstrate the working of ADC in atmega328p using interrupts, using two different kinds of sensors one is LDR it’s resistance decrease with increase in light intensity other is NTC it’s resistance decreases with increase in temperature.

My arduino is equipped with atmega328p, to get port mapping you can refer to Arduino [Port Manipulation] , this is reference of atmega168, newer chip atmega328p follows the same pin out of atmega168.

For more detailed information and references you can checkout datasheet of Atmega328p.
[Atmega328p datasheet]


##Project's Video
[https://www.youtube.com/watch?v=a2v7ayJu-cU&feature=youtu.be]

##Circuit Diagram:
![alt text][circuit diagram]


##FLOW CHART FOR THIS PROGRAM:
![alt text][flow chart]

##Description:

###How I am uploading code into arduino:
```sh
$ f = <source_code’s_file_name>
$ avr-gcc -g -mmcu=atmega328p -Wall -Os $(f).c -o $(f).elf
$ avr-objcopy -j .text -j .data -O ihex $(f).elf $(f).hex
$ sudo avrdude -F  -V -c arduino -p m328  -P /dev/ttyUSB* -b 57600 -e -U flash:w:$(f).hex
```
Just type these four commands, in the same order, in your terminal and remember to put the source code’s file name in variable “f”. These command are for Linux users only.
First command stores the file name in variable “f”, second command is used to convert source code to .elf file, third command is used to convert that .elf file to .hex file which can be uploaded on atmega328p, fourth command is used to upload that .hex file.


###Little bit of description of registers being used:
|            |      |      |       |   ADCSRA   |      |       |       |       |
|:----------------:|:----:|:----:|:-----:|:----:|:----:|:-----:|:-----:|:-----:|
| Bit              |   0  |   1  |   2   |   3  |   4  |   5   |   6   |   7   |
| 0x7A             | ADEN | ADSC | ADATE | ADIF | ADIE | ADPS2 | ADPS1 | ADPS0 |
| Initial Value    |   0  |   0  |   0   |   0  |   0  |   0   |   0   |   0   |


* Bit 7 – ADEN: ADC Enable 
Writing this bit to one enables the ADC. By writing it to zero, the ADC is turned off. Turning the ADC off while a conversion is in progress, will terminate this conversion.
* Bit 6 – ADSC: ADC Start Conversion
In Single Conversion mode, write this bit to one to start each conversion. 
* Bit 5 – ADATE: ADC Auto Trigger Enable 
When this bit is written to one, Auto Triggering of the ADC is enabled. The ADC will start a conversion on a positive edge of the selected trigger signal.
* Bit 4 – ADIF: ADC Interrupt Flag 
This bit is set when an ADC conversion completes and the Data Registers are updated.
* Bit 3 – ADIE: ADC Interrupt Enable 
When this bit is  written to one and the I-bit in SREG is set, the ADC Conversion Complete Interrupt is activated.
* Bits 2:0 – ADPS2:0: ADC Prescaler Select Bits 
These bits determine the division factor between the system clock frequency and the input clock to the ADC.


|            |      |      |       |   ADMUX    |      |       |       |       |
|:----------------:|:----:|:----:|:-----:|:----:|:----:|:-----:|:-----:|:-----:|
| Bit              |   0  |   1  |   2   |   3  |   4  |   5   |   6   |   7   |
| 0x7A             |REFS1 |REFS0 | ADLAR |   -  | MUX3 | MUX2  | MUX1  | MUX0  |
| Initial Value    |   0  |   0  |   0   |   0  |   0  |   0   |   0   |   0   |


* Bit 7 – ADEN: ADC Enable 
Writing this bit to one enables the ADC. By writing it to zero, the ADC is turned off. Turning the ADC off while a conversion is in progress, will terminate this conversion.
* Bit 6 – ADSC: ADC Start Conversion
In Single Conversion mode, write this bit to one to start each conversion. 
* Bit 5 – ADATE: ADC Auto Trigger Enable 
When this bit is written to one, Auto Triggering of the ADC is enabled. The ADC will start a conversion on a positive edge of the selected trigger signal.
* Bit 4 – ADIF: ADC Interrupt Flag 
This bit is set when an ADC conversion completes and the Data Registers are updated.
* Bit 3 – ADIE: ADC Interrupt Enable 
When this bit is  written to one and the I-bit in SREG is set, the ADC Conversion Complete Interrupt is activated.
* Bits 2:0 – ADPS2:0: ADC Prescaler Select Bits 
These bits determine the division factor between the system clock frequency and the input clock to the ADC.



###Explanation of code:

After defining appropriate clock frequency (F_CPU=16,000,000)and including essential libraries &lt;avr/io.h&gt;,&lt;util/delay.h&gt;,&lt;avr/interrupt.h&gt;.
I made a function setup_adc() which setup configuration of ADC.This function writes 11001111 in register ADCSRA and 0110000 in register ADMUX.

|                   |      |      |       |   ADCSRA   |      |       |       |       |
|:-----------------------:|:----:|:----:|:-----:|:----:|:----:|:-----:|:-----:|:-----:|
| 0x7A                    | ADEN | ADSC | ADATE | ADIF | ADIE | ADPS2 | ADPS1 | ADPS0 |
| Value after Setup_adc() |   1  |   1  |   0   |   0  |   1  |   1   |   1   |   1   |


According to data sheet in order to use 10bit ADC, I should set ADC frequency 
between 50KHz-200KHz, according to this data my pre-scalar value must be in the range of 
80-320 and the only available value in this range is 128. 
* ADEN bit enables ADC
* ADPS2 , ADPS1 , ADPS0 sets a prescaler of 128 ,ie, now ADC works at a frequency of 125KHz
*frequency of ADC= 1,60,00,000/128 = 125KHz*
* ADIE enables ADC interrupt
* ADSC it starts the conversion


|                   |      |      |       |   ADMUX    |      |       |       |       |
|:-----------------------:|:----:|:----:|:-----:|:----:|:----:|:-----:|:-----:|:-----:|
| 0x7A                    |REFS1 |REFS0 | ADLAR |   -  | MUX3 | MUX2  | MUX1  | MUX0  |
| Value after Setup_adc() |   0  |   1  |   1   |   0  |   0  |   0   |   0   |   0   |

* ADLAR for left adjusted result
* REFS0=1 and REFS1=0 to use Vcc as reference voltage

In main() function I set the value 00110000 in DDRD(Direction Register for Port D), ie, defining Pin 5 and 7 as output. Then iI called sei() which enabled global interrupt  by setting the I bit in status register (SREG), its a build in function in &lt;avr/interrupt.h&gt; library.
    Then setup_adc() function is called after which an infinite while loop is started.

Last part include the code which has to be executed after every ADC conversion,ie whenever an interrupt is generated. This code goes into ISR() block and respective interrupt vector is passed an argument(in this case ADC_vect).
    In ISR(), I store the 10-bit result in variable adc_ten_bit_value by simple manipulation as the result is left adjusted.
    I check values of LDR and NTC alternatively after every conversion ,ie, value of mux3, mux2, mux1, mux0 in ADMUX must be changed after every conversion, in case of my source code toggling of value present in mux0 after every conversion will do the work, its record is kept in variable value_of_mux0.
    Then simple conditional statements are placed for manipulation of output ports.



###Explanation of circuit and hardware components:

As can be seen in circuit diagram two potential dividers are made one with LDR and 1kohm resistor and other with NTC and 1kohm resistor. Wires from the junction of LDR and register is feed to Arduino PC1(pinA1) and wires from the junction of NTC and register is feed to Arduino PC0(pinA0), ie, both pins will measure potential drop across the sensors.
Now, I took two LEDs and connected their cathode to GND and anode of one LED to PD5(pin5) and anode of other to PD7(pin7).
LED connected to PD5(pin5) will glow when value of LDR is less than 10(critical value), similarly LED connected to PD7(pin7) will glow when the value of NTC is greater than 133(critical value).



[Port Manipulation]: http://www.arduino.cc/en/Reference/PortManipulation
[Atmega328p datasheet]: http://www.atmel.com/Images/doc8161.pdf
[https://www.youtube.com/watch?v=a2v7ayJu-cU&feature=youtu.be]: https://www.youtube.com/watch?v=a2v7ayJu-cU&feature=youtu.be
[circuit diagram]: https://github.com/varun13169/Engineers_Garage/blob/master/ADC%20in%20Atmega328p/circuit%20diagram.jpg "circuit diagram"
[flow chart]: https://github.com/varun13169/Engineers_Garage/blob/master/ADC%20in%20Atmega328p/flow%20chart.jpg "flow chart"



