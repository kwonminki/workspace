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


#include "image.h"

#define TRIGGER 0

#define LINES_PER_DISP  (Y_SIZE*3)
#define PIXELS_PER_LINE (X_SIZE*3)
#define PIXELS_IN_IMAGE (LINES_PER_DISP*PIXELS_PER_LINE)

#pragma DATA_SECTION( image, ".image")
Uint8 image[PIXELS_IN_IMAGE];

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


#if TRIGGER
void SetupEDMA3( void )
{

    Uint32 edma_evt;

    edma_evt = EDMA_EVENT5;

    edma3ccRegs->PARAMSET[edma_evt].SRC = (Uint32)image;
    edma3ccRegs->PARAMSET[edma_evt].DST = (Uint32)image + PIXELS_IN_IMAGE/3 + PIXELS_PER_LINE/3;

    edma3ccRegs->PARAMSET[edma_evt].OPT =             CSL_EDMA3CC_OPT_RESETVAL
                                                    | CSL_FMKT(EDMA3CC_OPT_TCINTEN, ENABLE)
                                                    | CSL_FMK(EDMA3CC_OPT_TCC, edma_evt)
                                                    | CSL_FMKT(EDMA3CC_OPT_SYNCDIM, ABSYNC);

    edma3ccRegs->PARAMSET[edma_evt].A_B_CNT =         CSL_FMK(EDMA3CC_A_B_CNT_BCNT, Y_SIZE)
                                                    | CSL_FMK(EDMA3CC_A_B_CNT_ACNT, X_SIZE);
    edma3ccRegs->PARAMSET[edma_evt].SRC_DST_BIDX =    CSL_FMK(EDMA3CC_SRC_DST_BIDX_DSTBIDX, PIXELS_PER_LINE)
                                                    | CSL_FMK(EDMA3CC_SRC_DST_BIDX_SRCBIDX, PIXELS_PER_LINE);
    edma3ccRegs->PARAMSET[edma_evt].LINK_BCNTRLD =    CSL_FMK(EDMA3CC_LINK_BCNTRLD_LINK, 0xFFFF);
    edma3ccRegs->PARAMSET[edma_evt].SRC_DST_CIDX = 0;
    edma3ccRegs->PARAMSET[edma_evt].CCNT = 1;
}

#else
void SetupEDMA3( int i, int j )
{
    Uint32 edma_evt;

    edma_evt = EDMA_EVENT5;

    edma3ccRegs->PARAMSET[edma_evt].SRC = (Uint32)image;
    edma3ccRegs->PARAMSET[edma_evt].DST = (Uint32)image + i*PIXELS_IN_IMAGE/3 + j*PIXELS_PER_LINE/3;

    edma3ccRegs->PARAMSET[edma_evt].OPT =             CSL_EDMA3CC_OPT_RESETVAL
                                                    | CSL_FMKT(EDMA3CC_OPT_TCINTEN, ENABLE)
                                                    | CSL_FMK(EDMA3CC_OPT_TCC, edma_evt)
                                                    | CSL_FMKT(EDMA3CC_OPT_SYNCDIM, ABSYNC);

    edma3ccRegs->PARAMSET[edma_evt].A_B_CNT =         CSL_FMK(EDMA3CC_A_B_CNT_BCNT, Y_SIZE)
                                                    | CSL_FMK(EDMA3CC_A_B_CNT_ACNT, X_SIZE);
    edma3ccRegs->PARAMSET[edma_evt].SRC_DST_BIDX =    CSL_FMK(EDMA3CC_SRC_DST_BIDX_DSTBIDX, PIXELS_PER_LINE)
                                                    | CSL_FMK(EDMA3CC_SRC_DST_BIDX_SRCBIDX, PIXELS_PER_LINE);
    edma3ccRegs->PARAMSET[edma_evt].LINK_BCNTRLD =    CSL_FMK(EDMA3CC_LINK_BCNTRLD_LINK, 0xFFFF);
    edma3ccRegs->PARAMSET[edma_evt].SRC_DST_CIDX = 0;
    edma3ccRegs->PARAMSET[edma_evt].CCNT = 1;
}
#endif

void SetupEDMA3Down( int i, int j )
{
    Uint32 edma_evt;

    edma_evt = EDMA_EVENT5;

    edma3ccRegs->PARAMSET[edma_evt].SRC = (Uint32)image;
    edma3ccRegs->PARAMSET[edma_evt].DST = (Uint32)image + i*PIXELS_IN_IMAGE/6 + j*PIXELS_PER_LINE/6; //보내는 위치가 6분의 1

    edma3ccRegs->PARAMSET[edma_evt].OPT =             CSL_EDMA3CC_OPT_RESETVAL
                                                    | CSL_FMKT(EDMA3CC_OPT_TCINTEN, ENABLE)
                                                    | CSL_FMKT(EDMA3CC_OPT_ITCCHEN, ENABLE)
                                                    | CSL_FMK(EDMA3CC_OPT_TCC, edma_evt)
                                                    | CSL_FMKT(EDMA3CC_OPT_SYNCDIM, ABSYNC);

    edma3ccRegs->PARAMSET[edma_evt].A_B_CNT =         CSL_FMK(EDMA3CC_A_B_CNT_BCNT, X_SIZE/2)
                                                    | CSL_FMK(EDMA3CC_A_B_CNT_ACNT, 1);
    edma3ccRegs->PARAMSET[edma_evt].SRC_DST_BIDX =    CSL_FMK(EDMA3CC_SRC_DST_BIDX_DSTBIDX, 1)
                                                    | CSL_FMK(EDMA3CC_SRC_DST_BIDX_SRCBIDX, 2);
    edma3ccRegs->PARAMSET[edma_evt].LINK_BCNTRLD =    CSL_FMK(EDMA3CC_LINK_BCNTRLD_LINK, 0xFFFF);
    edma3ccRegs->PARAMSET[edma_evt].SRC_DST_CIDX =    CSL_FMK(EDMA3CC_SRC_DST_CIDX_DSTCIDX, PIXELS_PER_LINE)
                                                    | CSL_FMK(EDMA3CC_SRC_DST_CIDX_SRCCIDX, PIXELS_PER_LINE*2);
    edma3ccRegs->PARAMSET[edma_evt].CCNT = Y_SIZE/2;
}

void SetupEDMA3Up( Int32 ch, Int32 offset )
{


    edma3ccRegs->PARAMSET[ch].SRC = (Uint32)image;
    edma3ccRegs->PARAMSET[ch].DST = (Uint32)image + PIXELS_IN_IMAGE/3 + PIXELS_PER_LINE/3 + offset; //전체의 3분의 1 지점.

    edma3ccRegs->PARAMSET[ch].OPT =             CSL_EDMA3CC_OPT_RESETVAL
                                                    | CSL_FMKT(EDMA3CC_OPT_TCINTEN, ENABLE)
                                                    | CSL_FMKT(EDMA3CC_OPT_ITCCHEN, ENABLE)
                                                    | CSL_FMK(EDMA3CC_OPT_TCC, ch)
                                                    | CSL_FMKT(EDMA3CC_OPT_SYNCDIM, ABSYNC);

    edma3ccRegs->PARAMSET[ch].A_B_CNT =         CSL_FMK(EDMA3CC_A_B_CNT_BCNT, X_SIZE)
                                                    | CSL_FMK(EDMA3CC_A_B_CNT_ACNT, 1);
    edma3ccRegs->PARAMSET[ch].SRC_DST_BIDX =    CSL_FMK(EDMA3CC_SRC_DST_BIDX_DSTBIDX, 2)
                                                    | CSL_FMK(EDMA3CC_SRC_DST_BIDX_SRCBIDX, 1);
    edma3ccRegs->PARAMSET[ch].LINK_BCNTRLD =    CSL_FMK(EDMA3CC_LINK_BCNTRLD_LINK, 0xFFFF);
    edma3ccRegs->PARAMSET[ch].SRC_DST_CIDX =    CSL_FMK(EDMA3CC_SRC_DST_CIDX_DSTCIDX, PIXELS_PER_LINE*2)
                                                    | CSL_FMK(EDMA3CC_SRC_DST_CIDX_SRCCIDX, PIXELS_PER_LINE);
    edma3ccRegs->PARAMSET[ch].CCNT = Y_SIZE;
}

void main()
{
    Int32 i, j, k=0;

    puts("\n=====================================================");
    puts("          Lab6C - Scaled 2D Memory Move");
    puts("=====================================================");

    SysConfigForPinMux( );
    LED_DIPSW_Init( );

    for(i=0; i < PIXELS_IN_IMAGE;i++)
            image[i] = 200;                 // gray background

    for( i=0; i < Y_SIZE; i++ )
        for( j=0; j < X_SIZE; j++ )
            image[i*PIXELS_PER_LINE + j] = org_img[k++];
    puts("stop here");
    BIOS_start( );
}


void Task_edma( void )
{

#if !TRIGGER
    Int32 i, j;
    for( i=2; i<6; i++){
        for( j=0; j<2; j++){
            ResetEDMA3( );
            SetupEDMA3Down( i, j );
            CSL_FINST(edma3ccRegs->ESR, EDMA3CC_ESR_E5, SET);
            while( (edma3ccRegs->IPR & (1<< EDMA_EVENT5)) == 0 );
        }
    }
    for( i=2; i<6; i++){
        for( j=0; j<2; j++){
            ResetEDMA3( );
            SetupEDMA3Down( j, i );
            CSL_FINST(edma3ccRegs->ESR, EDMA3CC_ESR_E5, SET);
            while( (edma3ccRegs->IPR & (1<< EDMA_EVENT5)) == 0 );
        }
    }
#else

  ResetEDMA3( );
  SetupEDMA3Down(2, 2);
  CSL_FINST(edma3ccRegs->ESR, EDMA3CC_ESR_E5, SET);
  while( (edma3ccRegs->IPR & (1<< EDMA_EVENT5)) == 0 );

#endif


      ResetEDMA3( );

      SetupEDMA3Up(EDMA_EVENT5, 0);
      CSL_FINST(edma3ccRegs->ESR, EDMA3CC_ESR_E5, SET);

      SetupEDMA3Up(EDMA_EVENT6, 1);
      CSL_FINST(edma3ccRegs->ESR, EDMA3CC_ESR_E6, SET);

      SetupEDMA3Up(EDMA_EVENT7, PIXELS_PER_LINE);
      CSL_FINST(edma3ccRegs->ESR, EDMA3CC_ESR_E7, SET);

      SetupEDMA3Up(EDMA_EVENT8, PIXELS_PER_LINE+1);
      CSL_FINST(edma3ccRegs->ESR, EDMA3CC_ESR_E8, SET);


      while( (edma3ccRegs->IPR & (1<< EDMA_EVENT5)) == 0 );
      while( (edma3ccRegs->IPR & (1<< EDMA_EVENT6)) == 0 );
      while( (edma3ccRegs->IPR & (1<< EDMA_EVENT7)) == 0 );
      while( (edma3ccRegs->IPR & (1<< EDMA_EVENT8)) == 0 );





    System_printf(">> Program Terminated!\n");

    BIOS_exit( 0 );
}



