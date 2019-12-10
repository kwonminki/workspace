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
#include "filter.h"
#include "fdacoefs.h"
#include "BAND_STOP.h"
#include "sine.h"

RT_buf ping, pong;

static float numX = 200.f;

static Uint8 pb = PUSH_UP;
static Uint8 pb2 = PUSH_UP;

#pragma DATA_ALIGN( L_dbuff, 8 );
#pragma DATA_ALIGN( R_dbuff, 8 );
static float L_dbuff[N+BUFLEN-1]; //lib을 사용하려고
static float R_dbuff[N+BUFLEN-1];
static float L_dbuff2[N2+BUFLEN-1]; //lib을 사용하려고
static float R_dbuff2[N2+BUFLEN-1];
static float r[BUFLEN];

void ClearBufferAll( void ){
    ClearFilterBuf( L_dbuff, BUFLEN );
    ClearFilterBuf( R_dbuff, BUFLEN );
    ClearFilterBuf( L_dbuff2, BUFLEN );
    ClearFilterBuf( R_dbuff2, BUFLEN );
}

void ProcessSWI( void ){
//    Uint32 sample_data;
    Int16 *in_L, *in_R, *out_L, *out_R;
    static int index = 0;
    static float sine[BUFLEN];

    QuePtr que_ptr = Queue_get( RT_Que );
    //QueObj *que_ptr = Queue_get( RT_Que );  위 아래 같은 역할

    in_L = que_ptr->rt_buf->in_L;  //포인터는 화살표
    in_R = que_ptr->rt_buf->in_R;
    out_L = que_ptr->rt_buf->out_L;
    out_R = que_ptr->rt_buf->out_R;

    index = GenSine( sine, numX, 48000.f, BUFLEN, index );  //6옥타브 도

    for( int i=0; i< BUFLEN; i++)
        {
            float f_val = 10000.f*sine[i];  // 사인파 볼륨
            out_L[i] = out_R[i] = (Int16)f_val;

        }

    Queue_put( RT_Que, &que_ptr->elem );

}

void IdlePButton( void ){
    pb = GetPushButton_Status( PUSH_BTN_1 );
    pb2 = GetPushButton_Status( PUSH_BTN_2 );
}


//static RT_buf ping, pong;
RT_buf ping, pong;

void InitQue( QueObj *que ){

    static RT_buf ping, pong;
    //RT_buf *ping_ptr = &ping;

    que[0].rt_buf = &ping;
    que[1].rt_buf = &pong;  //실체를 넣는 부분

    Queue_put( RT_Que, &que[0].elem ); //원래 있는 함수
    Queue_put( RT_Que, &que[1].elem );  // 큐에 핑 들어가고 퐁 들어가게 하는 두 줄임

    for(int i=0; i<BUFLEN; i++){

        que[0].rt_buf -> out_L[i] = 0;
        que[0].rt_buf -> out_R[i] = 0;
        que[1].rt_buf -> out_L[i] = 0;
        que[1].rt_buf -> out_R[i] = 0;

        //ping.out_L[i] = 0;
        //ping_ptr->out_L[i] = 0;

        //ping.out_L[i] = 0;
        //ping.out_R[i] = 0;
        //pong.out_L[i] = 0;
        //pong.out_R[i] = 0;
    }
}

void ProcessTimer(void){
    numX += 20.f;
    if (numX > 400.f){
        numX = 200.f;
    }
}
