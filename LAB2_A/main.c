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

	ConfigTimer_32bit( 50 ); //���ڰ��� �ٲٸ� �ӵ��� �ٲ�.

	InstallISR(INT_NUM_GPIO_B2, GPIO_PUSHBUTTON_ISR); //��ư ���ͷ�Ʈ ��ġ -> 8���� �س��� ������ 8���� �ؾ��Ѵ�. 2��° ���ڴ� �Լ���.
	InstallISR(INT_NUM_T64P1, TIMER_TINT12_ISR);

	EnableInterrupt(INT_NUM_GPIO_B2); //���ͷ�Ʈ �ο��̺�
	EnableInterrupt(INT_NUM_T64P1);
	_enable_interrupts(); //����� �Լ�. �۷ι����ͷ�Ʈ.

	StartTimer();

	while(1);
	
}
