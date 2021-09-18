/*
 * Nevigation by application.c
 *
 * Created: 18-09-2021 1.41.04 PM
 * Author : mintu
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
int x,y;
void usart_init(void);		//--- Usart Initialize
void usart_tx(char x);		//--- Usart Transmit
char usart_rx(void);		//--- Usart Receive


void usart_init()
{	UCSRC &= ~(1 << UMSEL); //setting the UMSEL bit to 0 for asynchronous mode
	int UBBR_Value=25;
	//Put the upper part of the baud number here (bits 8 to 11)
	UBRRH = (unsigned char) (UBBR_Value >> 8);

	//Put the remaining part of the baud number here
	UBRRL = (unsigned char) UBBR_Value;
	UCSRB |= (1 << RXEN) | (1 << TXEN);	/* Turn on transmission and reception */
	UCSRC |= (1 << URSEL) | (3 << UCSZ0) | (1 << UCSZ1);/* Use 8-bit char size */
}


void usart_tx(char x)
{
	//Wait until the Transmitter is ready
	while (! (UCSRA & (1 << UDRE)) );
	UDR = x;//Get that data outa here!
}

char usart_rx()
{	char ch;
	while ((UCSRA & (1<<RXC))==0){
		
	};		//--- Check whether Receive is complete
	ch=UDR;
	return ch;						//--- Return Data from UDR
}

void left(int *x,int *y){
	*x=*x-1;
}
void right(int *x,int *y){
	*x=*x+1;
}
void up(int *x,int *y){
	*y=*y-1;
}
void down(int *x,int *y){
	*y=*y+1;
}
void Ledglow(int x,int y){
	PORTB=0b00000000;
	PORTA =0b00000000;
	PORTB=1<<(x);
	PORTA =~(1<<(7-(y)));
}

int main(void)
{
	usart_init();

	DDRC = 0b00000000;
	
	while(1){
		int Rx_data=usart_rx();
		usart_tx(Rx_data);
		if(Rx_data=='S'){
			DDRB = 0b11111111;
			DDRA = 0b11111111;
			x=0,y=0;
			Ledglow(x,y);
		}
		if (Rx_data=='D') {
			down(&x,&y);
		}
		if (Rx_data=='U'){
			up(&x,&y);
			
		}
		if (Rx_data=='R') {
			right(&x,&y);
		}
		if (Rx_data=='L') {
			left(&x,&y);
		}
		if (Rx_data=='E'){
			PORTB=0b00000000;
			PORTA=0b00000000;
		}
		Ledglow(x,y);
		_delay_ms(40);
		
	}
}


