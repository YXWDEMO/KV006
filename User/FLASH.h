#ifndef __FLASH_H
#define __FLASH_H
#include "main.h"

#define FLASH_USER_START_ADDR     0x08004F80

#define LOW_SHORT_ERR_DATA 0xA500

#define LOW_SHORT_NO_ERR_DATA 0x5A00

#define SMOKEING_DATA 0x7C
#define NO_SMOKE_DATA 0xC7

extern void flash_Write_User_Data(uint32_t *userData, uint8_t size);
extern void flash_Read_User_Data(uint32_t* userData);

#endif
