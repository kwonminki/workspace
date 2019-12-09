/*
 * define.h
 *
 *  Created on: 2019. 10. 8.
 *      Author: user
 */

#ifndef DEFINE_H_
#define DEFINE_H_

#include "LED_DIPSW.h"
#include "I2C.h"
#include "Codec.h"
#include "McASP.h"
#include "sine.h"
#include "EDMA_McASP.h"

#define SAMPLING_FREQ SAMPLING_FREQ_48000

#define BUFLEN 200
#define PING 0
#define PONG (~PING)

#define ELEMENT_SIZE    2

typedef struct RT_buf
{
    Int16 in_L[BUFLEN];
    Int16 in_R[BUFLEN];
    Int16 out_L[BUFLEN];
    Int16 out_R[BUFLEN];
} RT_buf;


typedef struct QueObj
{
    Queue_Elem elem;    //기본으로 있는것
    RT_buf *rt_buf;      //이것 하나하나가 200개(BUFLEN)만큼의 큰 배열이기 때문에 너무 큼 따라서 배열 자체는 큐에 그대로 static으로 박아놓고 큐 안에서 움직이는 것은 포인터만 움직이면 됨
    // 포인터로 만들어서 걍 작은 주소만 움직이게 함
} QueObj, *QuePtr;

#endif /* DEFINE_H_ */
