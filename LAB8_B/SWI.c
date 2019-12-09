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
/*
#define NBIQ    5
#define GAIN1   0.7240377257702
#define GAIN2   0.687426802071
#define GAIN3   0.4405413301386
#define GAIN4   0.2177592867447
#define GAIN5   0.004047171962595
//게인으로 나온

F_COEF f_coef[NBIQ] = { { {-1.836889260649, 0.9755511815075},{ GAIN1, -1.79703832113*GAIN1, GAIN1 } },
                        { {-1.835752932109, 0.9445132047631},{ GAIN2, -1.741803638262*GAIN2, GAIN2 } },
                        { {-1.836622688537, 0.8965253094934},{ GAIN3, -1.533192787113*GAIN3, GAIN3 } },
                        { {-1.837968785407, 0.8519826919304},{ GAIN4, -0.0579952322755*GAIN4, GAIN4 } },
                        { {-1.841731135282, 0.9932916177034},{ GAIN5, -1.813721021878*GAIN5, GAIN5 } },
                       };

*/

#define NBIQ    1
F_COEF f_coef[NBIQ] = {{ {-1.886040053703, 0.9229897627825},{  0.9614948813912,   -1.886040053703,   0.9614948813912 } }};

RT_buf ping, pong;

static Uint8 pb = PUSH_UP;

#pragma DATA_ALIGN( L_dbuff, 8 );
#pragma DATA_ALIGN( R_dbuff, 8 );
static float L_dbuff[NBIQ][2]; //lib을 사용하려고
static float R_dbuff[NBIQ][2];


void ClearBufferAll( void ){
    ClearIIRFilterBuf( L_dbuff, NBIQ );
    ClearIIRFilterBuf( R_dbuff, NBIQ );
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

    index = GenSine( sine, 1500.f, 48000.f, BUFLEN, index ); //이러면 sine이 섞이게 할 수 있다. 이 sine값은 원음에 더해져있을 텐데 필터를 적용해서 이 sine을 제거해보자.

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

        IIRFilter( in_L, f_coef, out_L , L_dbuff, NBIQ ,BUFLEN );
        IIRFilter( in_R, f_coef, out_R , R_dbuff, NBIQ ,BUFLEN );
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
