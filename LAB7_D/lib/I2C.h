/***********************************************************
*
*	I2C Module Header
*
*	File Name : i2c.h
*	Date Created :
*	Last modified :
*
************************************************************/

#ifndef _I2C_H_
#define _I2C_H_

#include "L138_common.h"

void I2C_Init (Uint16 sclk);
void I2C_Write (Uint16 i2c_addr, Uint8* data, Uint16 len);
void I2C_Read (Uint16 i2c_addr, Uint8* data, Uint16 len);

#endif
