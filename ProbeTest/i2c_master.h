/* set CPU speed*/
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#ifndef _I2C_MASTER_H
#define _I2C_MASTER_H

/* I2C Setup Options */
#define F_I2C 100000
#define PRESCALER_I2C 1

void i2c_init(void);

unsigned char i2c_send_start(void);

void i2c_send_stop(void);

unsigned char i2c_send_add_rw(unsigned char address, unsigned char rw);

unsigned char i2c_send_byte(unsigned char byte);

unsigned char i2c_read_byte(void);

#endif
