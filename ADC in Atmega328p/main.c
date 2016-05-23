/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                         varun13169                                                              //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*
    Critical point of LDR: 10-15
    Critical point of NTC: 130-135
      
    Critical point for a sensor depends on its make model number and other factors, I have mentioned the range for critical point of my sensors.
*/

#define F_CPU 16000000UL
#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

void setup_adc();

int main()
{
    DDRD = 0xA0;   //Set Pin5 and Pin7 on arduino as output
    
    sei(); //Enales global interrupt
    setup_adc(); //Setup ADC according to the defined function
    
    while(1) {}    //Don't let the program to end
}



ISR(ADC_vect)
{
    uint8_t adcl = ADCL;      //This is an 8-bit varible used to store the value of ADLC
    uint16_t adc_ten_bit_value = ADCH<<2 | adcl>>6;  //This is an 16-bit varible use to store the 10-bit value of left adjusted result
    
    int value_of_mux0= ADMUX & 1<<MUX0;
    
    if(adc_ten_bit_value>133 && (value_of_mux0==0)) {PORTD|=1<<PD7;}        //NTC
    else {PORTD&=(~(1<<PD7));}
    //Input from NTC is on A0, hence when value_of_mux0 is equal to zero and the received adc_ten_bit_value is greater than 133, then make Pin7 on arduino HIGH else make it LOW
    
    
    if(adc_ten_bit_value<10 && (value_of_mux0!=0)) {PORTD|=1<<PD5;}         //LDR
    else {PORTD&=(~(1<<PD5));}
    //Input from LDR is on A1, hence when value_of_mux0 is'nt equal to zero and the received adc_ten_bit_value is less than ten, then make Pin5 on arduino HIGH else make it LOW
    
    
    ADMUX ^= 1<<MUX0;            //Toggles one of the select bit MUX0, i.e. toggling takes place in between A0 and A1 pin on arduino
    ADCSRA |= 1<<ADSC;           //Starts the conversion again
}




void setup_adc()
{
    ADCSRA |= 1<<ADEN;                              //Enables ADC
    ADCSRA |= 1<<ADPS2 | 1<<ADPS1 | 1<<ADPS0;       //Sets ADC Prescalar as 128, i.e. my ADC frequency is 125KHz
    ADCSRA |= 1<<ADIE | 1<<ADSC ;                   //Enables ADC interupt and Start the conversion
    
    ADMUX |= 1<<ADLAR | 1<<REFS0;                   //ADLAR=1 for left adjusted result and REFS0=1 with REFS1=0 to use Vcc as reference voltage
}


/*********************************************************** END *******************************************************************/

