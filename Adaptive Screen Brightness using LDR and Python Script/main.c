/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                         varun13169                                                              //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define F_CPU       16000000UL
#include "uartLibrary.h"
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


/****************** Limits **************/
#define low_min 0
#define low_max 10

#define mid_min 10
#define mid_max 30

#define high_min 30

#define minimum_brightness 500
#define medium_brightness 2500
#define maximum_brightness 4880
/****************************************/
/*
 You might need to change these limits
 according to your Linux machine and LDR
*/


int ldrValue=0;
void setup_adc();

int main(void)
{  
	uart_init();
	stdout = &uart_output;
	stdin  = &uart_input;
	
	DDRC |= 0x0A;             // Set Pin5 and Pin7 on arduino as output
	PORTC = 1<<PC1;           // To provide vcc on one of the LDR terminal
	
	sei();                    // Enales global interrupt
	setup_adc();              // Setup ADC according to the defined function
		
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
	//MUX1=1 because we want to start conversion from PORTC2
	DIDR0 |= 1<<ADC1D | 1<<ADC0D;            //disabling digital input of PC0,PC1 pins to save power
}


/*********** varun13169 **************/


/******************************************** ISR Block ********************************************/
ISR(ADC_vect)
{
	uint8_t adcl = ADCL;                             //This is an 8-bit varible used to store the value of ADLC
	uint16_t adc_ten_bit_value = ADCH<<2 | adcl>>6;  //This is an 16-bit varible use to store the 10-bit value of left adjusted result
	
	ldrValue=adc_ten_bit_value;
	
	if(low_min<=ldrValue && ldrValue<low_max){printf("%d %d\n", minimum_brightness, ldrValue);} // Send ldr value anlong with 
	if(mid_min<=ldrValue && ldrValue<mid_max){printf("%d %d\n", medium_brightness, ldrValue);}  // mapped brightness values
	if(ldrValue>=high_min){printf("%d %d\n", maximum_brightness, ldrValue);}                    // to my laptop

	ADCSRA |= 1<<ADSC; //Starts the conversion again
}
/***************************************************************************************************/


/*********************************************************** END *******************************************************************/


