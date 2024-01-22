#include "i2c_master.h"
#include "mcp4725.h"

#include <avr/io.h>

void mcp4725_setoutput_fastmode(uint8_t address, uint16_t output) 
{
	i2c_init ();
	i2c_send_start ();
	i2c_send_add_rw (address, 0);
	i2c_send_byte((uint8_t)(output>>8));
	i2c_send_byte((uint8_t)(output));
	i2c_send_stop ();
}

void mcp4725_setvoltage_fastmode(uint8_t address, double voltage) 
{
	//get the raw output
	uint16_t output = voltage*4096/DACREF;
	if (output > 4095)
		output = 4095;

	//write to chip
	mcp4725_setoutput_fastmode(address, output);
}