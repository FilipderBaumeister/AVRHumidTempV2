#include "i2c_master.h"
#include <avr/io.h>

void i2c_init (void)
{
	/*set i2c bus speed according to avr data sheet*/
	TWSR = 0;
	TWBR = (uint8_t)((((F_CPU / F_I2C) / PRESCALER_I2C) - 16 ) / 2);
}

unsigned char i2c_send_start (void)
{
	/*writing a one to TWINT clears it, TWSTA=Start, TWEN=TWI-enable*/
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	/*wait, until start condition has been sent --> ACK*/
	while (!(TWCR & (1<<TWINT)));
	return TWSR;
}

void i2c_send_stop (void)
{
	/*clear TWINT , TWSTO=Stop, TWEN=TWI-enable*/
	TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);	
}


unsigned char i2c_send_add_rw (unsigned char address, unsigned char rw)
{
	/*address can be 0 .. 8; rw=0 --> write, rw=1 --> read*/
	unsigned char addr_byte = 0;
	/*shift address one bit left*/
	addr_byte = address << 1;
	/*set RW-Bit, if necessary*/
	addr_byte |= rw;
	/*0b0100xxx0 --> address of Expander*/
	addr_byte |= 0b01000000;
	/*TWDR contains byte to send*/
	TWDR = addr_byte;
	/*send content of TWDR*/
	TWCR = (1<<TWINT) | (1<<TWEN);
	/*wait, until address has been sent --> ACK*/
	while (!(TWCR & (1<<TWINT)));
	return TWSR;
}


unsigned char i2c_send_byte (unsigned char byte)
{
	/*write byte to TWDR*/
	TWDR = byte;
	/*send content of TWDR*/
	TWCR = (1<<TWINT) | (1<<TWEN);
	/*wait, until byte has been sent --> ACK*/
	while (!(TWCR & (1<<TWINT)));
	return TWSR;
}


unsigned char i2c_read_byte (void)
{
	/*send content of TWDR; TWEA = enable ACK*/
	TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
	/*wait, until byte has been received --> ACK*/
	while (!(TWCR & (1<<TWINT)));
	return TWDR;
}
