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

#define SAMPLING_FREQ SAMPLING_FREQ_48000

#define NUM_KEY 88
#define MAX_NOTE 2000
#define DUR 500.f

typedef struct{
    Int16 key;
    Uint32 duration;
} Note;

#endif /* DEFINE_H_ */
