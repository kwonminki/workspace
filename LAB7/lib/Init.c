/***********************************************************
*
*	System Initialization Module
*
*	File Name : init.c
*	Date Created :
*	Last modified :
*
************************************************************/

#include "Init.h"

void SysConfigForPinMux(void)
{
	CSL_SyscfgRegsOvly  sys0Regs	= (CSL_SyscfgRegsOvly)	CSL_SYSCFG_0_REGS;
	CSL_Syscfg1RegsOvly sys1Regs 	= (CSL_Syscfg1RegsOvly) CSL_SYSCFG_1_REGS;

	ICR = 0xFFF0;		// clear all interrupts

/*=== KICK0 / KICK1 Registers  ===*/
	// Put the CPU chip in supervisor(privledged) mode
	CSL_FINS(sys0Regs->KICK0R, SYSCFG_KICK0R_KICK0, KICK0_KEY);
	CSL_FINS(sys0Regs->KICK1R, SYSCFG_KICK1R_KICK1, KICK1_KEY);


/*===PINMUX Config Registers  ===*/
	// McASP0 AMUTEIN
	CSL_FINST(sys0Regs->PINMUX0, SYSCFG_PINMUX0_PINMUX0_27_24, AMUTE0);

	// McASP0 Tx Clocks
	CSL_FINST(sys0Regs->PINMUX0, SYSCFG_PINMUX0_PINMUX0_23_20, AHCLKX0);
	CSL_FINST(sys0Regs->PINMUX0, SYSCFG_PINMUX0_PINMUX0_7_4,   ACLKX0);
	CSL_FINST(sys0Regs->PINMUX0, SYSCFG_PINMUX0_PINMUX0_15_12, AFSX0);

	// McASP0 Rx Clocks
	CSL_FINST(sys0Regs->PINMUX0, SYSCFG_PINMUX0_PINMUX0_19_16, AHCLKR0);
	CSL_FINST(sys0Regs->PINMUX0, SYSCFG_PINMUX0_PINMUX0_3_0,   ACLKR0);
	CSL_FINST(sys0Regs->PINMUX0, SYSCFG_PINMUX0_PINMUX0_11_8,  AFSR0);

	// McASP0 Rx/Tx Data
	CSL_FINST(sys0Regs->PINMUX1, SYSCFG_PINMUX1_PINMUX1_11_8,  AXR0_13);
	CSL_FINST(sys0Regs->PINMUX1, SYSCFG_PINMUX1_PINMUX1_7_4,   AXR0_14);

	// I2C0 for Communication with TLV320AIC3106
	CSL_FINST(sys0Regs->PINMUX4, SYSCFG_PINMUX4_PINMUX4_15_12, I2C0_SDA);
	CSL_FINST(sys0Regs->PINMUX4, SYSCFG_PINMUX4_PINMUX4_11_8, I2C0_SCL);

	// GPIO
    CSL_FINST(sys0Regs->PINMUX1, SYSCFG_PINMUX1_PINMUX1_27_24,  GPIO0_1);       // DIP SW1
    CSL_FINST(sys0Regs->PINMUX1, SYSCFG_PINMUX1_PINMUX1_23_20,  GPIO0_2);       // DIP SW2
    CSL_FINST(sys0Regs->PINMUX1, SYSCFG_PINMUX1_PINMUX1_19_16,  GPIO0_3);       // DIP SW3
    CSL_FINST(sys0Regs->PINMUX1, SYSCFG_PINMUX1_PINMUX1_15_12,  GPIO0_4);       // DIP SW4

    CSL_FINST(sys0Regs->PINMUX6, SYSCFG_PINMUX6_PINMUX6_15_12,  GPIO2_4);       // S2
    CSL_FINST(sys0Regs->PINMUX6, SYSCFG_PINMUX6_PINMUX6_11_8,   GPIO2_5);       // S3

    CSL_FINST(sys0Regs->PINMUX13, SYSCFG_PINMUX13_PINMUX13_11_8, GPIO6_13);     // LED D4
    CSL_FINST(sys0Regs->PINMUX13, SYSCFG_PINMUX13_PINMUX13_15_12, GPIO6_12);    // LED D5
    CSL_FINST(sys0Regs->PINMUX5, SYSCFG_PINMUX5_PINMUX5_15_12,  GPIO2_12);      // LED D6
    CSL_FINST(sys0Regs->PINMUX0, SYSCFG_PINMUX0_PINMUX0_27_24,  GPIO0_9);       // LED D78


/*===Emulation Syspention Config ===*/
	//Set DSP as source of Emulation Suspension Signal
	CSL_FINST(sys0Regs->SUSPSRC, SYSCFG_SUSPSRC_I2C0SRC, DSP);
	//Note: McASP0 does not support emulation mode


/*===CHIP Config Registers ===*/
	// CFGCHIP1
	// Configure AMUTE source when AMUTE pin is Logic Low
	CSL_FINST(sys0Regs->CFGCHIP1, SYSCFG_CFGCHIP1_AMUTESEL0, LOW);
	// Clear AMUTE Interrupt
	CSL_FINST(sys0Regs->CFGCHIP4, SYSCFG_CFGCHIP4_AMUTECLR0, CLEAR);


/*==== SATA CLOCKS ===*/
	//	Disable SATA Rx Clock
	CSL_FINST(sys1Regs->PWRDN, SYSCFG1_PWRDN_SATACLK_PWRDN, DISABLE);


/*=== KICK0 / KICK1 Registers  ===*/
	// Relock the System Configuration Registers
	CSL_FINS(sys0Regs->KICK0R, SYSCFG_KICK0R_KICK0, KICK_LOCK);
	CSL_FINS(sys0Regs->KICK1R, SYSCFG_KICK1R_KICK1, KICK_LOCK);
}



