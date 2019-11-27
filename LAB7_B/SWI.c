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

Int16 in_ping_buffer[2][BUFLEN];
Int16 in_pong_buffer[2][BUFLEN];
Int16 out_ping_buffer[2][BUFLEN];
Int16 out_pong_buffer[2][BUFLEN];

static Uint8 pb = PUSH_UP;
static float sine[BUFLEN];

void ProcessSWI( void ){
//    Uint32 sample_data;
    Int16 (*in)[BUFLEN], (*out)[BUFLEN];
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
            out[0][i] = in[0][i];
            out[1][i] = in[1][i];
        }
    }
    else{
        index = GenSine( sine, 1.f, SAMPLING_FREQ, BUFLEN, index );
        for( int i=0; i< BUFLEN; i++){

            out[0][i] = in[0][i] * sine[i];
            out[1][i] = in[1][i] * sine[i];

        }
    }


}

void IdlePButton( void ){
    pb = GetPushButton_Status( PUSH_BTN_1 );
}

void ClearBuffer( void ){
    for(int i=0; i<BUFLEN; i++){
        out_ping_buffer[0][i] = 0;
        out_pong_buffer[0][i] = 0;
        out_ping_buffer[1][i] = 0;
        out_pong_buffer[1][i] = 0;
    }
}
