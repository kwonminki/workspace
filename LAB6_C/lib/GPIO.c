/***********************************************************
* 	
*	GPIO Module  
*                              
*	File Name : GPIO.c 
*	Date Created :
*	Last modified :
*
************************************************************/

#include "GPIO.h"

CSL_GpioRegsOvly 	GpioRegs = (CSL_GpioRegsOvly)(CSL_GPIO_0_REGS);


void GPIO_SetDirection( Uint8 bank, Uint32 pin_id, Uint8 direction )
{
    if ( direction == GPIO_OUT )
		GpioRegs->BANK[bank].DIR &= ~pin_id;
    else
        GpioRegs->BANK[bank].DIR |= pin_id;   
}


void GPIO_SetOutput( Uint8 bank, Uint32 pin_id, Uint8 output )
{
    if ( output  == GPIO_HIGH )
        GpioRegs->BANK[bank].SET_DATA = pin_id;   	
    else
        GpioRegs->BANK[bank].CLR_DATA = pin_id;   	
}


Uint8 GPIO_GetInput( Uint8 bank, Uint32 pin_id )
{
    if( GpioRegs->BANK[bank].IN_DATA & pin_id )
		return 1;
	else
		return 0;
}


void GPIO_EnableInterrupt( Uint8 bank_bit, Uint8 enable )	// bank_bit : 0 ~ 7 
{
	if( enable == ENABLE )
		GpioRegs->BINTEN |= (1<<bank_bit);
	else
		GpioRegs->BINTEN &= ~(1<<bank_bit);	
}		
	

void GPIO_InterruptEdge( Uint8 bank, Uint32 pin_id, Uint8 edge )
{
	if( edge == RISING )
	{
		GpioRegs->BANK[bank].SET_RIS_TRIG = pin_id;
		GpioRegs->BANK[bank].CLR_FAL_TRIG = pin_id;
	}
	else if( edge == FALLING )
	{
		GpioRegs->BANK[bank].SET_FAL_TRIG = pin_id;
		GpioRegs->BANK[bank].CLR_RIS_TRIG = pin_id;
	}
	else if( edge == BOTH )
	{
		GpioRegs->BANK[bank].SET_RIS_TRIG = pin_id;
		GpioRegs->BANK[bank].SET_FAL_TRIG = pin_id;
	}
}


Uint8 GPIO_InterruptState( Uint8 bank, Uint32 pin_id )
{
	if( GpioRegs->BANK[bank].INTSTAT & pin_id )
	{
		GpioRegs->BANK[bank].INTSTAT = pin_id;
		return 1;
	}
	else
	{
		GpioRegs->BANK[bank].INTSTAT = pin_id;
		return 0;
	}
}


void GPIO_ClearInterruptState( Uint8 bank ) {
    GpioRegs->BANK[bank].INTSTAT = 0xFFFFFFFF;
}
