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

typedef struct RT_buf{
    Int16 in_L[BUFLEN];
    Int16 in_R[BUFLEN];
    Int16 out_L[BUFLEN];
    Int16 out_R[BUFLEN];
} RT_buf;

//extern RT_buf ping;
//extern RT_buf pong;

typedef struct QueObj {
    Queue_Elem elem; //여기까지는 미리 만들어져있다.
    RT_buf *rt_buf; //RT_buf rt_buf; realtime_buffer 그냥 이렇게 하면 될 것 같은데 이거 하나가 1600바이트이다. 하나를 꺼내면 1600바이트가 이동한다는 것은 매우 비효율적이다.
                    //따라서 static으로 버퍼를 만들어 둔 뒤, 포인터를 만들어 큐에 넣어준다.
} QueObj, *QuePtr;

#endif /* DEFINE_H_ */
