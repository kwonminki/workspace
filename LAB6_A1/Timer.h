/***********************************************************
* 	
*	Timer Module Header 
*                              
*	File Name : Timer.h 
*	Date Created :
*	Last modified :
*
************************************************************/

#ifndef _TIMER_H_
#define _TIMER_H_

#include "L138_common.h"

void ConfigTimer_64bit( Uint32 period_high32, Uint32 period_low32 );
void ConfigTimer_32bit( Uint32 msec );
void StartTimer(void);
void StopTimer(void);

#define INTERNAL_AUXCLK	24000000U

#endif
