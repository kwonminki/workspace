/*
 * ISR.c
 *
 *  Created on: 2019. 10. 8.
 *      Author: user
 */

#include <xdc/std.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/BIOS.h>
#include <xdc/cfg/global.h>
#include <ti/sysbios/knl/Swi.h>
#include "define.h"



static Int32 led_cnt = 0;

void EDMA3_CC_ISR( void ){//여기에 들어오는 순간은 EDMA에 의해 버퍼 하나가 다 채워진 순간이다. 그러면 이제 뭘 해야 할까? 명령서를 다시 줘야 한다.
    //가장 먼저 해줘야 할 일은 IPR 즉 인터럽트 팬딩 레지스터를 지워주는 것이다. 이걸 지워놓지 않으면 인터럽트가 계속 걸린다..
    static Int32 which_buffer = PING;

    CSL_FINST( edma3ccRegs->ICR, EDMA3CC_ICR_I0, CLEAR ); //IPR은 직접 지우는 것이 아닌 ICR을 통해 지운다.
    while( CSL_FEXT( edma3ccRegs->IPR, EDMA3CC_IPR_I1 ) != CSL_EDMA3CC_IPR_I1_YES );
                  //특정 비트를 뽑아내는 것. IPR에 접근해서 아웃 버퍼도 바뀌었는지 본다.
    CSL_FINST( edma3ccRegs->ICR, EDMA3CC_ICR_I1, CLEAR );

    Swi_or( swi0, which_buffer );
    which_buffer = ~which_buffer;

    led_cnt++;
}


void IdleLED( void ){
    if( led_cnt == (SAMPLING_FREQ>>1) ){
        LED_Toggle(LED_D4);
        led_cnt = 0;
    }
}


