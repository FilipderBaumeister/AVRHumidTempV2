/*
 * uart.c
 *
 * Created: 23.08.2023 07:31:53
 *  Author: bremdode
 */ 
#include "uart.h"
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void uart_init()
{
	
	UBRRH = UBRR_VAL >> 8;
	UBRRL = UBRR_VAL & 0xFF;

	UCSRB |= (1<<TXEN)|(1<<RXEN);  // UART TX&RX einschalten
	UCSRB |= (1<<RXCIE);	// Receive Interrupt enable
	UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);  // Asynchron 8N1
}

void uart_putString (char *s)
{
	while (*s)
	{   /* so lange *s != '\0' (Terminator)" */
		uart_putChar(*s);
		s++;
	}
}

int uart_putChar(unsigned char c)
{
	while (!(UCSRA & (1<<UDRE)));  /* warten bis Senden moeglich */

	UDR = c;                      /* sende Zeichen */
	return 0;
}

void uart_putInt(int num)
{
	int length = snprintf(NULL, 0, "%d", num);

	// Allocate memory for the string
	char *strInt = (char *)malloc((length + 1) * sizeof(char));
	if (strInt == NULL)
	return;
	snprintf(strInt, length + 1, "%d", num);
	uart_putString(strInt);
	free(strInt);
}

void uart_putDouble(double dnum) {
	
	int length = snprintf(NULL, 0, "%f", dnum);
	
	// Allocate memory for the string
	char *strValue = malloc(length + 1);
	if (strValue == NULL)
		return;
	dtostrf(dnum, 4, 2, strValue);
	
	uart_putString(strValue);
	free(strValue);
}