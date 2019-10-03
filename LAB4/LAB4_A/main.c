/*
 *  ======== main.c ========
 */

#include <xdc/std.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/BIOS.h>
#include <xdc/cfg/global.h>
#include <stdio.h>
#include "init.h"
#include "LED_DIPSW.h"
#include "Timer.h"


/*
 *  ======== main ========
 */
void main()
{ 
    puts("LAB4_A - SYS/BIOS HWI Module\n");

    SysConfigForPinMux();
    LED_DIPSW_Init();

    ConfigTimer_32bit( 200 ); //타이머 설정.
    StartTimer();

    BIOS_start();
}

