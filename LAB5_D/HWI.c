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

void MCASP_ISR( void ){
    static int sample_cnt = 0;
    static Uint32 *in = in_ping_buffer, *out = out_ping_buffer;
    static Int32 which_buffer = PING;

    in[sample_cnt] = mcaspRegs->RBUF14;
    mcaspRegs->XBUF13 = out[sample_cnt++];

    if(sample_cnt == BUFLEN ){
        sample_cnt = 0;

        //SWI를 불러와줘야한다.포스팅.

        Swi_or( swi0, which_buffer ); // 포스팅

        if( which_buffer == PING ){
            in = in_pong_buffer;
            out= out_pong_buffer;
        }
        else{
            in = in_ping_buffer;
            out= out_ping_buffer;
        }

        which_buffer = ~which_buffer;
    }

    led_cnt++;
}


void IdleLED( void ){
    if( led_cnt == (SAMPLING_FREQ>>1) ){
        LED_Toggle(LED_D4);
        led_cnt = 0;
    }
}
