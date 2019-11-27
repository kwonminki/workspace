/***********************************************************
* 	
*	EDMA McASP Module  
*                              
*	File Name : EDMA_McASP.c 
*	Date Created :
*	Last modified :
*
************************************************************/

#include "EDMA_McASP.h"
#include "MCASP.h"
#include "define.h"

CSL_Edma3ccRegsOvly edma3ccRegs = (CSL_Edma3ccRegsOvly)(CSL_EDMA30CC_0_REGS);

void ConfigEDMAForR( Uint16 ch, Uint32 dst, Uint16 buffer_size, Uint16 data_witdth, Uint16 link_num, Uint16 tcint )
{
	edma3ccRegs->PARAMSET[ch].OPT =   	  	  CSL_FMK(EDMA3CC_OPT_TCC, TCC_R)
											| CSL_FMKT(EDMA3CC_OPT_SYNCDIM, ASYNC);
	if( tcint )
		edma3ccRegs->PARAMSET[ch].OPT |=   	  CSL_FMKT(EDMA3CC_OPT_TCINTEN, ENABLE);
		
	edma3ccRegs->PARAMSET[ch].SRC = 	  	 (Uint32)(&mcaspRegs->RBUF14);
	edma3ccRegs->PARAMSET[ch].DST = 	  	  dst;
	edma3ccRegs->PARAMSET[ch].A_B_CNT =    	  CSL_FMK(EDMA3CC_A_B_CNT_BCNT, ELEMENT_SIZE)
											| CSL_FMK(EDMA3CC_A_B_CNT_ACNT, data_witdth);
	edma3ccRegs->PARAMSET[ch].SRC_DST_BIDX =  CSL_FMK(EDMA3CC_SRC_DST_BIDX_DSTBIDX, buffer_size*data_witdth);
	edma3ccRegs->PARAMSET[ch].LINK_BCNTRLD =  CSL_FMK(EDMA3CC_LINK_BCNTRLD_BCNTRLD, ELEMENT_SIZE)
	                                        | CSL_FMK(EDMA3CC_LINK_BCNTRLD_LINK ,(Uint32)(&(edma3ccRegs->PARAMSET[link_num])));
	edma3ccRegs->PARAMSET[ch].SRC_DST_CIDX =  CSL_FMK(EDMA3CC_SRC_DST_CIDX_DSTCIDX,-(buffer_size-1)*data_witdth);
	edma3ccRegs->PARAMSET[ch].CCNT = 	  	  buffer_size;
}

void ConfigEDMAForX( Uint16 ch, Uint32 src, Uint16 buffer_size, Uint16 data_witdth, Uint16 link_num, Uint16 tcint )
{
	edma3ccRegs->PARAMSET[ch].OPT = 	  	  CSL_FMK(EDMA3CC_OPT_TCC, TCC_X) //팬딩 레지스터를 1번으로 지정
											| CSL_FMKT(EDMA3CC_OPT_SYNCDIM, ASYNC);

	if( tcint )
		edma3ccRegs->PARAMSET[ch].OPT |=   	  CSL_FMKT(EDMA3CC_OPT_TCINTEN, ENABLE); //다 마치고 나면 인터럽트 팬딩 레지스터에 1을 작성한다.

	edma3ccRegs->PARAMSET[ch].SRC = 	  	  src;
	edma3ccRegs->PARAMSET[ch].DST = 	  	  (Uint32)(&mcaspRegs->XBUF13);
	edma3ccRegs->PARAMSET[ch].A_B_CNT =    	  CSL_FMK(EDMA3CC_A_B_CNT_BCNT, ELEMENT_SIZE)
											| CSL_FMK(EDMA3CC_A_B_CNT_ACNT, data_witdth);
	edma3ccRegs->PARAMSET[ch].SRC_DST_BIDX =  CSL_FMK(EDMA3CC_SRC_DST_BIDX_SRCBIDX, buffer_size*data_witdth);
	edma3ccRegs->PARAMSET[ch].LINK_BCNTRLD =  CSL_FMK(EDMA3CC_LINK_BCNTRLD_BCNTRLD, ELEMENT_SIZE)
                                            | CSL_FMK(EDMA3CC_LINK_BCNTRLD_LINK ,(Uint32)(&(edma3ccRegs->PARAMSET[link_num])));
	edma3ccRegs->PARAMSET[ch].SRC_DST_CIDX =  CSL_FMK(EDMA3CC_SRC_DST_CIDX_SRCCIDX,-(buffer_size-1)*data_witdth);
	edma3ccRegs->PARAMSET[ch].CCNT = 		  buffer_size;
}


void EDMAReset( void )
{
	edma3ccRegs->EMCR 		= 0xFFFFFFFF;
	edma3ccRegs->CCERRCLR 	= 0xFFFFFFFF;
	edma3ccRegs->SECR 		= 0xFFFFFFFF;
	edma3ccRegs->ECR 		= 0xFFFFFFFF;
	edma3ccRegs->ICR 		= 0xFFFFFFFF;
	edma3ccRegs->EECR 		= 0xFFFFFFFF;
	edma3ccRegs->IECR 		= 0xFFFFFFFF;
}



	

	

