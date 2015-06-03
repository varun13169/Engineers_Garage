/*****************************  Varun Kumar  *********************************/
#define F_CPU 16000000UL
#include<avr/io.h>
#include<util/delay.h>
#include<stdlib.h>
#include<string.h>
#include<avr/interrupt.h>
#include"lcd.h"

void timer();
int in_counter=0;  // keeps track on both the threads and resets when one complete cycle is over
int in_counter1=0; // keeps track on one cycle of thread1 and resets after one cycle of thread1 is over
int in_counter2=0; // keeps track on one cycle of thread2 and resets after one cycle of thread2 is over

int count1=0;
int count2=0;

int main(void)
{
    	DDRB = 0x03;          // Declare Pin 8,9 as output
	DDRD = 0xF0;          // Declare Pin 4,5,6,7 as output
	
	_delay_ms(500);
	start();              // Initialises LCD
	
	sei();                // Allows interupt
	timer();              // Initialises Timer
	
	command(0x80);        // moves the cursor to (1,1)
	Send_A_String("0");   // Initialize the LCD by writing Zero at (1,1)
	command(0xC0);        // moves the cursor to (2,1)
	Send_A_String("0");   // Initialize the LCD by writing Zero at (2,1)

	while(1)
    	{}
	return 0;
}

void timer()
{
	OCR1A = 31249;            // One tick is used to return to zero
	TCCR1B |= (1 << CS02);    // prescalar 256
	TCCR1B |= (1 << WGM12);   // turns on CTC mode for timer1
	
	TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
	TCNT1 = 0;                // 16 bit register
}

/********************************** ISR ******************************/
ISR(TIMER1_COMPA_vect)
{

	in_counter++; 
	
	/************* Thread1 Starts **************/
	if(in_counter<=11)
	{
		in_counter1++;
		if(in_counter1%2==0)
    		{
        		count1++;
        		command(0x80);
			Send_An_Integer(count1);
		}
		if(in_counter1==22){in_counter1=0;}  // One cycle of thread1 is over when in_counter1 equals 22		
	}
	/*************** Thread1 Ends **************/
	
	
	/************* Thread2 Starts **************/
	if(in_counter>11)
	{
		in_counter2++;
		if(in_counter2%4==0)
    		{
			count2--;
			command(0xC0);
			Send_An_Integer(count2);
		}
		if(in_counter2==44){in_counter2=0;}  // One cycle of thread2 is over when in_counter2 equals 44
	}
	/*************** Thread2 Ends **************/		
	
	
	if(in_counter==22)
	{
		in_counter=0;                        // One complete cycle is over when in_counter equals 22
	}		
}

