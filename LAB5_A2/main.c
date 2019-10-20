/*
 *  ======== main.c ========
 */

#include <xdc/std.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/BIOS.h>
#include <xdc/cfg/global.h>
#include <stdio.h>
#include "init.h"
#include "define.h"

/*
 *  ======== main ========
 */
void main()
{

    puts("LAB5_A1 - Delayed Codec Talk-Thr\n");
    SysConfigForPinMux();
    LED_DIPSW_Init();
    I2C_Init( 400 );


    CodecInit( SAMPLING_FREQ, WORD_LEN_16BIT, LINE_IN );
    ConfigMcASP( MCASP_32BIT, MCASP_1SLOT, CFG, RINT, NO_XINT );

    EnableInterrupt( INT_5 ); //app.cfg에서 스타트 설정을 안해놓음.


    InitMcASP( RECEIVE, CFG );
    InitMcASP( TRANSMIT, CFG );

    BIOS_start();
}
