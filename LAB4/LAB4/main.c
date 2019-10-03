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


/*
 *  ======== main ========
 */
void main()
{ 
    puts("LAB4 - LED Blinking Clock Module\n");

    SysConfigForPinMux();
    LED_DIPSW_Init();

    BIOS_start();
}

static int pb = PUSH_UP;

void ProcessClk( void ){

    if( pb == PUSH_DOWN ){
        LED_Toggle(LED_D4);
        LED_Toggle(LED_D5);
        LED_Toggle(LED_D6);
        LED_Toggle(LED_D7);
    }
}

void ProcessIdle(){
    pb = GetPushButton_Status( PUSH_BTN_1 );
}
