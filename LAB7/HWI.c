/*
 * ISR.c
 *
 *  Created on: 2019. 10. 8.
 *      Author: user
 */

#include <xdc/std.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/BIOS.h>
#include <xdc/cfg/global.h>
#include <ti/sysbios/knl/Swi.h>
#include "define.h"



static Int32 led_cnt = 0;

void EDMA3_CC_ISR( void ){//���⿡ ������ ������ EDMA�� ���� ���� �ϳ��� �� ä���� �����̴�. �׷��� ���� �� �ؾ� �ұ�? ��ɼ��� �ٽ� ��� �Ѵ�.
    //���� ���� ����� �� ���� IPR �� ���ͷ�Ʈ �ҵ� �������͸� �����ִ� ���̴�. �̰� �������� ������ ���ͷ�Ʈ�� ��� �ɸ���..
    static Int32 which_buffer = PING;

    CSL_FINST( edma3ccRegs->ICR, EDMA3CC_ICR_I0, CLEAR ); //IPR�� ���� ����� ���� �ƴ� ICR�� ���� �����.
    while( CSL_FEXT( edma3ccRegs->IPR, EDMA3CC_IPR_I1 ) != CSL_EDMA3CC_IPR_I1_YES );
                  //Ư�� ��Ʈ�� �̾Ƴ��� ��. IPR�� �����ؼ� �ƿ� ���۵� �ٲ������ ����.
    CSL_FINST( edma3ccRegs->ICR, EDMA3CC_ICR_I1, CLEAR );

    if( which_buffer == PING ){
        edma3ccRegs->PARAMSET[REVT].DST = (Uint32)in_pong_buffer;
        edma3ccRegs->PARAMSET[XEVT].SRC = (Uint32)out_pong_buffer;
    }
    else{
        edma3ccRegs->PARAMSET[REVT].DST = (Uint32)in_ping_buffer;
        edma3ccRegs->PARAMSET[XEVT].SRC = (Uint32)out_ping_buffer;
    }

    edma3ccRegs->PARAMSET[REVT].A_B_CNT =       CSL_FMK(EDMA3CC_A_B_CNT_BCNT, BUFLEN)
                                            | CSL_FMK(EDMA3CC_A_B_CNT_ACNT, ELEMENT_SIZE);

    edma3ccRegs->PARAMSET[XEVT].A_B_CNT =       CSL_FMK(EDMA3CC_A_B_CNT_BCNT, BUFLEN)
                                            | CSL_FMK(EDMA3CC_A_B_CNT_ACNT, ELEMENT_SIZE);
    //�� �����غ��� Bī��Ʈ�� ��� �ٲ�� ������ ���� �ʱ�ȭ ����� �Ѵ�.

    Swi_or( swi0, which_buffer );
    which_buffer = ~which_buffer;

    led_cnt++;
}


void IdleLED( void ){
    if( led_cnt == (SAMPLING_FREQ>>1) ){
        LED_Toggle(LED_D4);
        led_cnt = 0;
    }
}
