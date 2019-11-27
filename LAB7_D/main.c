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



static void SetupEDMA3( QueObj *que ){
    EDMAReset();

    //For Receiver
    ConfigEDMAForR( R_LINK_PING, (Uint32)( que[0].rt_buf->in_L), BUFLEN, ELEMENT_SIZE, R_LINK_PONG, TCINT );
    ConfigEDMAForR( R_LINK_PONG, (Uint32)(que[1].rt_buf->in_L), BUFLEN, ELEMENT_SIZE, R_LINK_PING, TCINT );
                    //32��, 33���� �ش��ϴ� RAMSET�� ���ɼ��� �ۼ��ϴ� ���̴�. ���ο��� ��ũ�� �ɾ�д�.
    ConfigEDMAForR( REVT, (Uint32)(que[0].rt_buf->in_L), BUFLEN, ELEMENT_SIZE, R_LINK_PONG, TCINT );
                    //ä�� 0�� ���ɼ��ε� ������ ������ ��ũ�ȴ�. �� ī���ؿͼ� ����.
    //For Transmitter
    ConfigEDMAForX( X_LINK_PING, (Uint32)(que[0].rt_buf->in_L), BUFLEN, ELEMENT_SIZE, X_LINK_PONG, TCINT );
    ConfigEDMAForX( X_LINK_PONG, (Uint32)(que[1].rt_buf->in_L), BUFLEN, ELEMENT_SIZE, X_LINK_PING, TCINT );
                    //�´� ���� �ش��ϴ� RAMSET�� ���ɼ��� �ۼ��ϴ� ���̴�. ���ο��� ��ũ�� �ɾ�д�.
    ConfigEDMAForX( XEVT, (Uint32)(que[0].rt_buf->in_L), BUFLEN, ELEMENT_SIZE, X_LINK_PONG, TCINT );
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
    void InitQue( QuePtr que ); //�Ǵ� QueObj *que ��� ���� �־��൵ ����.
    static QueObj que[2];

    puts("LAB7D - Ping-Pong Buffer Processing(EDMA, Linking, Channel Sorting, Queue)\n");

    SysConfigForPinMux();
    LED_DIPSW_Init();
    I2C_Init( 400 );

    //ClearBuffer(); �̰� ���� InitQue�� ��������.
    InitQue( que );

    CodecInit( SAMPLING_FREQ, WORD_LEN_16BIT, LINE_IN );
    ConfigMcASP( MCASP_16BIT, MCASP_2SLOT, CFG, NO_RINT, NO_XINT ); //����!


    SetupEDMA3(que);

    EnableInterrupt( INT_5 );


    InitMcASP( RECEIVE, CFG );
    InitMcASP( TRANSMIT, CFG );

    BIOS_start();
}