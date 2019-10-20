/*
 *  ======== main.c ========
 */

#include <xdc/std.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/BIOS.h>
#include <xdc/cfg/global.h>
#include <ti/sysbios/knl/Clock.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "init.h"
#include "LED_DIPSW.h"
#include "I2C.h"
#include "codec.h"
#include "McASP.h"
#include "Define.h"

static Int16 freq[NUM_KEY+1];
static Note note[MAX_NOTE];

static Uint16 GetNoteFromFile( char *input )
{
    FILE *infile;
    Uint16 num=0;
    float fval;

    if( (infile = fopen( input, "rt" )) == NULL )
    {
        puts(" File Open Error!!!");
        exit(-1);
    }

    while( fscanf( infile, "%d %f", &note[num].key, &fval ) != EOF )
    {
        note[num].duration = (Uint32)(DUR*fval);
        num++;
    }

    fclose( infile );

    return num;
}



static void CalcFreq( void )
{
    Int16 i;

    for( i=1; i <= NUM_KEY; i++ )
        freq[i] = (Int16)( 440.* pow(2., (i-49.)/12.) + 0.5 );
}


static Uint16 num_note;

void main(void)
{
    puts("\n======================================");
    puts("     Lab5E - Synthesize Music(TASK)");
    puts("======================================");

    SysConfigForPinMux( );
    LED_DIPSW_Init( );
    I2C_Init( 400 );

    CalcFreq( );
    num_note = GetNoteFromFile( "Input2.note" );

    CodecInit( SAMPLING_FREQ_48000, WORD_LEN_16BIT, LINE_IN );
    ConfigMcASP( MCASP_32BIT, MCASP_1SLOT, CFG, RINT, NO_XINT );

    EnableInterrupt( INT_5 );

    InitMcASP( RECEIVE, CFG );
    InitMcASP( TRANSMIT, CFG );

    BIOS_start( );
}


static void Wait( Uint32 time )
{
    Uint32 start;

    start = Clock_getTicks( );
    while( Clock_getTicks( ) < start+ time );
}


volatile float omega;
volatile Int32 time_index;
volatile Int16 done, temp_done;


#define TWO_PI (2.*3.141592654 / (float)48000)

void PlayNote( void )
{
    Int32 i;

    for( i=0; i < num_note; i++ )
    {
        System_printf("Enter task : %ld\n", Clock_getTicks( ));
        temp_done = done = 0;
        omega = TWO_PI * freq[note[i].key];

        time_index=1;

        Wait( note[i].duration );

        temp_done = 1;
        while( done != 1 );
    }

    BIOS_exit( 0 );
}

