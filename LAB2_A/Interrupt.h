/***********************************************************
* 	
*	Interrupt Configuration Module Header
*                              
*	File Name : Interrupt.h 
*	Date Created :
*	Last modified :
*
************************************************************/

#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

#include "L138_common.h"

#define SYSCFG_CHIPINT2	5
#define T64P0_TINT12	4
#define EDMA3_CC0_INT1	8
#define IIC0_INT		36
#define SP0_INT			37
#define UART0_INT		38
#define T64P1_TINT12    40
#define GPIO_B1INT		41
#define IIC1_INT		42
#define SP1_INT			43
#define UART1_INT		46
#define GPIO_B2INT		49
#define GPIO_B3INT		52
#define GPIO_B4INT		54
#define GPIO_B5INT		59
#define MCASP_INT		61
#define GPIO_B6INT		62
#define RTC_IRQS		63
#define GPIO_B0INT		65
#define SYSCFG_CHIPINT3	67
#define UART2_INT		69
#define GPIO_B7INT		72
#define USER_RESERVE1	75
#define USER_RESERVE2	76
#define USER_RESERVE3	77

#define INT_NUM_T64P1	4
#define INT_NUM_MCASP	5
#define INT_NUM_EDMA3	6
#define INT_NUM_UART2	7
#define INT_NUM_GPIO_B2	8
#define INT_NUM_RTC		9

void ConfigInterrupt( void );
void InstallISR(Uint32 int_num, void (*c_int)(void));


extern __cregister volatile unsigned int AMR;
extern __cregister volatile unsigned int CSR;
extern __cregister volatile unsigned int IFR;
extern __cregister volatile unsigned int ISR;
extern __cregister volatile unsigned int ICR;
extern __cregister volatile unsigned int IER;
extern __cregister volatile unsigned int ISTP;
extern __cregister volatile unsigned int IRP;
extern __cregister volatile unsigned int NRP;

#endif
