#include <avr/io.h>
#include <util/delay.h>
#include<stdbool.h>
#include <stddef.h>
#include <stdio.h>
#define F_CPU 16000000ul
#include <math.h>
#include <avr/pgmspace.h>
#define USART0SendByte(x) printf(" = %u",(x))
void USART0Init(void);
int USART00SendByte(char u8Data, FILE *stream);
int USART00ReceiveByte(FILE *stream);
FILE usart0_str = FDEV_SETUP_STREAM(USART00SendByte, USART00ReceiveByte, _FDEV_SETUP_RW);

void USART0Init(void)
{
	// Set <a href="#">baud rate</a>
	UBRR0H = (uint8_t)(UBRR_VALUE>>8);
	UBRR0L = (uint8_t)UBRR_VALUE;
	// Set frame format to 8 <a href="#">data bits</a>, no parity, 1 stop bit
	UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
	//enable transmission and reception
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0);	
}
int USART00SendByte(char u8Data, FILE *stream)
{
	if(u8Data == '\n')
	{
		USART00SendByte('\r', 0);
	}
	//wait while previous byte is completed
	while(!(UCSR0A&(1<<UDRE0))){};
	// Transmit data
	UDR0 = u8Data;
	return 0;
}
int USART00ReceiveByte(FILE *stream)
{
	uint8_t u8Data;
	// Wait for byte to be received
	while(!(UCSR0A&(1<<RXC0))){};
	u8Data=UDR0;
	//echo input data
	USART00SendByte(u8Data,stream);
	// Return received data
	return u8Data;
}

int main(void)
{
	stdin=stdout=&usart0_str;
	USART0Init();
  while(1)
  {
  printf("this is test ");
  }
  }
