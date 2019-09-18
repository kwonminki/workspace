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

	InstallISR(INT_NUM_GPIO_B2, GPIO_PUSHBUTTON_ISR); //버튼 인터럽트 설치 -> 8번에 해놨기 때문에 8번에 해야한다. 2번째 인자는 함수명.

	EnableInterrupt(INT_NUM_GPIO_B2); //인터럽트 인에이블
	_enable_interrupts(); //내장된 함수. 글로벌인터럽트.

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
