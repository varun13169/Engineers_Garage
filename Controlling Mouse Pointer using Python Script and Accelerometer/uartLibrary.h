#define F_CPU 16000000UL
#define BAUD 9600
#define BRC ((F_CPU/16/BAUD)-1)


#include <util/setbaud.h>
#include <avr/io.h>
#include <stdio.h>

void uart_init() 
{
	UBRR0H = (BRC>>8); //Putting Upper 4 bits of BRC in lower 4 bits of UBRR0H
	UBRR0L = BRC; //Putting Lowwer 8 bits of BRC in UBRR0L

    	UCSR0B = 1 << TXEN0 | 1 << TXCIE0 | 1 << RXEN0 | 1 << RXCIE0;     //Enables TX, TX complete Interupt Enable, Enable RX, RX complete Interupt Enable
	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);                               //8-bit data size
}

void uart_putchar(char c, FILE *stream) 
{
	if (c == '\n')
	{
        	uart_putchar('\r', stream);
    	}
    	loop_until_bit_is_set(UCSR0A, UDRE0);  // Wait until data register empty.
    	UDR0 = c;

}

char uart_getchar(FILE *stream)
{
    loop_until_bit_is_set(UCSR0A, RXC0);
    return UDR0;
}

FILE uart_output = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

FILE uart_input = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);


