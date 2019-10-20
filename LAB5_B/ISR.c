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
#include "sine.h"

static Int32 led_cnt = 0;
static Uint8 pb = PUSH_UP;

#define BUFLEN 50 // 1/8초에 해당하는 데이터 분량.
Uint32 in_buffer[BUFLEN];
Uint32 out_buffer[BUFLEN];

void ClearBuffer( void ){
    for(int i=0; i<BUFLEN; i++){
        in_buffer[i] = 0;
        out_buffer[i] = 0;
    }
}

float sine[BUFLEN];

void MCASP_ISR( void ){
//    Uint32 sample_data;
    Int16 left, right;
    static int sample_cnt = 0;
    static int index = 0;

    in_buffer[sample_cnt] = mcaspRegs->RBUF14;

    mcaspRegs->XBUF13 = out_buffer[sample_cnt++];

    if(sample_cnt == BUFLEN ){
        sample_cnt = 0;

        if( pb == PUSH_UP){
            for( int i=0; i< BUFLEN; i++){
                out_buffer[i] = in_buffer[i];
            }
        }
        else{
            index = GenSine( sine, 1.f, SAMPLING_FREQ, BUFLEN, index );
            for( int i=0; i< BUFLEN; i++){
                right = (in_buffer[i]>>16);
                left = (in_buffer[i] & 0xFFFF);

                left *= sine[i];
                right *= sine[i];

                out_buffer[i] = (right << 16)|(left & 0xFFFF);
            }
        }
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
