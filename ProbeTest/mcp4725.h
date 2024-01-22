#include <avr/io.h>

#ifndef _MCP_4725_H
#define _MCP_4725_H

/* adjust DAC reference in volt*/
#define DACREF 5.00

void mcp4725_setoutput_fastmode(uint8_t address, uint16_t output);
void mcp4725_setvoltage_fastmode(uint8_t address, double voltage);

#endif
