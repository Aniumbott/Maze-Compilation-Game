/*
 * Dot matrix.c
 *
 * Created: 14-09-2021 5.45.32 PM
 * Author : mintu
 */ 

#define F_CPU 1000000UL
#define BAUD_PRESCALE (((F_CPU / (9600 * 16UL))) - 1)
#include <avr/io.h>
#include <util/delay.h>

//Initialize UART
void UART_init(long UART_BAUDRATE)
{
	UCSRB |= (1 << RXEN) | (1 << TXEN);
	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1)|(0<<UMSEL);
	UBRRL = BAUD_PRESCALE;
	UBRRH = (BAUD_PRESCALE >> 8);
}

int x=1, y=7;
void op(char c)
{
	switch(c)
	{
		case 'R':
		if(x<7)
		x++;
		break;
		
		case 'L':
		if(x>0)
		x--;
		break;
		
		case 'U':
		if(y<7)
		y++;
		break;
		
		case 'D':
		if(y>0)
		y--;
		break;
	}
}
void prntmat(int* mat[])
{
	for(int i=0; i<8; i++)
	{
		PORTB = 0;
		PORTB = mat[i];
		if (i == (7-y))
		PORTB = 1<<x | PORTB;
		PORTA = ~(1<<(7-i));
		_delay_ms(1);
	}
}

int main(void)
{
	UART_init(9600);
	int mat[] = {0b11111110, 0b10000000, 0b10101100, 0b10011001, 0b11010011, 0b10010101, 0b10100001, 0b00111111};
	DDRB = 0b11111111;
	DDRA = 0b11111111;
	while(1)
	{
		while ((UCSRA & (1 << RXC)) == 0)
		prntmat(mat);
		op(UDR);
		_delay_ms(1);
	}
}