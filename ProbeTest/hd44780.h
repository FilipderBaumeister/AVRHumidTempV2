#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#ifndef _HD44780_H_
#define _HD44780_H_

#include <avr/io.h>

/* Configuration */

// LCD size
#define LCD_Size 1602

// LCD I/O           Port/Pin
#define LCD_DDR DDRB
#define LCD_PORT PORTB
#define LCD_PIN PINB
#define LCD_RS 0
#define LCD_RW 1
#define LCD_EN 2
#define LCD_BL 3
#define LCD_D4 4
#define LCD_D5 5
#define LCD_D6 6
#define LCD_D7 7

// Macros
#define INPUT 0
#define OUTPUT 1
#define PERCENT 37
#define DEGREE 223

/* Functions */
void lcd_init(void);
void lcd_sendCommand(unsigned char command);
void lcd_sendData(unsigned char data);
void lcd_sendByte(unsigned char byte);
void lcd_send(unsigned char byte);
void lcd_waitBusy();
void lcd_clear();
void lcd_setCursor(uint8_t row, uint8_t col);
void lcd_print(char *text);
void lcd_printChar(unsigned char byte);
void lcd_printInt(int num);
void lcd_printDouble(double dnum, int precision);
unsigned char lcd_read();

#endif
