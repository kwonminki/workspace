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

RT_buf ping, pong;

static Uint8 pb = PUSH_UP;

static float L_dbuff[N];
static float R_dbuff[N];

void ClearBufferAll( void ){
    ClearFilterBuf( L_dbuff, BUFLEN );
    ClearFilterBuf( R_dbuff, BUFLEN );
}

void ProcessSWI( void ){
//    Uint32 sample_data;
    Int16 *in_L, *in_R, *out_L, *out_R;
    static int index = 0;

    QuePtr que_ptr = Queue_get( RT_Que );
    //QueObj *que_ptr = Queue_get( RT_Que );  �� �Ʒ� ���� ����

    in_L = que_ptr->rt_buf->in_L;  //�����ʹ� ȭ��ǥ
    in_R = que_ptr->rt_buf->in_R;
    out_L = que_ptr->rt_buf->out_L;
    out_R = que_ptr->rt_buf->out_R;

    if( pb == PUSH_UP){
        for( int i=0; i< BUFLEN; i++){
            out_L[i] = in_L[i];
            out_R[i] = in_R[i];
        }
    }
    else{
//================================
        FIRFilter( in_L, h, out_L , L_dbuff, N ,BUFLEN);
        FIRFilter( in_R, h, out_R , R_dbuff, N ,BUFLEN);
       // FIRFilter( Int16 *x -�Է�, float *h ���� ���, Int16 *r-���, float *dbuff, Int32 nh, Int32 nx ũ�� );

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
