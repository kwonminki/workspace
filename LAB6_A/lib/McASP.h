/***********************************************************
* 	
*	McASP Module Header
*                              
*	File Name : McASP.h
*	Date Created :
*	Last modified :
*
************************************************************/

#ifndef _MCASP_H_
#define _MCASP_H_

#include "L138_common.h"

extern void ConfigMcASP( Uint16 slot_size, Uint16 slot_num, Uint16 buf_sel, Uint16 rcv_int, Uint16 xmt_int );
extern void InitMcASP( Uint16 rcv_xmt, Uint16 buf_sel );
extern void CloseMcASP( void );
extern void GlobalResetMcASP( void );
extern void RResetMcASP( void );
extern void XResetMcASP( void );

extern CSL_McaspRegsOvly mcaspRegs;


#define MCASP_RFMT_RSSZ_16BITS	(CSL_MCASP_RFMT_RSSZ_16BITS << CSL_MCASP_RFMT_RSSZ_SHIFT)
#define MCASP_RFMT_RSSZ_20BITS	(CSL_MCASP_RFMT_RSSZ_20BITS << CSL_MCASP_RFMT_RSSZ_SHIFT)
#define MCASP_RFMT_RSSZ_24BITS	(CSL_MCASP_RFMT_RSSZ_24BITS << CSL_MCASP_RFMT_RSSZ_SHIFT)
#define MCASP_RFMT_RSSZ_32BITS	(CSL_MCASP_RFMT_RSSZ_32BITS << CSL_MCASP_RFMT_RSSZ_SHIFT)

#define MCASP_16BIT	1
#define MCASP_20BIT	2
#define MCASP_24BIT	3
#define MCASP_32BIT	4

#define MCASP_1SLOT	1
#define MCASP_2SLOT	2

#define CFG	1
#define DMA	0

#define RINT	1
#define NO_RINT	0
#define XINT	1
#define NO_XINT	0

#define TRANSMIT	1
#define RECEIVE		2

#define MCASP_0_DATA 	*(Uint32 *)CSL_MCASP_0_DATA_REGS
#define MCASP_0_DATA_ADDR 	CSL_MCASP_0_DATA_REGS

#endif
