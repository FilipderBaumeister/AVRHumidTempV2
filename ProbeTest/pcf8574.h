#ifndef _PCF_8574_H
#define _PCF_8574_H

unsigned char pcf8574_get_inputs (unsigned char address);

void pcf8574_set_outputs (unsigned char address, unsigned char byte);

#endif
