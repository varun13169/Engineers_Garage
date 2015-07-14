/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                         varun13169                                                              //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define F_CPU       16000000UL
#include "uartLibrary.h"
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


//These values are from my sensors you might have to change it according to your sensor
#define min_x 295 // approx max. value of x I'm getting from my sensor
#define max_x 395 // approx min. value of x I'm getting from my sensor
#define min_y 295 // approx max. value of y I'm getting from my sensor
#define max_y 390 // approx min. value of y I'm getting from my sensor
#define min_z 295 // approx max. value of z I'm getting from my sensor
#define max_z 422 // approx min. value of z I'm getting from my sensor
/*************************************************************************************/

#define height_min 0
#define height_max 767
#define width_min 0
#define width_max 1365


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


// This function is combination of map and constraint functions
// available in Arduino IDE
int map_contraint(int val, int from_low, int from_high, int to_low, int to_high)
{
	int a = ((to_low - to_high)/(from_low - from_high)*(val - from_low)) + to_low;
	// Above is a simple fromula which LINEARLY maps one set of values on other
	//Three lines under this sets the constraint on the highest and the lowest value obtained from the above formula
	if(a < to_low){return to_low;}
	else if(a > to_high){return to_high;}
	else{return a;}
}
/*********** varun13169 **************/

ISR(ADC_vect)
{
	uint8_t adcl = ADCL;                             //This is an 8-bit varible used to store the value of ADLC
	uint16_t adc_ten_bit_value = ADCH<<2 | adcl>>6;  //This is an 16-bit varible use to store the 10-bit value of left adjusted result
	
	int value_of_mux0= ADMUX & 0x0F; // Retains last four bits of ADMUX,starting fom LSB,  
	                                 // used in mapping ADC converted values to xRaw,yRaw,zRaw respectively

	/************ For PORTC2 *************/
	if(value_of_mux0==0x02)
	{
		xRaw=adc_ten_bit_value;
		ADMUX &= 0xF0; // Clears last four bits in ADMUX
		ADMUX |= 0x03; // Put the next four bit accrding to the next conversion
		xRaw = map_contraint(xRaw,min_x,max_x,height_min,height_max);
	}
	/*************************************/
	
	
	/************ For PORTC3 *************/
	if(value_of_mux0==0x03)
	{
		yRaw=adc_ten_bit_value;
		ADMUX &= 0xF0; // Clears last four bits in ADMUX
		ADMUX |= 0x02; // Put the next four bit accrding to the next conversion
		yRaw = map_contraint(yRaw,min_y,max_y,-width_max,width_min);
		yRaw = -yRaw;
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
	printf("%d %d\n", xRaw,yRaw); // Send these to my Laptop
}

/*********************************************************** END *******************************************************************/

