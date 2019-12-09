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

// LAB7C 는 이전 핑퐁버퍼 그냥 구조체로 바꿔서 코드 편하게 만든것 뿐임

static void SetupEDMA3( QueObj *que ){
    EDMAReset();


    //For Receiver
    ConfigEDMAForR( R_LINK_PING, (Uint32)( que[0].rt_buf->in_L), BUFLEN, ELEMENT_SIZE, R_LINK_PONG, TCINT );
    ConfigEDMAForR( R_LINK_PONG, (Uint32)( que[1].rt_buf->in_L), BUFLEN, ELEMENT_SIZE, R_LINK_PING, TCINT );
                    //32번, 33번에 해당하는 RAMSET에 명령서를 작성하는 것이다. 서로에게 링크를 걸어둔다.
    ConfigEDMAForR( REVT, (Uint32)( que[0].rt_buf->in_L), BUFLEN, ELEMENT_SIZE, R_LINK_PONG, TCINT );
                    //채널 0번 명령서인데 끝나면 퐁에게 링크된다. 즉 카피해와서 쓴다.
    //For Transmitter
    ConfigEDMAForX( X_LINK_PING, (Uint32)( que[0].rt_buf->out_L), BUFLEN, ELEMENT_SIZE, X_LINK_PONG, TCINT );
    ConfigEDMAForX( X_LINK_PONG, (Uint32)( que[1].rt_buf->out_L), BUFLEN, ELEMENT_SIZE, X_LINK_PING, TCINT );
                    //맞는 곳에 해당하는 RAMSET에 명령서를 작성하는 것이다. 서로에게 링크를 걸어둔다.
    ConfigEDMAForX( XEVT, (Uint32)( que[0].rt_buf->out_L), BUFLEN, ELEMENT_SIZE, X_LINK_PONG, TCINT );
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
    //void InitQue( QueObj *que );   //아래랑 같은거임
    void InitQue( QuePtr que );
    void ClearBufferAll(void);

    static QueObj que[2]; // 실제 버퍼가 들어가는 스태틱으로 선언되는 큐


    puts("TEST2 for final exam \n");  // 버튼 누를 때마다 모드 변경      원음->LPF->HPF->무음->원음

    // 원래 핑퐁 버퍼를 구별하기 위해서 휘치버퍼 플래그를 사용해서 어느 버퍼가 꽉찼으면 서로 스위치하고 하는 동작을 했었는데
    // 이제는 그 동작을 큐를 이용해서 할것임 큐의 개념을 이욯해서 핑버퍼 퐁버퍼를 순서대로 넣으면 알아서 순서대로 바뀔것임

    SysConfigForPinMux();
    LED_DIPSW_Init();
    I2C_Init( 400 );

    InitQue( que ); //큐 초기화가 있기 때문에 클리어 버퍼 불필요
    ClearBufferAll();

    CodecInit( SAMPLING_FREQ, WORD_LEN_16BIT, LINE_IN );
    ConfigMcASP( MCASP_16BIT, MCASP_2SLOT, CFG, NO_RINT, NO_XINT ); //여기!


    SetupEDMA3( que );

    EnableInterrupt( INT_5 );


    InitMcASP( RECEIVE, CFG );
    InitMcASP( TRANSMIT, CFG );

    BIOS_start();
}
