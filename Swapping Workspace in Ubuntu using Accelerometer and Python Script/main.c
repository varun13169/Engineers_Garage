/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                         varun13169                                                              //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define F_CPU       16000000UL
#include "uartLibrary.h"
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


int xRaw=0,yRaw=0,zRaw=0;
void setup_adc();


int main(void)
{  
	uart_init();
	stdout = &uart_output;
	stdin  = &uart_input;
	
	DDRC = 0x22;                             //Set Pin5 and Pin7 on arduino as output
	PORTC |= 1<<PC1 | 0<<PC5;
	
	sei();                                   //Enales global interrupt
	setup_adc();                             //Setup ADC according to the defined function
		
	while(1)
	{
	}
}
 


void setup_adc()
{
	ADCSRA |= 1<<ADEN;                       //Enables ADC
	ADCSRA |= 1<<ADPS2 | 1<<ADPS1 | 1<<ADPS0;//Sets ADC Prescalar as 128, i.e. my ADC frequency is 125KHz
	ADCSRA |=  1<<ADSC | 1<<ADIE;            //Enables ADC interupt and Start the conversion
	ADMUX |= 1<<ADLAR | 1<<REFS0 | 1<<MUX1;
	//ADLAR=1 for left adjusted result and REFS0=1 with REFS1=0 to use Vcc as reference voltage
	//MUX1=1 because we want to start conversion from PORTC1
	DIDR0 |= 1<<ADC1D | 1<<ADC0D;            //disabling digital input of PC0,PC1 pins to save power
}

// Used in choosing workspace according to the accelerometer value
int workspace()
{
	if (xRaw>290 && yRaw>280){return 1;}
	if (xRaw>290 && yRaw<280){return 2;}
	if (xRaw<290 && yRaw>320){return 3;}
	if (xRaw<290 && yRaw<320){return 4;}
	else{return 0;}
}
/*********** varun13169 **************/

ISR(ADC_vect)
{
	uint8_t adcl = ADCL;                             //This is an 8-bit varible used to store the value of ADLC
	uint16_t adc_ten_bit_value = ADCH<<2 | adcl>>6;  //This is an 16-bit varible use to store the 10-bit value of left adjusted result
	
	int value_of_mux0= ADMUX & 0x0F; // Retains last four bits of ADMUX,starting fom LSB,  
	                                 // used in workspaceping ADC converted values to xRaw,yRaw,zRaw respectively

	/************ For PORTC2 *************/
	if(value_of_mux0==0x02)
	{
		xRaw=adc_ten_bit_value;
		ADMUX &= 0xF0; // Clears last four bits in ADMUX
		ADMUX |= 0x03; // Put the next four bit accrding to the next conversion
	}
	/*************************************/
	
	
	/************ For PORTC3 *************/
	if(value_of_mux0==0x03)
	{
		yRaw=adc_ten_bit_value;
		ADMUX &= 0xF0; // Clears last four bits in ADMUX
		ADMUX |= 0x02; // Put the next four bit accrding to the next conversion
	}
	/*************************************/
	
	
	
	// This is for z-axis, as Z-out pin is connected to PORTC4,
	// I don't require Z-out but one can easily get it by 
	// making some small changes
	/*
	if(value_of_mux0==0x04)
	{
		zRaw=adc_ten_bit_value;
		ADMUX &= 0xF0;
		ADMUX |= 0x02;
	}
	*/
	
	
	
	ADCSRA |= 1<<ADSC;            //Starts the conversion again
	printf("%d %d %d\n", xRaw,yRaw, workspace()); // Send these to my Laptop
}

/*********************************************************** END *******************************************************************/


