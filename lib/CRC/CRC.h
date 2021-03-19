#ifndef _CRC_H_
#define _CRC_H_

#include<stdint.h>

void crc_init(void);

uint16_t crc_generate(uint16_t data);

#endif
