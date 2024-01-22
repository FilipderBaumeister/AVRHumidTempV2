/*
 * uart.h
 *
 * Created: 23.08.2023 07:33:29
 *  Author: bremdode
 */ 

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#ifndef UART_H_
#define UART_H_

#define BAUD 9600UL
#define UBRR_VAL ((F_CPU+BAUD*8)/(BAUD*16)-1)   // clever runden
#define BAUD_REAL (F_CPU/(16*(UBRR_VAL+1)))     // Reale Baudrate
#define BAUD_ERROR ((BAUD_REAL*1000)/BAUD) // Fehler in Promille, 1000 = kein Fehler.

#if ((BAUD_ERROR<990) || (BAUD_ERROR>1010))
#error Baudrate error out of margin 1%
#endif

#define UART_MAXSTRLEN 32

void uart_init();
void uart_putString(char *s);
int uart_putChar(unsigned char c);
void uart_putInt(int num);
void uart_putDouble(double dnum);

#endif /* UART_H_ */



