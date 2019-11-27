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
                    //32번, 33번에 해당하는 RAMSET에 명령서를 작성하는 것이다. 서로에게 링크를 걸어둔다.
    ConfigEDMAForR( REVT, (Uint32)(que[0].rt_buf->in_L), BUFLEN, ELEMENT_SIZE, R_LINK_PONG, TCINT );
                    //채널 0번 명령서인데 끝나면 퐁에게 링크된다. 즉 카피해와서 쓴다.
    //For Transmitter
    ConfigEDMAForX( X_LINK_PING, (Uint32)(que[0].rt_buf->in_L), BUFLEN, ELEMENT_SIZE, X_LINK_PONG, TCINT );
    ConfigEDMAForX( X_LINK_PONG, (Uint32)(que[1].rt_buf->in_L), BUFLEN, ELEMENT_SIZE, X_LINK_PING, TCINT );
                    //맞는 곳에 해당하는 RAMSET에 명령서를 작성하는 것이다. 서로에게 링크를 걸어둔다.
    ConfigEDMAForX( XEVT, (Uint32)(que[0].rt_buf->in_L), BUFLEN, ELEMENT_SIZE, X_LINK_PONG, TCINT );
                    //끝나면 퐁에게 링크된다. 즉 카피해와서 쓴다.



    CSL_FINST( edma3ccRegs->EESR, EDMA3CC_EESR_E0, SET );
               //이벤트 레지스터를 위해서 이벤트 인에이블 셋 레지스터
    CSL_FINST( edma3ccRegs->EESR, EDMA3CC_EESR_E1, SET );

    CSL_FINST( edma3ccRegs->IESR, EDMA3CC_EESR_E0, SET );
                //인터럽트 세트 레지스터
                //참고. IPR은 자동으로 지워지지 않는다.
    CSL_FINST( edma3ccRegs->DRA[CSL_EDMA3_REGION_1].DRAE, EDMA3CC_DRAE_E0, ENABLE );
                //DMA소관이라고 알려줌.
}
/*
 *  ======== main ========
 */
void main()
{
    void InitQue( QuePtr que ); //또는 QueObj *que 라고 인자 넣어줘도 같다.
    static QueObj que[2];

    puts("LAB7D - Ping-Pong Buffer Processing(EDMA, Linking, Channel Sorting, Queue)\n");

    SysConfigForPinMux();
    LED_DIPSW_Init();
    I2C_Init( 400 );

    //ClearBuffer(); 이걸 이제 InitQue에 구현하자.
    InitQue( que );

    CodecInit( SAMPLING_FREQ, WORD_LEN_16BIT, LINE_IN );
    ConfigMcASP( MCASP_16BIT, MCASP_2SLOT, CFG, NO_RINT, NO_XINT ); //여기!


    SetupEDMA3(que);

    EnableInterrupt( INT_5 );


    InitMcASP( RECEIVE, CFG );
    InitMcASP( TRANSMIT, CFG );

    BIOS_start();
}
