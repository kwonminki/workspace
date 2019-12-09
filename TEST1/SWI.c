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

    index = GenSine( sine, 1046.f, 48000.f, BUFLEN, index );  //6��Ÿ�� ��

    for( int i=0; i< BUFLEN; i++)
        {
            float f_val = 500.f*sine[i];  // ������ ����
            in_L[i] = in_L[i] + (Int16)f_val;
            in_R[i] = in_R[i] + (Int16)f_val;
        }

    if( pb == PUSH_UP && pb2 == PUSH_UP ){
        for( int i=0; i< BUFLEN; i++){
            out_L[i] = in_L[i];
            out_R[i] = in_R[i];
        }
    }
    else if( pb == PUSH_DOWN )
    {
//==================��ư ������ ��==============
  //      FIRFilter( in_L, h, out_L , L_dbuff, N ,BUFLEN);
  //      FIRFilter( in_R, h, out_R , R_dbuff, N ,BUFLEN);
       // FIRFilter( Int16 *x -�Է�, float *h ���� ���, Int16 *r-���, float *dbuff, Int32 nh, Int32 nx ũ�� );
        FIRFilterDSPLib( in_L, h2, r, out_L , L_dbuff2, N2 ,BUFLEN);
        FIRFilterDSPLib( in_R, h2, r, out_R , R_dbuff2, N2 ,BUFLEN);
//================================
    }
    else if( pb2 == PUSH_DOWN )
    {
        for( int i=0; i< BUFLEN; i++)
        {
            float f_val = 500.f*sine[i];  // ������ ����
            out_L[i] = (Int16)f_val;
            out_R[i] = (Int16)f_val;
        }
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
