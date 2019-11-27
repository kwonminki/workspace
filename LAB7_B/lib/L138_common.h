/***********************************************************
*
*	Header for Common header files
*
*	File Name : L138_commom.h
*	Date Created :
*	Last modified :
*
************************************************************/

#ifndef _L138_COMMON_H_
#define _L138_COMMON_H_

#include <ti/pspiom/cslr/csl_types.h>
#include <ti/pspiom/cslr/soc_OMAPL138.h>
#include <ti/pspiom/cslr/cslr_syscfg0_OMAPL138.h>
#include <ti/pspiom/cslr/cslr_syscfg1_OMAPL138.h>
#include <ti/pspiom/cslr/cslr_psc_OMAPL138.h>
#include <ti/pspiom/cslr/cslr_pllc_OMAPL138.h>
#include <ti/pspiom/cslr/cslr_gpio.h>
#include <ti/pspiom/cslr/cslr_i2c.h>
#include <ti/pspiom/cslr/cslr_tmr.h>
#include <ti/pspiom/cslr/cslr_uart.h>
#include <ti/pspiom/cslr/cslr_edma3cc.h>
#include <ti/pspiom/cslr/cslr_cache.h>
#include <ti/pspiom/cslr/cslr_aintc.h>
#include <ti/pspiom/cslr/cslr_dspintc.h>
#include <ti/pspiom/cslr/cslr_mcasp.h>
#include <sharedCpuVars.h>
#include <c6x.h>


// OMAPL1x PSC Specific
#define pscTimeout 10240

// OMAPL1x SYSCFG Specific
#define KICK0_KEY 0x83E70B13
#define KICK1_KEY 0x95A4F1E0
#define KICK_LOCK 0x00000000

#define EDMA_EVENT0		0
#define EDMA_EVENT1		1
#define EDMA_EVENT2		2
#define EDMA_EVENT3		3
#define EDMA_EVENT4		4
#define EDMA_EVENT5		5
#define EDMA_EVENT6		6
#define EDMA_EVENT7		7
#define EDMA_EVENT8		8
#define EDMA_EVENT9		9
#define EDMA_EVENT10	10
#define EDMA_EVENT11	11
#define EDMA_EVENT12	12
#define EDMA_EVENT13	13
#define EDMA_EVENT14	14
#define EDMA_EVENT15	15
#define EDMA_EVENT16	16
#define EDMA_EVENT17	17
#define EDMA_EVENT18	18
#define EDMA_EVENT19	19
#define EDMA_EVENT20	20
#define EDMA_EVENT21	21
#define EDMA_EVENT22	22
#define EDMA_EVENT23	23
#define EDMA_EVENT24	24
#define EDMA_EVENT25	25
#define EDMA_EVENT26	26
#define EDMA_EVENT27	27
#define EDMA_EVENT28	28
#define EDMA_EVENT29	29
#define EDMA_EVENT30	30
#define EDMA_EVENT31	31

#define INT_4	4
#define INT_5	5
#define INT_6	6
#define INT_7	7
#define INT_8	8
#define INT_9	9
#define INT_10	10
#define INT_11	11
#define INT_12	12
#define INT_13	13
#define INT_14	14
#define INT_15	15


static inline void EnableInterrupt( Uint32 int_num )
{
	IER |= (0x01 << int_num );
}


static inline void DisableInterrupt( Uint32 int_num )
{
	IER &= ~(0x01 << int_num );
}

#endif /*L138_COMMON_H_*/
