/*
 *  ======== main.c ========
 */

#include <xdc/std.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/BIOS.h>
#include <xdc/cfg/global.h>
#include <stdio.h>
#include "init.h"
#include "define.h"

static void SetupEDMA3( void ){
    EDMAReset();

    //For Receiver
    ConfigEDMAForR( REVT, (Uint32)in_ping_buffer, BUFLEN, ELEMENT_SIZE, REVT, TCINT );
                    //ä�� 0�� ��ɼ��ε� ������ �ڱ��ڽ��� ����� �����Ѵ�.

    //For Transmitter
    ConfigEDMAForX( XEVT, (Uint32)out_ping_buffer, BUFLEN, ELEMENT_SIZE, XEVT, TCINT );
                    //^�̰� �� �ȹٲ�?(�����Ѱ� �ƴ�?)

    CSL_FINST( edma3ccRegs->EESR, EDMA3CC_EESR_E0, SET );
               //�̺�Ʈ �������͸� ���ؼ� �̺�Ʈ �ο��̺� �� ��������
    CSL_FINST( edma3ccRegs->EESR, EDMA3CC_EESR_E1, SET );

    CSL_FINST( edma3ccRegs->IESR, EDMA3CC_EESR_E0, SET );
                //���ͷ�Ʈ ��Ʈ ��������
                //����. IPR�� �ڵ����� �������� �ʴ´�.
    CSL_FINST( edma3ccRegs->DRA[CSL_EDMA3_REGION_1].DRAE, EDMA3CC_DRAE_E0, ENABLE );
                //DMA�Ұ��̶�� �˷���.
}
/*
 *  ======== main ========
 */
void main()
{
    void ClearBuffer( void );

    puts("LAB7 - Ping-Pong Buffer Processing(EDMA)\n");

    SysConfigForPinMux();
    LED_DIPSW_Init();
    I2C_Init( 400 );

    ClearBuffer();

    CodecInit( SAMPLING_FREQ, WORD_LEN_16BIT, LINE_IN );
    ConfigMcASP( MCASP_32BIT, MCASP_1SLOT, CFG, NO_RINT, NO_XINT ); //���� RINT�� �ʿ����


    SetupEDMA3( );

    EnableInterrupt( INT_5 );


    InitMcASP( RECEIVE, CFG );
    InitMcASP( TRANSMIT, CFG );

    BIOS_start();
}
