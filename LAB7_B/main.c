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
    ConfigEDMAForR( R_LINK_PING, (Uint32)(in_ping_buffer[0]), BUFLEN, ELEMENT_SIZE, R_LINK_PONG, TCINT );
    ConfigEDMAForR( R_LINK_PONG, (Uint32)(in_pong_buffer[0]), BUFLEN, ELEMENT_SIZE, R_LINK_PING, TCINT );
                    //32��, 33���� �ش��ϴ� RAMSET�� ��ɼ��� �ۼ��ϴ� ���̴�. ���ο��� ��ũ�� �ɾ�д�.
    ConfigEDMAForR( REVT, (Uint32)(in_ping_buffer[0]), BUFLEN, ELEMENT_SIZE, R_LINK_PONG, TCINT );
                    //ä�� 0�� ��ɼ��ε� ������ ������ ��ũ�ȴ�. �� ī���ؿͼ� ����.
    //For Transmitter
    ConfigEDMAForX( X_LINK_PING, (Uint32)(out_ping_buffer[0]), BUFLEN, ELEMENT_SIZE, X_LINK_PONG, TCINT );
    ConfigEDMAForX( X_LINK_PONG, (Uint32)(out_pong_buffer[0]), BUFLEN, ELEMENT_SIZE, X_LINK_PING, TCINT );
                    //�´� ���� �ش��ϴ� RAMSET�� ��ɼ��� �ۼ��ϴ� ���̴�. ���ο��� ��ũ�� �ɾ�д�.
    ConfigEDMAForX( XEVT, (Uint32)(out_ping_buffer[0]), BUFLEN, ELEMENT_SIZE, X_LINK_PONG, TCINT );
                    //������ ������ ��ũ�ȴ�. �� ī���ؿͼ� ����.



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

    puts("LAB7B - Ping-Pong Buffer Processing(EDMA, Linking, Channel Sorting)\n");

    SysConfigForPinMux();
    LED_DIPSW_Init();
    I2C_Init( 400 );

    ClearBuffer();

    CodecInit( SAMPLING_FREQ, WORD_LEN_16BIT, LINE_IN );
    ConfigMcASP( MCASP_16BIT, MCASP_2SLOT, CFG, NO_RINT, NO_XINT ); //����!


    SetupEDMA3( );

    EnableInterrupt( INT_5 );


    InitMcASP( RECEIVE, CFG );
    InitMcASP( TRANSMIT, CFG );

    BIOS_start();
}
