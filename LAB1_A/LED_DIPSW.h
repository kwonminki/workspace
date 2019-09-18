/***********************************************************
* 	
*	LED & DIP SW Control Module Header 
*                              
*	File Name : LED_DIPSW.h 
*	Date Created :
*	Last modified :
*
************************************************************/

#ifndef _LED_DIPSW_H_
#define _LED_DIPSW_H_

#include "GPIO.h"

Uint8 GetDIP_Status( Uint8 num );
Uint8 GetPushButton_Status( Uint8 num );
Uint8 GetDIP_AllStatus( void );
void LED_On( Uint8 num );
void LED_Off( Uint8 num );
void LED_Toggle( Uint8 num );
void LED_DIPSW_Init( void );

#define DIP_ON	0
#define DIP_OFF	1

#define DIP_1   0
#define DIP_2   1
#define DIP_3   2
#define DIP_4   3

#define PUSH_BTN_1  0
#define PUSH_BTN_2  1

#define LED_ON  1
#define LED_OFF 0

#define LED_ONOFF   1
#define LED_SWING   0

#define PUSH_DOWN   0
#define PUSH_UP     1

#define LED_D4  0
#define LED_D5  1
#define LED_D6  2
#define LED_D7  3

#endif
