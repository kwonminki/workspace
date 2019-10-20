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
#include <math.h>

static Int32 led_cnt = 0;

void MCASP_ISR( void ){
    Int16 out_val;
    static Int16 prev=0;
    extern volatile float omega;
    extern volatile Int32 time_index;
    extern volatile Int16 done, temp_done;

    Uint32 dummy = mcaspRegs->RBUF14;

    out_val = (Int16)(15000.*sinf( omega*time_index ) );

    if( ++time_index == SAMPLING_FREQ ){
        time_index = 0;
    }

    mcaspRegs->XBUF13 = (out_val << 16)|(out_val & 0xFFFF);

    if(temp_done == 1 ){
        if( prev < 0 && out_val >= 0){
            done =1;
        }
    }

    prev = out_val;

    led_cnt++;
}

void IdleLED( void ){
    if( led_cnt == (SAMPLING_FREQ>>1) ){
        LED_Toggle(LED_D4);
        led_cnt = 0;
    }
}

void IdlePButton( void ){

}
