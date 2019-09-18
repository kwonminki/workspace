/***********************************************************
* 	
*	Interrupt Configuration Module  
*                              
*	File Name : Interrupt.c 
*	Date Created :
*	Last modified :
*
************************************************************/

#include "Interrupt.h"

void ConfigInterrupt( void )
{
	CSL_DspintcRegsOvly IntcRegs = (CSL_DspintcRegsOvly)CSL_INTC_0_REGS;

    /* mapping the event to the interrupts   */
    CSL_FINS(IntcRegs->INTMUX1, DSPINTC_INTMUX1_INTSEL4, T64P1_TINT12);
	CSL_FINS(IntcRegs->INTMUX1, DSPINTC_INTMUX1_INTSEL5, MCASP_INT);
	CSL_FINS(IntcRegs->INTMUX1, DSPINTC_INTMUX1_INTSEL6, EDMA3_CC0_INT1);
	CSL_FINS(IntcRegs->INTMUX1, DSPINTC_INTMUX1_INTSEL7, UART2_INT);
	CSL_FINS(IntcRegs->INTMUX2, DSPINTC_INTMUX2_INTSEL8, GPIO_B2INT);
	CSL_FINS(IntcRegs->INTMUX2, DSPINTC_INTMUX2_INTSEL9, RTC_IRQS);

    ICR = 0xFFF0;		// clear all interrupts
	IER = 0x02;			// enable NMI
}



void InstallISR(Uint32 int_num, void (*c_int)(void))
{	
	extern void intvecTable(void);
	volatile Uint32 *code;
	Uint32 temp;

	/* set ISTP to point to the vector table address  */
    ISTP = (unsigned int)intvecTable;

	code = (volatile Uint32 *)((Uint32)intvecTable + int_num*32 );

	*code++ = 0x003C30F6;					// STW   B0,*--B15

	temp = ((Uint32)c_int & 0x0FFFF) << 7;
	*code++ = 0x0000002A | temp;			// MVKL  c_int,B0

	temp = ((Uint32)c_int >> 16) << 7;
	*code++ = 0x0000006A | temp;			// MVKH  c_int,B0

	*code++ = 0x00000362;					// B     B0
	*code++ = 0x003C36E6;					// LDW   *B15++,B0
	*code++ = 0x00002000;					// NOP   2
	*code++ = 0x00000000;					// NOP
	*code   = 0x00000000;					// NOP
}
