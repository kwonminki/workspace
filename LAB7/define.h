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

#define ELEMENT_SIZE    4

extern Uint32 in_ping_buffer[BUFLEN];
extern Uint32 in_pong_buffer[BUFLEN];
extern Uint32 out_ping_buffer[BUFLEN];
extern Uint32 out_pong_buffer[BUFLEN];

#endif /* DEFINE_H_ */
