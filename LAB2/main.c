#include <stdio.h>
#include "init.h"
#include "LED_DIPSW.h"
#include "ISR.h"
#include "Interrupt.h"


void MicroSecDelay(unsigned delay){
    volatile unsigned i;

    for( i=0; i<delay*15; i++){
        asm(" nop");
    }
}

/**
 * LAB2 - External Interrupt(PUSH BUTTON)
 * main.c
 */

int led_flag = LED_ON;

int main(void)
{

    puts("\n====================================");
	puts("               LAB2");
	puts("====================================");

	SysConfigForPinMux();
	LED_DIPSW_Init();
	ConfigInterrupt();

	InstallISR(INT_NUM_GPIO_B2, GPIO_PUSHBUTTON_ISR); //��ư ���ͷ�Ʈ ��ġ -> 8���� �س��� ������ 8���� �ؾ��Ѵ�. 2��° ���ڴ� �Լ���.

	EnableInterrupt(INT_NUM_GPIO_B2); //���ͷ�Ʈ �ο��̺�
	_enable_interrupts(); //����� �Լ�. �۷ι����ͷ�Ʈ.

	while(1){

	    if( led_flag == LED_ON ){
            LED_Toggle(LED_D4);
            LED_Toggle(LED_D5);
            LED_Toggle(LED_D6);
            LED_Toggle(LED_D7);
	    }

        MicroSecDelay(250000);

	}
	
	return 0;
}
