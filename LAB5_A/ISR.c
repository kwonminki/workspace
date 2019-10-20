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
static Uint8 pb = PUSH_UP;

#define BUFLEN (SAMPLING_FREQ/2) // 1/8초에 해당하는 데이터 분량.
static Uint32 data[BUFLEN];

void ClearBuffer( void ){
    for(int i=0; i<BUFLEN; i++){
        data[i] = 0;
    }
}

void MCASP_ISR( void ){
    Uint32 sample_data;
    Int16 left, right;
    static int sample_cnt = 0;

    sample_data = mcaspRegs->RBUF14;

    if( pb==PUSH_UP ){
        mcaspRegs->XBUF13 = data[sample_cnt];
    }
    else{
        right = (sample_data>>16);
        left = (data[sample_cnt] & 0xFFFF);
        mcaspRegs->XBUF13 = (right << 16)|(left & 0xFFFF);
    }

    data[sample_cnt++] = sample_data;


    if(sample_cnt == BUFLEN ){
        sample_cnt = 0;
    } //1/8초 딜레이

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
