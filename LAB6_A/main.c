/*
 *  ======== main.c ========
 */

#include <xdc/std.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/BIOS.h>
#include <xdc/cfg/global.h>

#include <stdio.h>
#include "init.h"
#include "LED_DIPSW.h"


//#define INTERRUPT

#define ARRAY_SIZE      100
#define ELEMENT_SIZE    4

Int32 srcBuffer[ARRAY_SIZE];
Int32 dstBuffer[ARRAY_SIZE];


void GenArrayData( Int32 *src, Int32 *dst, Int32 len ) {
    Int32 i;

    for(i=0; i<len; i++ ) {
        src[i] = (i<<16) + (ARRAY_SIZE-i);
        dst[i] = 0;
    }
}


Int32 VerifyArrayData( Int32 *src, Int32 *dst, Int32 len ) {
    Int32 i;

    for(i=0; i<ARRAY_SIZE; i++ )
        if( src[i] != dst[i] ) {
            System_printf("\tTransfer fail!!!");
            return -1;
        }

    System_printf(">> Transfer Success!\n");
    return 0;
}


CSL_Edma3ccRegsOvly edma3ccRegs = (CSL_Edma3ccRegsOvly)(CSL_EDMA30CC_0_REGS);

void ResetEDMA3( void ) {
    edma3ccRegs->EMCR       = 0xFFFFFFFF;
    edma3ccRegs->CCERRCLR   = 0xFFFFFFFF;
    edma3ccRegs->SECR       = 0xFFFFFFFF;
    edma3ccRegs->ECR        = 0xFFFFFFFF;
    edma3ccRegs->ICR        = 0xFFFFFFFF;
    edma3ccRegs->EECR       = 0xFFFFFFFF;
    edma3ccRegs->IECR       = 0xFFFFFFFF;
}

void SetupEDMA3( Uint32 ch, Uint32 src, Uint32 dst, Uint32 elem_size, Uint32 frame_size )
{
//***********************************************************************
//  A-sync Timer trigger : ACNT : 4byte*ARRAY_SIZE, BCNT : 1, CCNT : 1
//***********************************************************************
    edma3ccRegs->PARAMSET[ch].OPT =             CSL_EDMA3CC_OPT_RESETVAL
                                                    | CSL_FMKT(EDMA3CC_OPT_TCINTEN, ENABLE)
                                                    | CSL_FMK(EDMA3CC_OPT_TCC, ch)
                                                    | CSL_FMKT(EDMA3CC_OPT_SYNCDIM, ASYNC);
    edma3ccRegs->PARAMSET[ch].SRC = src;
    edma3ccRegs->PARAMSET[ch].DST = dst;
    edma3ccRegs->PARAMSET[ch].A_B_CNT =         CSL_FMK(EDMA3CC_A_B_CNT_BCNT, 1)
                                                    | CSL_FMK(EDMA3CC_A_B_CNT_ACNT, elem_size*frame_size);
    edma3ccRegs->PARAMSET[ch].SRC_DST_BIDX =    CSL_FMK(EDMA3CC_SRC_DST_BIDX_DSTBIDX, 0)
                                                    | CSL_FMK(EDMA3CC_SRC_DST_BIDX_SRCBIDX, 0);
    edma3ccRegs->PARAMSET[ch].LINK_BCNTRLD =    CSL_FMK(EDMA3CC_LINK_BCNTRLD_LINK, 0xFFFF);
    edma3ccRegs->PARAMSET[ch].SRC_DST_CIDX = 0;
    edma3ccRegs->PARAMSET[ch].CCNT = 1;


//***********************************************************************
//  AB-sync Timer trigger : ACNT : 4byte, BCNT : ARRAY_SIZE, CCNT : 1
//***********************************************************************

/*
    edma3ccRegs->PARAMSET[ch].OPT =             CSL_EDMA3CC_OPT_RESETVAL
                                                    | CSL_FMKT(EDMA3CC_OPT_TCINTEN, ENABLE)
                                                    | CSL_FMK(EDMA3CC_OPT_TCC, ch)
                                                    | CSL_FMKT(EDMA3CC_OPT_SYNCDIM, ABSYNC);
    edma3ccRegs->PARAMSET[ch].SRC = src;
    edma3ccRegs->PARAMSET[ch].DST = dst;
    edma3ccRegs->PARAMSET[ch].A_B_CNT =         CSL_FMK(EDMA3CC_A_B_CNT_BCNT, frame_size)
                                                    | CSL_FMK(EDMA3CC_A_B_CNT_ACNT, elem_size);
    edma3ccRegs->PARAMSET[ch].SRC_DST_BIDX =    CSL_FMK(EDMA3CC_SRC_DST_BIDX_DSTBIDX, ELEMENT_SIZE)
                                                    | CSL_FMK(EDMA3CC_SRC_DST_BIDX_SRCBIDX, ELEMENT_SIZE);
    edma3ccRegs->PARAMSET[ch].LINK_BCNTRLD =    CSL_FMK(EDMA3CC_LINK_BCNTRLD_LINK, 0xFFFF);
    edma3ccRegs->PARAMSET[ch].SRC_DST_CIDX = 0;
    edma3ccRegs->PARAMSET[ch].CCNT = 1;
*/
}

volatile int edma_done = 0;

void EDMA3_CC0_INT( void ){
    edma_done = 1;
}

void main()
{
    puts("\n=====================================================");
    puts("          Lab6_A - Move Data using EDMA");
    puts("=====================================================");

    SysConfigForPinMux( );
    LED_DIPSW_Init( );

    GenArrayData( srcBuffer, dstBuffer, ARRAY_SIZE ); //배열, 배열 ,100

    ResetEDMA3( );
    SetupEDMA3( EDMA_EVENT5,  (Uint32)srcBuffer, (Uint32)dstBuffer, ELEMENT_SIZE, ARRAY_SIZE );

    BIOS_start( );
}


void Task_edma( void )
{
    EnableInterrupt(INT_6);
    CSL_FINST(edma3ccRegs->IESR, EDMA3CC_IESR_I5, SET);
    CSL_FINST(edma3ccRegs->DRA[CSL_EDMA3_REGION_1].DRAE, EDMA3CC_DRAE_E5, ENABLE);
    CSL_FINST(edma3ccRegs->ESR, EDMA3CC_ESR_E5, SET);

    while( edma_done == 0 );

    VerifyArrayData( srcBuffer, dstBuffer, ARRAY_SIZE );

    System_printf(">> Program Terminated!\n");
    BIOS_exit( 0 );
}



