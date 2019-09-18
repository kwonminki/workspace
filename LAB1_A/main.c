#include <stdio.h>
#include "init.h"
#include "LED_DIPSW.h"


void MicroSecDelay(unsigned delay){
    volatile unsigned i;

    for( i=0; i<delay*15; i++){
        asm(" nop");
    }
}

/**
 * LAB1_A - LED Blinking Using Delay Func(PUSH BUTTON)
 * main.c
 */
int main(void)
{
    int pb1;
    int pb2;

    puts("\n====================================");
	puts("               LAB1_A");
	puts("====================================");

	SysConfigForPinMux();
	LED_DIPSW_Init();

	while(1){
	    pb1 = GetPushButton_Status( PUSH_BTN_1 );
	    pb2 = GetPushButton_Status( PUSH_BTN_2 );
	    if(pb1 == PUSH_DOWN){
            LED_Toggle(LED_D4);
            LED_Toggle(LED_D5);
	    }
	    else{
	        LED_Off(LED_D4);
	        LED_Off(LED_D5);
	    }

        if(pb2 == PUSH_DOWN){
            LED_Toggle(LED_D6);
            LED_Toggle(LED_D7);
        }
        else{
            LED_Off(LED_D6);
            LED_Off(LED_D7);
        }
        MicroSecDelay(250000);

	}
	
	return 0;
}
