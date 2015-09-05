#define F_CPU 16000000UL
#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#include<stdlib.h>
#include<string.h>
#include"lcd.h"

/**************** Variables *******************/
int player_flag=1;
int flag=1;
int led_number;
int player1_count;
int player2_count;
int count=0;
int start_flag=0;
int i;
volatile uint8_t portbhistory = 0x00;
/**********************************************/


/************ Functions Prototype *************/
int random_number();
void player1();
void player2();
/**********************************************/

/**** Decimal Values to Display Special Characters ****/
unsigned int s1[]={31,17,17,17,17,17,17,17};
unsigned int s2[]={31,8,4,2,1,0,0,0};
unsigned int s3[]={0,0,0,0,0,17,10,4};
unsigned int s4[]={31,2,4,8,16,0,0,0};
/******************************************************/


int main(void)
{
    	DDRB |= 0xFF;                    // Declaring pins 8,9,10,11,12,13 as output
	DDRD |= 0xF0;                    // Declaring pins 4,5,6,7 as output
	DDRC |= 0x00;                    // Declaring all pins of PortC as input
	PORTC |= ((1 << PORTC0) | (1 << PORTC1) | (1 << PORTC2) | (1 << PORTC3)); // Enables the pull-up	
	
	_delay_ms(500);
	start();                      // Initialises LCD display
	_delay_ms(100);
	clearScreen();
	

	EICRA = 1<<ISC10 | 1<<ISC00;  // Rising edge of INT0 generates an interrupt request 
	EIMSK = 1<<INT0;              // Enables INT0
	PORTD |= 0<<PD2;              // Enables the pull-up
	
	PCICR = 1<<PCIE1;             // Enables PCMSK1 scan
	PCMSK1 = 1<<PCINT8 | 1<<PCINT9 | 1<<PCINT10 | 1<<PCINT11; // Trigers interupt whenever pin 14,15,16,17 changes their state
	
	
	
	/****************************/
	sei();                        // Enables Interupt
	clearScreen();                // Clears the Screen
	Send_A_String(" Reaction  Time ");
	setCursor(1,0);
	Send_A_String("      Game     ");
	createChar(0,s1);             //
	createChar(1,s2);             // Creates Custom Charater
	createChar(2,s3);             // to design Arrow
	createChar(3,s4);             //
    	clearScreen();
	Send_A_String("    Push Button");
	setCursor(1,0);
	Send_A_String("      To Play");
	
	setCursor(0,1);               //
	data(0);                      //
	setCursor(1,0);               // Displays the Custom Character
	data(1);                      // that we designed above,
	setCursor(1,1);               // to form an arrow like structure
	data(2);                      //
	setCursor(1,2);               //
	data(3);                      //
	/*****************************/
	
	while(1)
    	{
    		while(start_flag==0){asm ("");}  // Waits for the push button
    		
		/*********** Player 1 Readdy************/
    		cli();                           // Disables interrupt
    		clearScreen();
    		Send_A_String("Player 1");
    		setCursor(1,0);
    		Send_A_String("Get Reddy ");
    		for(i=3;i>0;i--)
    		{                                //
    			display();               //
    			setCursor(1,11);         //
    			PORTB |= 0B00111100;     // Indicates player 1
    			Send_An_Integer(i);      // to get reddy,
    			_delay_ms(500);          // before the start of Game
    			noDisplay();             //
    			PORTB &= 0B11000011;     //
    			_delay_ms(500);          //
    		}
    		setCursor(1,11);
    		Send_A_String("Go !!");
    		display();
    		_delay_ms(500);
    		sei();                           // Enables interrupt
    		/***************************************/
    		
	
	
		/************** Player 1 ***************/
		count=0;                           // Initializes the score
    		clearScreen();
    		Send_A_String("Player 1 score:");
    		setCursor(1,0);
    		Send_An_Integer(count);
    		for(i=0;i<4;i++)
    		{
    			setCursor(1,0);            // This loop gives player 1
    			player1();                 // four chances and
    			Send_An_Integer(count);    // displays score after every chance
    		}
    		player1_count=count;
    		_delay_ms(500);
    		/***************************************/
    		
    		
    		
    		
    		/*********** Player 2 Readdy************/
    		cli();                           // Disables interrupt
    		clearScreen();
    		Send_A_String("Player 2");
    		setCursor(1,0);
    		Send_A_String("Get Reddy ");
    		for(i=3;i>0;i--)
    		{
    			display();               //
    			setCursor(1,11);         //
    			PORTB |= 0B00111100;     // Indicates player 2
    			Send_An_Integer(i);      // to get reddy,
    			_delay_ms(500);          // before the start of Game
    			noDisplay();             //
    			PORTB &= 0B11000011;     //
    			_delay_ms(500);          //
    		}
    		setCursor(1,11);
    		Send_A_String("Go !!");
    		display();
    		_delay_ms(500);
    		sei();                           // Enables interrupt
    		/***************************************/
    		
    		
    		
    		
    		/************** Player 2 ***************/
		count=0;                           // Initializes the score
    		clearScreen();
    		Send_A_String("Player 2 score:");
    		setCursor(1,0);
    		Send_An_Integer(count);
    		for(i=0;i<4;i++)
    		{
    			setCursor(1,0);            // This loop gives player 2
    			player2();                 // four chances and
    			Send_An_Integer(count);    // displays score after every chance
    		}
    		player2_count=count;
    		_delay_ms(500);
    		/***************************************/
    		
    		
    		
    		/*********************** Decide Winner ********************/
    		cli();                                 // Disables interrupt
    		PORTB &= 0B11000011;                   // Turn off all the LEDs
    		_delay_ms(1000);

    		if(player1_count > player2_count)      //
    		{                                      //
    			clearScreen();                 //
    			Send_A_String("Player 1 is");  //
    			setCursor(1,0);                //
    			Send_A_String("faster");       //
    		}                                      // Checks which player got
    		else                                   // the lowest time and
    		{                                      // accordingly declares the winner
    			clearScreen();                 //
    			Send_A_String("Player 2 is");  //
    			setCursor(1,0);                //
    			Send_A_String("faster");       //
    		}                                      //
    		_delay_ms(2000);                       //
    		/************************************************************/
    		
    		
    		
    		/************** Restart ***************/
    		start_flag=0;
    		clearScreen();
		Send_A_String("    Push Button");
		setCursor(1,0);
		Send_A_String("   To Play Again");
		
		setCursor(0,1);
		data(0);
		setCursor(1,0);
		data(1);
		setCursor(1,1);
		data(2);
		setCursor(1,2);
		data(3);
		/**************************************/
		sei();
	}
	return 0;
}



void player1()
{

	player_flag=1;
	led_number = random_number(); // get a random number between 0-3
	while(player_flag==1)
	{
		_delay_ms(1);         // This loop counts the time
		count++;              // in milli-seconds
	}
	player_flag = 1;              // Just to re-initiallise
	
}


void player2()
{
	player_flag=1;
	led_number = random_number(); // get a pseudo random number between 0-3
	while(player_flag==1)
	{
		_delay_ms(1);         // This loop counts the time
		count++;              // in milli-seconds
	}
	player_flag = 1;              // Just to re-initiallise
	
}

int random_number()
{
	int rand_value = rand()%4;             // Genrates a pseudo random number between 0-3
    	                                       // I'm using pseudo random number because it's
  	switch(rand_value)                     // easy to debug and show the concept of intrrupts.
        {                                      //
        	case 0:                        // Used to genrate a pseudo random number
        		PORTB = 1<<PB2;break;  // and according to it glow
        	case 1:                        // one of the four LEDs
        		PORTB = 1<<PB3;break;  //
        	case 2:                        //
        		PORTB = 1<<PB4;break;  //
        	case 3:                        //
        		PORTB = 1<<PB5;break;  //
        }                                      //
        return rand_value;                     //

}


/************************ ISR Blocks *************************/
ISR (PCINT1_vect)
{
    uint8_t changedbits;
    changedbits = PINC ^ portbhistory; // Keeps track on pin change w.r.t. previous ststus
    portbhistory = PINC;               // Stores the current status of PortC for future use

    
    if(changedbits & (1 << PINC0))     // To check pin 14 on arduino
    {
		PORTB ^= 1<<PB2;
		player_flag=0;
		_delay_ms(200);
		if(led_number!=0)
		{                      // Checks if write button is pressed,
			count+=1000;   // if not gives a 1000ms penalty
		}
    }
    
    if(changedbits & (1 << PINC1))     // To check pin 15 on arduino
    {
		PORTB ^= 1<<PB3;
		player_flag=0;
		_delay_ms(200);
		if(led_number!=1)
		{                      // Checks if write button is pressed,
			count+=1000;   // if not gives a 1000ms penalty
		}
    }

    if(changedbits & (1 << PINC2))     // To check pin 16 on arduino
    {
		PORTB ^= 1<<PB4;
		player_flag=0;
		_delay_ms(200);
		if(led_number!=2)
		{                      // Checks if write button is pressed,
			count+=1000;   // if not gives a 1000ms penalty
		}
    }

    if(changedbits & (1 << PINC3))     // To check pin 17 on arduino
    {
		PORTB ^= 1<<PB5;
		player_flag=0;
		_delay_ms(200);
		if(led_number!=3)
		{                      // Checks if write button is pressed,
			count+=1000;   // if not gives a 1000ms penalty
		}
    }
    _delay_ms(250);                    // This is just to take care of debouncing
}

ISR (INT0_vect)
{
		start_flag=1;    // Used in starting the game whenever player is ready
}
/*************************************************************/

