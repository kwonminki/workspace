/*
 *  ======== main.c ========
 */
#include <xdc/std.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/BIOS.h>
#include <xdc/cfg/global.h>
#include "sine.h"
#include <stdio.h>

#define BUFLEN 2000
#define STEP 200
short data[BUFLEN];

#define FREQ        200.
#define SAMPLE_RATE 8000.
/*
 *  ======== main ========
 */
Int main()
{ 
    int index = 0;

    puts("LAB3A - Hello SYS/BIOS\n");

    for( int i=0; i<BUFLEN; i+=STEP){
        index = GenSine( &data[i], FREQ, SAMPLE_RATE, STEP, index );
    }



    puts("LAB3A - Program Terminated!!\n");

    return(0);
}
