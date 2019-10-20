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
#include "sine.h"

static Int32 led_cnt = 0;
static Uint8 pb = PUSH_UP;
static Int32 which_buffer = PING;

Uint32 in_ping_buffer[BUFLEN];
Uint32 in_pong_buffer[BUFLEN];
Uint32 out_ping_buffer[BUFLEN];
Uint32 out_pong_buffer[BUFLEN];

void ClearBuffer( void ){
    for(int i=0; i<BUFLEN; i++){
        out_ping_buffer[i] = 0;
        out_pong_buffer[i] = 0;
    }
}

float sine[BUFLEN];

void MCASP_ISR( void ){
    static int sample_cnt = 0;
    static Uint32 *in = in_ping_buffer, *out = out_ping_buffer;

    in[sample_cnt] = mcaspRegs->RBUF14;
    mcaspRegs->XBUF13 = out[sample_cnt++];

    if(sample_cnt == BUFLEN ){
        sample_cnt = 0;

        //SWI를 불러와줘야한다.포스팅.

        Swi_post( swi0 ); // 포스팅

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

void ProcessSWI( void ){
//    Uint32 sample_data;
    Int16 left, right;
    Uint32 *in, *out;
    static int index = 0;

    if( which_buffer == PING ){
        in = in_pong_buffer;
        out= out_pong_buffer;
    }
    else{
        in = in_ping_buffer;
        out= out_ping_buffer;
    }

    if( pb == PUSH_UP){
        for( int i=0; i< BUFLEN; i++){
            out[i] = in[i];
        }
    }
    else{
        index = GenSine( sine, 1.f, SAMPLING_FREQ, BUFLEN, index );
        for( int i=0; i< BUFLEN; i++){
            right = (in[i]>>16);
            left = (in[i] & 0xFFFF);

            left *= sine[i];
            right *= sine[i];

            out[i] = (right << 16)|(left & 0xFFFF);
        }
    }


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
