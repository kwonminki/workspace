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
#include "define.h"

static Int32 led_cnt = 0;
void MCASP_ISR( void ){
    Uint32 sample_data;
    Int16 left, right;

    sample_data = mcaspRegs->RBUF14;

    right = sample_data>>16;
    //right = sample_data & 0xFFFF;
    left = 0;
    mcaspRegs->XBUF13 = (right << 16)|(left & 0xFFFF);

    led_cnt++;
}

void IdleLED( void ){
    if( led_cnt == (SAMPLING_FREQ>>1) ){
        LED_Toggle(LED_D4);
        led_cnt = 0;
    }
}
