/***********************************************************
* 	
*	GPIO Module Header 
*                              
*	File Name : GPIO.h
*	Date Created :
*	Last modified :
*
************************************************************/

#ifndef _GPIO_H_
#define _GPIO_H_

#include "L138_common.h"

void GPIO_SetDirection( Uint8 bank, Uint32 pin_id, Uint8 direction );
void GPIO_SetOutput( Uint8 bank, Uint32 pin_id, Uint8 output );
Uint8 GPIO_GetInput( Uint8 bank, Uint32 pin_id );
void GPIO_EnableInterrupt( Uint8 bank_bit, Uint8 enable );
void GPIO_InterruptEdge( Uint8 bank, Uint32 pin_id, Uint8 edge );
Uint8 GPIO_InterruptState( Uint8 bank, Uint32 pin_id );
void GPIO_ClearInterruptState( Uint8 bank );

extern CSL_GpioRegsOvly 	GpioRegs;

#define ENABLE	1
#define DISABLE	0

#define RISING	1
#define FALLING	2
#define BOTH	3

#define GPIO_OUT    1
#define GPIO_IN     0

#define GPIO_HIGH   1
#define GPIO_LOW    0

#endif
