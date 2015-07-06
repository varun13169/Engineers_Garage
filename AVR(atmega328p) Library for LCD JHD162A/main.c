#define F_CPU 16000000UL
#include<avr/io.h>
#include<util/delay.h>
#include<string.h>
#include<stdlib.h>
#include "lcd.h"
//D4-D7 connected to D4-D7

#define rs PB0    //pin8 
#define en PB1    //pin9



/**** Decimal Values to Display Special Characters ****/
unsigned int s1[]={10,21,17,17,17,10,4,0};
unsigned int s2[]={0,10,0,4,4,17,10,4};
unsigned int s3[]={0,10,0,4,4,0,14,17};
unsigned int s4[]={1,3,5,9,9,11,27,24};
unsigned int s5[]={0,17,10,17,4,0,14,17};
unsigned int s6[]={0,10,0,4,4,0,31,0};
unsigned int s7[]={10,0,4,0,14,17,17,14};
unsigned int s8[]={0,10,0,31,17,14,0,0};
/******************************************************/

int main()
{
	int i;
	DDRB = 0x03;
	DDRD = 0xF0;
	
	_delay_ms(200);
	start();
	
	while(1)
	{
		clearScreen();
		Send_A_String("Send_A_String()");
		_delay_ms(100);//////
		while(!(PINB & (1<<PB2))){}
		
	
		clearScreen();
		cut("cut() is used to display this.");
		_delay_ms(100);//////
		while(!(PINB & (1<<PB2))){}
		
		clearScreen();
		cut("Send_An_Integer");
		setCursor(1,0);
		Send_An_Integer(sizeof(int));
		_delay_ms(100);//////
		while(!(PINB & (1<<PB2))){}
		
		
		clearScreen();
		setCursor(0,0);
		data('s');
		setCursor(1,1);
		data('e');
		setCursor(0,2);
		data('t');
		setCursor(1,3);
		data('C');
		setCursor(0,4);
		data('u');
		setCursor(1,5);
		data('r');
		setCursor(0,6);
		data('s');
		setCursor(1,7);
		data('o');
		setCursor(0,8);
		data('r');
		setCursor(1,9);
		data('(');
		setCursor(0,10);
		data(')');
		_delay_ms(100);//////
		while(!(PINB & (1<<PB2))){}
		
		
		clearScreen();
		cursor();
		Send_A_String("Cursor is ON");
		_delay_ms(100);//////
		while(!(PINB & (1<<PB2))){}
		noCursor();
		
		
		clearScreen();
		blink();
		Send_A_String("Blinking is ON");
		_delay_ms(100);//////
		while(!(PINB & (1<<PB2))){}
		noBlink();
	
		
		clearScreen();
		Send_A_String("Display will");
		setCursor(1,0);
		Send_A_String("Flicker 5 times");
		for(i=0;i<5;i++)
		{
			_delay_ms(500);
			noDisplay();
			_delay_ms(500);
			display();
		}
		_delay_ms(100);//////
		while(!(PINB & (1<<PB2))){}
		
		
		clearScreen();
		setCursor(0,5);
		Send_A_String("Scroll");
		setCursor(1,6);
		Send_A_String("Left");
		_delay_ms(1000);
		scrollDisplayLeft();
		_delay_ms(1000);
		scrollDisplayLeft();
		_delay_ms(1000);
		scrollDisplayLeft();
		_delay_ms(1000);
		scrollDisplayLeft();
		_delay_ms(1000);
		while(!(PINB & (1<<PB2))){}
		
		
		
		clearScreen();
		setCursor(0,5);
		Send_A_String("Scroll");
		setCursor(1,5);
		Send_A_String("Right");
		_delay_ms(1000);
		scrollDisplayRight();
		_delay_ms(1000);
		scrollDisplayRight();
		_delay_ms(1000);
		scrollDisplayRight();
		_delay_ms(1000);
		scrollDisplayRight();
		_delay_ms(1000);
		while(!(PINB & (1<<PB2))){}
	
		
		clearScreen();
		autoscroll();
		char autos[]={'a','u','t','o','s','c','r','o','l','l','(',')',' ',' ',' '};
		setCursor(0,15);
		for(i=0;i<15;i++)
		{
			data(autos[i]);
			_delay_ms(100);
		}
		noAutoscroll();
		_delay_ms(100);//////
		while(!(PINB & (1<<PB2))){}
		
		
		clearScreen();
		createChar(0,s1);
		setCursor(0,0);
		data(0);
		createChar(1,s2);
		setCursor(0,2);
		data(1);
		createChar(2,s3);
		setCursor(0,4);
		data(2);
		createChar(3,s4);
		setCursor(0,6);
		data(3);
		createChar(4,s5);
		setCursor(0,8);
		data(4);
		createChar(5,s6);
		setCursor(0,10);
		data(5);
		createChar(6,s7);
		setCursor(0,12);
		data(6);
		createChar(7,s8);
		setCursor(0,14);
		data(7);
		_delay_ms(100);//////
		while(!(PINB & (1<<PB2))){}
	}
	
	return 0;
}
 

