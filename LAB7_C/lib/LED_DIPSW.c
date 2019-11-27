/***********************************************************
* 	
*	LED & DIP SW Control Module 
*                              
*	File Name : LED_DIPSW.c
*	Date Created :
*	Last modified :
*
************************************************************/

#include "LED_DIPSW.h"


Uint8 GetDIP_Status( Uint8 num )			//  num : 0 ~ 3
{
	return GPIO_GetInput( GP0, GP0P1 << num );
}


Uint8 GetPushButton_Status( Uint8 num )            //  num : 0 ~ 1
{
    return GPIO_GetInput( GP2, GP2P4 << num );
}


Uint8 GetDIP_AllStatus( void )
{
	Uint8 val;

	val = 	 GetDIP_Status( 0 ) |
			(GetDIP_Status( 1 ) << 1) |
			(GetDIP_Status( 2 ) << 2) |
			(GetDIP_Status( 3 ) << 3);

	return val;
}


void LED_On( Uint8 num )	//  num : 0 ~ 3
{
	switch( num ) {
	    case LED_D4 :
	        GPIO_SetOutput( GP6, GP6P13, GPIO_HIGH );
	        break;
	    case LED_D5 :
            GPIO_SetOutput( GP6, GP6P12, GPIO_HIGH );
            break;
        case LED_D6 :
            GPIO_SetOutput( GP2, GP2P12, GPIO_HIGH );
            break;
        case LED_D7 :
            GPIO_SetOutput( GP0, GP0P9, GPIO_HIGH );
            break;
	}
}


void LED_Off( Uint8 num )    //  num : 0 ~ 3
{
    switch( num ) {
        case LED_D4 :
            GPIO_SetOutput( GP6, GP6P13, GPIO_LOW );
            break;
        case LED_D5 :
            GPIO_SetOutput( GP6, GP6P12, GPIO_LOW );
            break;
        case LED_D6 :
            GPIO_SetOutput( GP2, GP2P12, GPIO_LOW );
            break;
        case LED_D7 :
            GPIO_SetOutput( GP0, GP0P9, GPIO_LOW );
            break;
    }
}


void LED_Toggle( Uint8 num )				//  num : 0 ~ 3
{
	switch( num ) {
        case LED_D4 :
            if( GpioRegs->BANK[GP6].OUT_DATA & GP6P13 )
                GPIO_SetOutput( GP6, GP6P13, GPIO_LOW );
            else
                GPIO_SetOutput( GP6, GP6P13, GPIO_HIGH );
            break;
        case LED_D5 :
            if( GpioRegs->BANK[GP6].OUT_DATA & GP6P12 )
                GPIO_SetOutput( GP6, GP6P12, GPIO_LOW );
            else
                GPIO_SetOutput( GP6, GP6P12, GPIO_HIGH );
            break;
        case LED_D6 :
            if( GpioRegs->BANK[GP2].OUT_DATA & GP2P12 )
                GPIO_SetOutput( GP2, GP2P12, GPIO_LOW );
            else
                GPIO_SetOutput( GP2, GP2P12, GPIO_HIGH );
            break;
        case LED_D7 :
            if( GpioRegs->BANK[GP0].OUT_DATA & GP0P9 )
                GPIO_SetOutput( GP0, GP0P9, GPIO_LOW );
            else
                GPIO_SetOutput( GP0, GP0P9, GPIO_HIGH );
            break;
    }
}	


void LED_DIPSW_Init( void )
{
    //  GPIO pins direction to input for DIP SW
    GPIO_SetDirection( GP0, GP0P1, GPIO_IN );
    GPIO_SetDirection( GP0, GP0P2, GPIO_IN );
    GPIO_SetDirection( GP0, GP0P3, GPIO_IN );
    GPIO_SetDirection( GP0, GP0P4, GPIO_IN );

    //  GPIO pins direction to input for PUSH BUTTON SW
    GPIO_SetDirection( GP2, GP2P4, GPIO_IN );
    GPIO_SetDirection( GP2, GP2P5, GPIO_IN );

    // interrupt enable for GPIO pins for DIP SW
    GPIO_EnableInterrupt( 2, ENABLE );
    GPIO_ClearInterruptState( GP2 );
    GPIO_InterruptEdge( GP2, GP2P4, FALLING );
    GPIO_InterruptEdge( GP2, GP2P5, FALLING );

    // GPIO pins direction to input for LED
    GPIO_SetDirection( GP6, GP6P13, GPIO_OUT );
    GPIO_SetDirection( GP6, GP6P12, GPIO_OUT );
    GPIO_SetDirection( GP2, GP2P12, GPIO_OUT );
    GPIO_SetDirection( GP0, GP0P9, GPIO_OUT );

    LED_Off( LED_D4 );
    LED_Off( LED_D5 );
    LED_Off( LED_D6 );
    LED_Off( LED_D7 );
}


