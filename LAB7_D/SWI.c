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

    QuePtr que_ptr = Queue_get( RT_Que );
    //QueObj *que_ptr = Queue_get( RT_Que );


    in_L = que_ptr->rt_buf->in_L;
    in_R = que_ptr->rt_buf->in_R;
    out_L = que_ptr->rt_buf->out_L;
    out_R = que_ptr->rt_buf->out_R; //길어서 그냥 변수 선언했다.

    if( pb == PUSH_UP){
        for( int i=0; i< BUFLEN; i++){
            out_L[i] = in_L[i];
            out_R[i] = in_R[i];
        }
    }
    else{
        index = GenSine( sine, 2.f, SAMPLING_FREQ, BUFLEN, index );
        for( int i=0; i< BUFLEN; i++){

            out_L[i] = in_L[i] * sine[i];
            out_R[i] = in_R[i] * sine[i];

        }
    }

    Queue_put( RT_Que, &que_ptr->elem ); //썼으니 큐를 다시 넣어주자.


}

void IdlePButton( void ){
    pb = GetPushButton_Status( PUSH_BTN_1 );
}

//RT_buf ping, pong;
void InitQue( QuePtr que ){

    static RT_buf ping, pong;

    que[0].rt_buf = &ping;
    que[1].rt_buf = &pong;

    Queue_put( RT_Que, &que[0].elem );
    Queue_put( RT_Que, &que[1].elem );

    for(int i=0; i<BUFLEN; i++){
        que[0].rt_buf->out_L[i] = 0; //포인터 주소를 참조할때는 화살표를 쓴다.
        que[0].rt_buf->out_R[i] = 0;
        pong.out_L[i] = 0;
        pong.out_R[i] = 0;
    }
}
