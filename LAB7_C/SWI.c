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

RT_buf ping, pong;

static Uint8 pb = PUSH_UP;
static float sine[BUFLEN];

void ProcessSWI( void ){
//    Uint32 sample_data;
    Int16 *in_L, *in_R, *out_L, *out_R;
    static int index = 0;

    Int32 which_buffer = Swi_getTrigger();

    if( which_buffer == PONG ){
        in_L = pong.in_L;
        in_R = pong.in_R;
        out_L = pong.out_L;
        out_R = pong.out_R;
    }
    else{
        in_L = ping.in_L;
        in_R = ping.in_R;
        out_L = ping.out_L;
        out_R = ping.out_R;
    }

    if( pb == PUSH_UP){
        for( int i=0; i< BUFLEN; i++){


            out_L[i] = in_L[i];
            out_R[i] = in_R[i];
        }
    }
    else{
        index = GenSine( sine, 1.f, SAMPLING_FREQ, BUFLEN, index );
        for( int i=0; i< BUFLEN; i++){

            out_L[i] = in_L[i] * sine[i];
            out_R[i] = in_R[i] * sine[i];

        }
    }


}

void IdlePButton( void ){
    pb = GetPushButton_Status( PUSH_BTN_1 );
}

void ClearBuffer( void ){
    for(int i=0; i<BUFLEN; i++){
        ping.out_L[i] = 0;
        ping.out_R[i] = 0;
        pong.out_L[i] = 0;
        pong.out_R[i] = 0;
    }
}
