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
#include "HPF.h"


RT_buf ping, pong;

static Uint8 pb = PUSH_UP;
static Uint8 pb_flag = PUSH_UP;
static Uint8 pb2 = PUSH_UP;
static Uint8 pb2_flag = PUSH_UP;
static float  L_dbuff[N];
static float  R_dbuff[N];
static float  L_dbuff2[N2];
static float  R_dbuff2[N2];

int mode = 0;

void ClearBufferAll( void )
{
    ClearFilterBuf( L_dbuff, BUFLEN );
    ClearFilterBuf( R_dbuff, BUFLEN );
    ClearFilterBuf( L_dbuff2, BUFLEN );
    ClearFilterBuf( R_dbuff2, BUFLEN );
}


void ProcessSWI( void ){


    if( pb_flag==1 && pb==0 )  // 버튼 1번 라이징엣지
    {
        if( mode<3 ) mode++;
        else mode = 0;
    }

//    Uint32 sample_data;
    Int16 *in_L, *in_R, *out_L, *out_R;
    static int index = 0;

    QuePtr que_ptr = Queue_get( RT_Que );
    //QueObj *que_ptr = Queue_get( RT_Que );  위 아래 같은 역할

    in_L = que_ptr->rt_buf->in_L;  //포인터는 화살표
    in_R = que_ptr->rt_buf->in_R;
    out_L = que_ptr->rt_buf->out_L;
    out_R = que_ptr->rt_buf->out_R;

    if( mode == 0 )     //original
    {
        for( int i=0; i< BUFLEN; i++)
        {
            out_L[i] = in_L[i];
            out_R[i] = in_R[i];
        }
        LED_On( LED_D4 );
        LED_Off( LED_D5 );
        LED_Off( LED_D6 );
        LED_Off( LED_D7 );
    }
    else if( mode == 1 )        //LPF
    {
        FIRFilter( in_L, h, out_L, L_dbuff, N, BUFLEN  );
        FIRFilter( in_R, h, out_R, R_dbuff, N, BUFLEN  );
        LED_On( LED_D5 );
        LED_Off( LED_D6 );
        LED_Off( LED_D7 );
        LED_Off( LED_D4 );
    }
    else if( mode == 2 )        //HPF
    {
        FIRFilter( in_L, h2, out_L, L_dbuff2, N2, BUFLEN  );
        FIRFilter( in_R, h2, out_R, R_dbuff2, N2, BUFLEN  );
        LED_On( LED_D6 );
        LED_Off( LED_D7 );
        LED_Off( LED_D4 );
        LED_Off( LED_D5 );
    }
    else if( mode == 3 )        //mute
    {
        for( int i=0; i< BUFLEN; i++)
        {
            out_L[i] = 0;
            out_R[i] = 0;
        }
        LED_On( LED_D7 );
        LED_Off( LED_D4 );
        LED_Off( LED_D5 );
        LED_Off( LED_D6 );
    }

    Queue_put( RT_Que, &que_ptr->elem );

    pb_flag = pb;
    pb2_flag = pb2;
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
