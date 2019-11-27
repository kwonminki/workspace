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

Uint32 in_ping_buffer[BUFLEN];
Uint32 in_pong_buffer[BUFLEN];
Uint32 out_ping_buffer[BUFLEN];
Uint32 out_pong_buffer[BUFLEN];

static Uint8 pb = PUSH_UP;
static float sine[BUFLEN];

void ProcessSWI( void ){
//    Uint32 sample_data;
    Int16 left, right;
    Uint32 *in, *out;
    static int index = 0;

    Int32 which_buffer = Swi_getTrigger();

    if( which_buffer == PONG ){
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

void IdlePButton( void ){
    pb = GetPushButton_Status( PUSH_BTN_1 );
}

void ClearBuffer( void ){
    for(int i=0; i<BUFLEN; i++){
        out_ping_buffer[i] = 0;
        out_pong_buffer[i] = 0;
    }
}
