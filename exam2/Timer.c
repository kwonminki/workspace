/***********************************************************
* 	
*	Timer Module  
*                              
*	File Name : Timer.c 
*	Date Created :
*	Last modified :
*
************************************************************/

#include "Timer.h"

static CSL_TmrRegsOvly TimerRegs = (CSL_TmrRegsOvly)CSL_TMR_1_REGS;

void ConfigTimer_64bit( Uint32 period_high32, Uint32 period_low32 )
{
    TimerRegs->TGCR = 0;
    TimerRegs->TCR = 0;

	TimerRegs->TIM12 = 0;
	TimerRegs->TIM34 = 0;

	CSL_FINST(TimerRegs->TGCR, TMR_TGCR_TIMMODE, 64BIT_GPT);	// 64-bit time mode
	CSL_FINST(TimerRegs->TCR, TMR_TCR_CLKSRC12, INTERNAL);		// 24MHz internal AUXCLK

    // timer out of reset 
    TimerRegs->TGCR = CSL_FMKT(TMR_TGCR_TIM12RS, NO_RESET) | CSL_FMKT(TMR_TGCR_TIM34RS, NO_RESET);

    // set period registers
	TimerRegs->PRD12 = period_low32;
	TimerRegs->PRD34 = period_high32;
}


void ConfigTimer_32bit( Uint32 msec )
{
    TimerRegs->TGCR = 0;
    TimerRegs->TCR = 0;

	TimerRegs->TIM12 = 0;
	TimerRegs->TIM34 = 0;

	CSL_FINST(TimerRegs->TGCR, TMR_TGCR_TIMMODE, 32BIT_UNCHAIN);	// 32-bit time mode
	CSL_FINST(TimerRegs->TCR, TMR_TCR_CLKSRC12, INTERNAL);			// 24MHz internal AUXCLK

    // timer out of reset  */
	CSL_FINST(TimerRegs->TGCR, TMR_TGCR_TIM12RS, NO_RESET);

    // set period register
	TimerRegs->PRD12 = (INTERNAL_AUXCLK/1000)*msec;
}


void StartTimer(void)
{
	CSL_FINST(TimerRegs->TCR, TMR_TCR_ENAMODE12, EN_CONT);
}


void StopTimer(void)
{
	CSL_FINST(TimerRegs->TCR, TMR_TCR_ENAMODE12, DISABLE);
	
	TimerRegs->TIM12 = 0;
	TimerRegs->TIM34 = 0;
}			
