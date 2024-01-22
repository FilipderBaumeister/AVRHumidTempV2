#include "adc32.h"
#include <avr/io.h>
#include <util/delay.h>

void adc_init()
{
	ADCSRA |= (1 << ADEN);
	ADCSRA |= 0x07; // Prescaler 1
	ADMUX |= 0x40;	// Set ext. AREF as Vref
}

void adc_channel_select(unsigned char channel)
{
	ADMUX &= 0xC0; // clear MUX4:MUX0 and ADLAR bit for initialization

	switch (channel)
	{
	case 0:
		break;
	case 1:
		ADMUX |= (1 << MUX0);
		break;
	case 2:
		ADMUX |= (1 << MUX1);
		break;
	case 3:
		ADMUX |= (1 << MUX0) | (1 << MUX1);
		break;
	case 4:
		ADMUX |= (1 << MUX2);
		break;
	case 5:
		ADMUX |= (1 << MUX0) | (1 << MUX2);
		break;
	case 6:
		ADMUX |= (1 << MUX1) | (1 << MUX2);
		break;
	case 7:
		ADMUX |= (1 << MUX0) | (1 << MUX1) | (1 << MUX2);
		break;
	default:
		ADMUX |= (0x1F & channel);
	}
	return;
}

double adc_readvoltage(unsigned char channel)
{
	// get the raw input
	double analogReading = adc_read(channel);
	return analogReading / 1024 * AREF;
}

int adc_read(unsigned char channel)
{
	adc_channel_select(channel);
	ADCSRA |= (1 << ADSC); // start conversion
	while ((ADCSRA & (1 << ADSC)) == 1)
		;		// Wait until conversion is done
	(void)ADCW; // discard first value after channel change
	_delay_ms(2);
	ADCSRA |= (1 << ADSC); // start conversion
	while ((ADCSRA & (1 << ADSC)) == 1)
		; // Wait until conversion is done

	int analogReading = ADCW;
	return analogReading;
}