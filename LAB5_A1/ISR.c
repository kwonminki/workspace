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
static Uint8 pb = PUSH_UP;


#define PI 3.141592654
#define FREQ 300.f

#define W (2.*PI*FREQ/SAMPLING_FREQ)

void MCASP_ISR( void ){
    Uint32 sample_data;
//    Int16 left, right;
//    static int sample_cnt = 0;
    static int index = 0;

    sample_data = mcaspRegs->RBUF14;

    if( pb==PUSH_UP ){
        mcaspRegs->XBUF13 = sample_data;
    }
    else{
        Int16 val = 10000.*sin(W*index++);
        if(index == SAMPLING_FREQ){
            index = 0;
        }
        mcaspRegs->XBUF13 = (val << 16)|(val & 0xFFFF);
    }

    led_cnt++;
}

void IdleLED( void ){
    if( led_cnt == (SAMPLING_FREQ>>1) ){
        LED_Toggle(LED_D4);
        led_cnt = 0;
    }
}

void IdlePButton( void ){
    pb = GetPushButton_Status( PUSH_BTN_1 );
}
