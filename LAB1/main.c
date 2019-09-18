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
 * LAB1 - LED Blinking Using Delay Func
 * hello.c
 */
int main(void)
{
    int dip1;
    int dip2;

    puts("\n====================================");
	puts("               LAB1");
	puts("====================================");

	SysConfigForPinMux();
	LED_DIPSW_Init();

	while(1){
	    dip1 = GetDIP_Status( DIP_1 );
	    dip2 = GetDIP_Status( DIP_2 );
	    if(dip1 == DIP_ON){
            LED_Toggle(LED_D4);
            LED_Toggle(LED_D5);
	    }
	    else{
	        LED_Off(LED_D4);
	        LED_Off(LED_D5);
	    }

        if(dip2 == DIP_ON){
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
