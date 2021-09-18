/*
 * Final code-1.c
 *
 * Created: 03-09-2021 12.39.23 AM
 * Author : mintu
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
int x=0,y=0;


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
	DDRB = 0b11111111;
	DDRA = 0b11111111;
	DDRD = 0b00000000;
	PORTB&=0b00000000;
	PORTA&=0b00000000;
	Ledglow(x,y);
	while(1){
		if (PIND & 0b00000001) {
			down(&x,&y);
		}
		else if (PIND & 0b00000010){
			up(&x,&y);
		}
		else if (PIND & 0b00000100) {
			right(&x,&y);
		}
		else if (PIND & 0b00001000) {
			left(&x,&y);
		}
		Ledglow(x,y);
		_delay_ms(40);
	}
}


