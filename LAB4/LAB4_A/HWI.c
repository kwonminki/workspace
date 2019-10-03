/*
 * HWI.c
 *
 *  Created on: 2019. 10. 1.
 *      Author: user
 */


#include <xdc/std.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/BIOS.h>
#include <xdc/cfg/global.h>
#include "LED_DIPSW.h"
#include "sine.h"

#define BUFLEN 200
short data[BUFLEN];

static int led_flag = LED_ON;

void ProcessGPIO2(void){
    //유저 스위치 뭘 눌러도 여기로 들어오게 된다. GPIO Bank 2에 스위치가 달려있다.
    uint8_t is_pb_sw1, is_pb_sw2;
    extern int led_flag;
    static int led_mode = LED_ONOFF;

    is_pb_sw1 = GPIO_InterruptState( GP2, GP2P4);
    is_pb_sw2 = GPIO_InterruptState( GP2, GP2P5);

    if(is_pb_sw1){
      led_flag = !led_flag;
    }
    else if(is_pb_sw2){
        led_mode = !led_mode;
        if(led_mode == LED_ONOFF){
            LED_Off(LED_D4);
            LED_Off(LED_D5);
            LED_Off(LED_D6);
            LED_Off(LED_D7);
        }
        else{
            LED_Off(LED_D4);
            LED_Off(LED_D5);
            LED_On(LED_D6);
            LED_On(LED_D7);
        }
    }

}

void ProcessTimer(void){
    static int index = 0;

    if(led_flag == LED_ON){
        LED_Toggle(LED_D4);
        LED_Toggle(LED_D5);
        LED_Toggle(LED_D6);
        LED_Toggle(LED_D7);
    }

    index = GenSine( data, 300.f, 8000.f, BUFLEN, index );
}
