/***********************************************************
* 	
*	EDMA McASP Module Header 
*                              
*	File Name : EDMA_McASP.h 
*	Date Created :
*	Last modified :
*
************************************************************/

#ifndef _EDMA_MCASP_H_
#define _EDMA_MCASP_H_

#include "L138_common.h"

extern void ConfigEDMAForR( Uint16 ch, Uint32 dst, Uint16 buffer_size, Uint16 data_witdth, Uint16 link_num, Uint16 tcint );
extern void ConfigEDMAForX( Uint16 ch, Uint32 src, Uint16 buffer_size, Uint16 data_witdth, Uint16 link_num, Uint16 tcint );
extern void EDMAReset( void );
extern CSL_Edma3ccRegsOvly edma3ccRegs;

#define REVT	0
#define XEVT	1

#define TCC_R	REVT
#define TCC_X	XEVT

#define TCINT		1
#define NO_TCINT	0

#define R_LINK_PING	32
#define R_LINK_PONG	33
#define X_LINK_PING	34
#define X_LINK_PONG	35

#endif
