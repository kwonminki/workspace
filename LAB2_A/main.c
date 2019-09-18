#include <stdio.h>
#include "init.h"
#include "LED_DIPSW.h"
#include "ISR.h"
#include "Interrupt.h"
#include "Timer.h"


/**
 * LAB2 - External Interrupt(PUSH BUTTON, Timer)
 * main.c
 */



void main(void)
{

    puts("\n====================================");
	puts("               LAB2_A");
	puts("====================================");

	SysConfigForPinMux();
	LED_DIPSW_Init();
	ConfigInterrupt();

	ConfigTimer_32bit( 50 ); //숫자값을 바꾸면 속도가 바뀜.

	InstallISR(INT_NUM_GPIO_B2, GPIO_PUSHBUTTON_ISR); //버튼 인터럽트 설치 -> 8번에 해놨기 때문에 8번에 해야한다. 2번째 인자는 함수명.
	InstallISR(INT_NUM_T64P1, TIMER_TINT12_ISR);

	EnableInterrupt(INT_NUM_GPIO_B2); //인터럽트 인에이블
	EnableInterrupt(INT_NUM_T64P1);
	_enable_interrupts(); //내장된 함수. 글로벌인터럽트.

	StartTimer();

	while(1);
	
}
