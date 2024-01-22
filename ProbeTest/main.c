/*

Museum_2023.c
Created: 13.12.2023 14:05:30
Author : nassnode */
// Einbinden der Bibliothek
#include "hd44780.h" //LCD
#include "i2c_master.h" //I2C
#include "pcf8574.h" // PCF8574 I/O Expander Bibliothek
#include "uart.h" // uart 
#include "adc32.h" // 32-Bit ADC Bibliothek 
#include "mcp4725.h" // MCP4725 DAC Bibliothek

// Einbinden von Standardbibliotheken
#include <avr/io.h> // I/O Funktionen für AVR Mikrocontroller
#include <util/delay.h> // Verzögerungsfunktionen

// Deklarieren und initialisieren ////////////////////////////////////////////////////////////////////////// 
volatile uint8_t buttons = 0xff; volatile int i1=0,ledstatus,ledgruen = 0b01111111, ledgelb = 0b10111111, ledrot = 0b11011111; // Leds werden durch ein low geschaltet. Ledstatus ist der rückgabevariable. i1 ein übergabevariable 
volatile double adctemp= 0.0, adchumid =0.0;
int abfrage1 = 0;

////////////////////////////////////////////////////////////////////////// 
void einlesentempandhumid() 
{
adchumid = adc_readvoltage(0);

_delay_ms(10);

adctemp = adc_readvoltage(1);
} //////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////// 
int checkhumidandtemp(double x, double y) // Abfrage der Humid und Temperatur 
{
if( abfrage1 == 0)
{
	if(((x >= 20)&&(x<= 22))&&((y>= 40)&&(y<= 60))) // Abfrage für den optimalen Bereich
	{
		PORTD &= ~(1 << PD6);
		ledstatus = ledgruen; // led wird grün
	}


	else if ((x<16)||(y<30)||(x>26)||(y>70)) // Abfrage für den roten Bereich und den überschritt in den roten bereich durch abfrage  ledstatus
	{
		ledstatus = ledrot & 0b11110111;// led wird rot
		PORTD |= (1 << PD6);
	}

	else
	{
		PORTD &= ~(1 << PD6);
		ledstatus= ledgelb; // wen nichts stimmt soll die led rot werden überprüfen bzw. Erschuetterung ist
		
	}
	return ledstatus; // rückgabewert
}
else
{
	
	if(((x >= 40)&&(x<= 44))&&((y>= 10)&&(y<= 30))) // Abfrage für den optimalen Bereich
	{
		PORTD &= ~(1 << PD6);
		ledstatus = ledgruen; // led wird grün
	}


	else if ((x<35)||(y<0)||(x>49)||(y>40)) // Abfrage für den roten Bereich und den überschritt in den roten bereich durch abfrage  ledstatus
	{
		
		ledstatus = ledrot & 0b11110111; // led wird rot
		PORTD |= (1 << PD6);
	}

	else
	{
		PORTD &= ~(1 << PD6);
		ledstatus= ledgelb; // wen nichts stimmt soll die led rot werden überprüfen bzw. Erschuetterung ist
		
	}
	return ledstatus; // rückgabewert
	
}
}
////////////////////////////////////////////////////////////////////////// 
void displayData() {
	
	
		lcd_init();
		if (abfrage1 == 0)
		{
		lcd_print("M:1");
		}
		else
		{
			lcd_print("M:2");
		
		}
		lcd_setCursor(0,4);
		lcd_print(" Temp:");

		lcd_setCursor(0, 10);

		lcd_printDouble(adctemp, 1);

		lcd_printChar(DEGREE);

		lcd_print("C");

		lcd_setCursor(1, 4);

		lcd_print(" Humid:");

		lcd_setCursor(1, 11);

		lcd_printDouble(adchumid, 1);

		lcd_printChar(PERCENT);

		_delay_ms(200);
	
	
} 

//////////////////////////////////////////////////////////////////////////
void alarm()
{
	
	while(!(PIND & (PD7)))
	{
		einlesentempandhumid();
		lcd_init();
		lcd_setCursor(0,4);
		lcd_print("Achtung");
		lcd_setCursor(1,4);
		lcd_print("Alarm");
		int i = checkhumidandtemp(adctemp,adchumid);
		i = i & 0b11111110;
		pcf8574_set_outputs(0x21,i);
		
	}	
	
}
///////////////////////////////////////////////////////////////////////////

void abfrage()
{
	
	buttons = pcf8574_get_inputs(0x20);
	switch (buttons)
	{
		
		case 0b11111110:
		while (buttons != 0b11111101 )
		{
			einlesentempandhumid();
			int i = checkhumidandtemp(adctemp,adchumid);
			i = i & 0b11111110;
			pcf8574_set_outputs(0x21,i);
			displayData();
			
			buttons = pcf8574_get_inputs(0x20);
		}
		
		break;
		
		case 0b11111101:
		
			while (buttons != 0b11111110)
			{
				einlesentempandhumid();
				int i14 = checkhumidandtemp(adctemp,adchumid);
				i14 = i14 & 0b11111101;
				pcf8574_set_outputs(0x21,i14);
				abfrage1 = 1;
				displayData();
				
				buttons = pcf8574_get_inputs(0x20);
			}
		abfrage1 = 0;
		break;
		
		case 0b11111011:
		
		pcf8574_set_outputs(0x21,0x00);
		
		break;
		default:
		einlesentempandhumid();
		int i12 = checkhumidandtemp(adctemp,adchumid);
		i12 = i12 & 0b11111110;
		pcf8574_set_outputs(0x21,i12);
		displayData();
		break;
		
		
	}
	
	
	
	
}



////////////////////////////////////////////////////////////////////////// 
int main(void) { 

PORTD |= PIND7;
DDRD |= PD7;

DDRD |= (1 << PD6);

// Setze PD6 standardmäßig auf LOW
PORTD &= ~(1 << PD6);

adc_init(); // Analog digital COnverter initialiseren

while (1)
{
	alarm();
	abfrage();
}
return 0;
} //////////////////////////////////////////////////////////////////////////

