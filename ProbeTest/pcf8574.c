#include "i2c_master.h"
#include "pcf8574.h"
#include <avr/io.h>

unsigned char pcf8574_get_inputs (unsigned char address)
{
	i2c_init ();
	i2c_send_start ();
	i2c_send_add_rw (address, 1);
	unsigned char input = i2c_read_byte ();
	i2c_send_stop ();
	return input;
}


void pcf8574_set_outputs (unsigned char address, unsigned char byte)
{
	i2c_init ();
	i2c_send_start ();
	i2c_send_add_rw (address, 0);
	i2c_send_byte (byte);
	i2c_send_stop ();
}

