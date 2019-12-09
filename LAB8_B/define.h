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
    Queue_Elem elem;    //�⺻���� �ִ°�
    RT_buf *rt_buf;      //�̰� �ϳ��ϳ��� 200��(BUFLEN)��ŭ�� ū �迭�̱� ������ �ʹ� ŭ ���� �迭 ��ü�� ť�� �״�� static���� �ھƳ��� ť �ȿ��� �����̴� ���� �����͸� �����̸� ��
    // �����ͷ� ���� �� ���� �ּҸ� �����̰� ��
} QueObj, *QuePtr;

#endif /* DEFINE_H_ */
