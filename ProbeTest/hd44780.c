#include "hd44780.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const unsigned char row_offset[] = {0x00, 0x40};
static inline void lcd_pulseEn();
static void lcd_setDDR(unsigned char ddr);

void lcd_init(void)
{

    LCD_DDR = 0xFF;
    LCD_PORT = 0x00;
    _delay_ms(40);
    lcd_sendByte(0x03);
    _delay_ms(15);
    lcd_sendByte(0x03);
    _delay_ms(1);
    lcd_sendByte(0x03);
    _delay_ms(1);
    lcd_sendByte(0x02);
    _delay_us(40);
    lcd_sendCommand(0x28);
    lcd_sendCommand(0x0C);
    lcd_sendCommand(0x06);
    lcd_sendCommand(0x01);
    _delay_ms(10);
}

void lcd_sendCommand(unsigned char command)
{

    lcd_waitBusy();
    LCD_PORT &= ~(1 << LCD_RS);
    lcd_send(command);
}
void lcd_sendData(unsigned char data)
{

    lcd_waitBusy();
    LCD_PORT |= (1 << LCD_RS);
    lcd_send(data);
}
void lcd_sendByte(unsigned char byte)
{

    LCD_PORT &= ~(1 << LCD_RS);
    LCD_PORT |= (byte << 4);
    lcd_pulseEn();
    LCD_PORT &= 0x0F; // Clean data pins
}

void lcd_send(unsigned char byte)
{

    // high nibble
    LCD_PORT |= (byte & 0xF0);
    lcd_pulseEn();
    LCD_PORT &= 0x0F; // clean data pins

    // low nibble
    LCD_PORT |= ((byte << 4) & 0xF0);
    lcd_pulseEn();
    LCD_PORT &= 0x0F; // clean data pins
}

void lcd_waitBusy()
{

    unsigned char busy = 0;
    lcd_setDDR(INPUT);
    LCD_PORT &= ~(1 << LCD_RS);
    LCD_PORT |= (1 << LCD_RW);

    do
    {
        LCD_PORT |= (1 << LCD_EN);
        _delay_us(10);
        busy &= ~(1 << LCD_D7);
        busy |= ((LCD_PIN & (1 << LCD_D7)) << LCD_D7);
        LCD_PORT &= ~(1 << LCD_EN);

    } while (busy & (1 << LCD_D7) ? 1 : 0);

    lcd_setDDR(OUTPUT);
    LCD_PORT &= ~(1 << LCD_RW);
    _delay_us(100);
}

void lcd_clear()
{

    lcd_sendCommand(0x01);
}

void lcd_setCursor(uint8_t row, uint8_t col)
{

    lcd_sendCommand(0x80 | (col + row_offset[row]));
}

void lcd_print(char *text)
{

    int len = strlen(text);
    for (int i = 0; i != len; i++)
    {
        lcd_sendData(text[i]);
    }
}

void lcd_printChar(unsigned char byte)
{
    lcd_sendData(byte);
}

void lcd_printInt(int num)
{

    int length = snprintf(NULL, 0, "%d", num);

    // Allocate memory for the string
    char *strInt = (char *)malloc((length + 1) * sizeof(char));
    if (strInt == NULL)
        return;
    snprintf(strInt, length + 1, "%d", num);
    lcd_print(strInt);
    free(strInt);
}
void lcd_printDouble(double dnum, int precision)
{
	int length = snprintf(NULL, 0, "%f", dnum);
	
	// Allocate memory for the string
	char *strValue = malloc(length + 1);
	if (strValue == NULL)
		return;
	dtostrf(dnum, 4, precision, strValue);
	
	// Print
	lcd_print(strValue);
	free(strValue);
}

static inline void lcd_pulseEn()
{

    LCD_PORT |= (1 << LCD_EN);
    _delay_us(1);
    LCD_PORT &= ~(1 << LCD_EN);
}

unsigned char lcd_read()
{

    unsigned char status = 0;

    lcd_waitBusy();
    lcd_setDDR(INPUT);

    LCD_PORT &= ~(1 << LCD_RS);
    LCD_PORT |= (1 << LCD_RW);

    // high nibble
    LCD_PORT |= (1 << LCD_EN);
    _delay_us(10);
    status |= (LCD_PIN & (1 << LCD_D4));
    status |= (LCD_PIN & (1 << LCD_D5));
    status |= (LCD_PIN & (1 << LCD_D6));
    LCD_PORT &= ~(1 << LCD_EN);

    // low nibble
    LCD_PORT |= (1 << LCD_EN);
    _delay_us(10);
    status |= (LCD_PIN & (1 << LCD_D4)) >> 4;
    status |= (LCD_PIN & (1 << LCD_D5)) >> 4;
    status |= (LCD_PIN & (1 << LCD_D6)) >> 4;
    status |= (LCD_PIN & (1 << LCD_D7)) >> 4;
    LCD_PORT &= ~(1 << LCD_EN);

    lcd_setDDR(OUTPUT);
    LCD_PORT &= ~(1 << LCD_RW);

    return status;
}

static void lcd_setDDR(unsigned char ddr)
{

    if (ddr == 0)
    {
        LCD_DDR &= ~((1 << LCD_D4) | (1 << LCD_D5) | (1 << LCD_D6) | (1 << LCD_D7));
    }
    else
    {
        LCD_DDR |= ((1 << LCD_D4) | (1 << LCD_D5) | (1 << LCD_D6) | (1 << LCD_D7));
        LCD_PORT &= ~((1 << LCD_D4) | (1 << LCD_D5) | (1 << LCD_D6) | (1 << LCD_D7));
    }
}