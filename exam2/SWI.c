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
static float L_dbuff[N+BUFLEN-1]; //lib�� ����Ϸ���
static float R_dbuff[N+BUFLEN-1];
static float L_dbuff2[N2+BUFLEN-1]; //lib�� ����Ϸ���
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
    //QueObj *que_ptr = Queue_get( RT_Que );  �� �Ʒ� ���� ����

    in_L = que_ptr->rt_buf->in_L;  //�����ʹ� ȭ��ǥ
    in_R = que_ptr->rt_buf->in_R;
    out_L = que_ptr->rt_buf->out_L;
    out_R = que_ptr->rt_buf->out_R;

    index = GenSine( sine, numX, 48000.f, BUFLEN, index );  //6��Ÿ�� ��

    for( int i=0; i< BUFLEN; i++)
        {
            float f_val = 10000.f*sine[i];  // ������ ����
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
    que[1].rt_buf = &pong;  //��ü�� �ִ� �κ�

    Queue_put( RT_Que, &que[0].elem ); //���� �ִ� �Լ�
    Queue_put( RT_Que, &que[1].elem );  // ť�� �� ���� �� ���� �ϴ� �� ����

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
