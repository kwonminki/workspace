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
#include "sine.h"

RT_buf ping, pong;

static Uint8 pb = PUSH_UP;

#pragma DATA_ALIGN( L_dbuff, 8 );
#pragma DATA_ALIGN( R_dbuff, 8 );
static float L_dbuff[N+BUFLEN-1]; //lib을 사용하려고
static float R_dbuff[N+BUFLEN-1];
static float r[BUFLEN];

void ClearBufferAll( void ){
    ClearFilterBuf( L_dbuff, BUFLEN );
    ClearFilterBuf( R_dbuff, BUFLEN );
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

    index = GenSine( sine, 3500.f, 48000.f, BUFLEN, index ); //이러면 sine이 섞이게 할 수 있다. 이 sine값은 원음에 더해져있을 텐데 필터를 적용해서 이 sine을 제거해보자.

    for( int i=0; i< BUFLEN; i++){
            float f_val = 10000.f*sine[i];
            in_L[i] = in_L[i] + (Int16)f_val;
            in_R[i] = in_R[i] + (Int16)f_val;
    }

    if( pb == PUSH_UP){
        for( int i=0; i< BUFLEN; i++){
            out_L[i] = in_L[i] ;
            out_R[i] = in_R[i];
        }
    }
    else{
//==================버튼 눌렸을 때==============
  //      FIRFilter( in_L, h, out_L , L_dbuff, N ,BUFLEN);
  //      FIRFilter( in_R, h, out_R , R_dbuff, N ,BUFLEN);
       // FIRFilter( Int16 *x -입력, float *h 필터 계수, Int16 *r-출력, float *dbuff, Int32 nh, Int32 nx 크기 );
        FIRFilterDSPLib( in_L, h, r, out_L , L_dbuff, N ,BUFLEN);
        FIRFilterDSPLib( in_R, h, r, out_R , R_dbuff, N ,BUFLEN);
//================================
    }

    Queue_put( RT_Que, &que_ptr->elem );

}

void IdlePButton( void ){
    pb = GetPushButton_Status( PUSH_BTN_1 );
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
