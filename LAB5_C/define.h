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

#define SAMPLING_FREQ SAMPLING_FREQ_48000

#define BUFLEN 200
#define PING 0
#define PONG (~PING)

#endif /* DEFINE_H_ */
