/*
 * ISR.c
 * ���ͷ�Ʈ ���� ��ƾ
 *  Created on: 2019. 9. 17.
 *      Author: user
 */

#include "LED_DIPSW.h"
#include "GPIO.h"

interrupt void GPIO_PUSHBUTTON_ISR(void){
    //���� ����ġ �� ������ ����� ������ �ȴ�. GPIO Bank 2�� ����ġ�� �޷��ִ�.
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
