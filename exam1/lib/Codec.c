/***********************************************************
* 	
*	Codec Initialization & Control Module  
*                              
*	File Name : Codec.c 
*	Date Created :
*	Last modified :
*
************************************************************/

#include "Codec.h"
#include "I2C.h"

static void Codec_RSET( Uint16 reg_num, Uint16 reg_val )
{
    Uint16 data;

    data = (reg_val << 8) | reg_num;       							// register addr &  data

    I2C_Write (AIC3106_I2C_ADDR, (Uint8 *)&data, 2);
}


void ResetCodec( void )
{
    volatile unsigned int delay = 0xFFF;

    Codec_RSET( PAGE_SELECT, 0 ); 									// select page 0
    Codec_RSET( SOFT_RESET, 0x80 );   								// Reset the AIC3106
    while(delay--);
}


void CodecInputGain( Uint8 vol )
{
	Codec_RSET(  LEFT_ADC_PGA_GAIN, vol );    						// mute off, (vol/2) dB
    Codec_RSET(  RIGHT_ADC_PGA_GAIN, vol );    						// Mute off, (vol/2) dB	
}


void CodecOutputAttenuation( Uint8 vol )
{
	Codec_RSET( LEFT_DAC_VOLUME, vol & 0x7F );    					// mute off, -(vol/2) dB
    Codec_RSET( RIGHT_DAC_VOLUME, vol & 0x7F  );    				// mute off, -(vol/2) dB
}


void CodecSetHPFilter( Uint8 mode )
{
	Codec_RSET( AUDIO_CODEC_DIGITAL_FILTER, mode );					// high pass filter
}


void CodecInputSelect( Uint8 input_sel )
{
	if( input_sel == MIC ) {
        Codec_RSET(  LEFT_ADC_PGA_GAIN, 0x30 );                     // mute off, 24dB (default vol for mic)
        Codec_RSET(  RIGHT_ADC_PGA_GAIN, 0x30 );                    // mute off, 24dB (default vol for mic)

        Codec_RSET( LINE1L_LEFT_ADC, 0x7C );                        // not connected, power up
        Codec_RSET( LINE1R_RIGHT_ADC, 0x7C );                       // not connected, power up

        Codec_RSET( MIC3LR_LEFT_ADC, 0x0F );                        // MIC3L-->left: 0dB,  MIC3L-->right: not connected
        Codec_RSET( MIC3LR_RIGHT_ADC, 0xF0 );                       // MIC3R-->right: 0dB, MIC3L-->left: not connected

        Codec_RSET( MICBIAS, 0x80 );                                // mic bias on : 2.5V
    }
	else {
        Codec_RSET(  LEFT_ADC_PGA_GAIN, 0 );                       // mute off, 0dB (default vol for line-in)
        Codec_RSET(  RIGHT_ADC_PGA_GAIN, 0 );                      // mute off, 0dB (default vol for line-in)

        Codec_RSET( LINE1L_LEFT_ADC, 0x04 );                        // single-ended, 0dB, power up
        Codec_RSET( LINE1R_RIGHT_ADC, 0x04 );                       // single-ended, 0dB, power up

        Codec_RSET( MIC3LR_LEFT_ADC, 0xFF );                        // not connected
        Codec_RSET( MIC3LR_RIGHT_ADC, 0xFF );                       // not connected

        Codec_RSET( MICBIAS, 0x00 );                                // mic bias off
    }
}


void CodecSampleRate44100( unsigned int sampling_freq ) {
    Codec_RSET( PLL_PROGRAMMING_B, 7<<2 );                      // PLL on, J=7
    Codec_RSET( PLL_PROGRAMMING_C, (3500>>6) &0xFF );           // PLL on, D=3500
    Codec_RSET( PLL_PROGRAMMING_D, (3500 & 0x3F) << 2 );        // PLL on, D=3500

    Codec_RSET( CODEC_DATAPATH_SETUP, 0x8A );                   // Fs=44.1, left DAC-->LEFT, right DAC-->RIGHT

    if( sampling_freq == 22050 )
        Codec_RSET( CODEC_SAMPLE_RATE_SEL, 0x22 );               // ADC fs=fs(ref)/X, DAC fs=fs(ref)/X;
    else if ( sampling_freq == 11025 )
        Codec_RSET( CODEC_SAMPLE_RATE_SEL, 0x66 );               // ADC fs=fs(ref)/X, DAC fs=fs(ref)/X;
    else
        Codec_RSET( CODEC_SAMPLE_RATE_SEL, 0x0 );                // ADC fs=fs(ref)/X, DAC fs=fs(ref)/X;
}


void CodecSampleRate48000( unsigned int sampling_freq ) {
    Codec_RSET( PLL_PROGRAMMING_B, 8<<2 );                      // PLL on, J=8
    Codec_RSET( PLL_PROGRAMMING_C, 0x0 );                       // PLL on, D=0
    Codec_RSET( PLL_PROGRAMMING_D, 0x0 );                       // PLL on, D=0

    Codec_RSET( CODEC_DATAPATH_SETUP, 0x0A );                   // Fs=48, left DAC-->LEFT, right DAC-->RIGHT

    if( sampling_freq == 32000 )
        Codec_RSET( CODEC_SAMPLE_RATE_SEL, 0x11 );              // ADC fs=fs(ref)/X, DAC fs=fs(ref)/X;
    else if ( sampling_freq == 16000 )
        Codec_RSET( CODEC_SAMPLE_RATE_SEL, 0x44 );              // ADC fs=fs(ref)/X, DAC fs=fs(ref)/X;
    else if ( sampling_freq == 8000 )
        Codec_RSET( CODEC_SAMPLE_RATE_SEL, 0xAA );              // ADC fs=fs(ref)/X, DAC fs=fs(ref)/X;
    else
        Codec_RSET( CODEC_SAMPLE_RATE_SEL, 0x0 );               // ADC fs=fs(ref)/X, DAC fs=fs(ref)/X;
}

void CodecInit( unsigned int sampling_freq, Uint8 word_len, Uint8 input_sel ) // codec system clk : 24.576MHz
{
//  Init_I2C( 100 );                                            // SCLK = 100KHz

    ResetCodec( );

    Codec_RSET( PLL_PROGRAMMING_A, 0x82 );                      // PLL on, P=2
    Codec_RSET( AUDIO_CODEC_OVERFLOW, 0x01 );                   // R=1

    if( sampling_freq == 44100 || sampling_freq == 22050 || sampling_freq == 11025 )
        CodecSampleRate44100( sampling_freq );
    else
        CodecSampleRate48000( sampling_freq );

    Codec_RSET( CLOCK_GENERATION, 0x00 );                       // PLLCLK_IN=MCLK,  CLKDIV_IN=MCLK
    Codec_RSET( ADDITIONAL_GPIO_B, 0x00 );                      // CODEC_CLKIN=PLLDIV_OUT

    Codec_RSET( AUDIO_SERIAL_DATA_INTFACE_A, 0xC0 );            // BCLK=master, WCLK=master
    Codec_RSET( AUDIO_SERIAL_DATA_INTFACE_B, word_len );        // DSP mode, word len=word_len, bit clk rate=256 clk mode
    Codec_RSET( AUDIO_SERIAL_DATA_INTFACE_C, 0x00);             // data offset=0

    Codec_RSET( LINE2L_LEFT_ADC, 0x78);                         // not connected
    Codec_RSET( LINE2R_RIGHT_ADC, 0x78);                        // not connected

    Codec_RSET( LINE1R_LEFT_ADC, 0x78);                         // not connected
    Codec_RSET( LINE1L_RIGHT_ADC, 0x78);                        // not connected

    CodecInputSelect( input_sel );

    Codec_RSET( LEFT_AGC_A, 0 );                                // AGC off
    Codec_RSET( RIGHT_AGC_A, 0 );                               // AGC off

    Codec_RSET( LEFT_AGC_B, 0 );                                // AGC max gain=0
    Codec_RSET( RIGHT_AGC_B, 0 );                               // AGC max gain=0

    Codec_RSET( DAC_POWER_OUTPUT_DRIVER, 0xE0 );                // left, right DAC on, HPLCOM:single-ended
    Codec_RSET( HIGHPOWER_OUTPUT_DRIVER, 0x10 );                // HPRCOM:single-end, short-circuit off

    Codec_RSET( DAC_OUTPUT_SWITCHING, 0 );                      // left DAC-->DAC_L1, right DAC-->DAC_R1
    Codec_RSET( LEFT_DAC_VOLUME, 0 );                           // mute off, 0dB
    Codec_RSET( RIGHT_DAC_VOLUME, 0 );                          // mute off, 0dB

    Codec_RSET( DAC_L1_HPLOUT_VOLUME, 0x80 );                   // DAC_L1-->HPLOUT, 0dB
    Codec_RSET( HPLOUT_OUTPUT_LEVEL, 0x04 );                    // mute on, 0dB, power-down, hi-imp
    Codec_RSET( HPLCOM_OUTPUT_LEVEL, 0x04 );                    // mute on, 0dB, power-down, hi-imp
    Codec_RSET( DAC_R1_HPROUT_VOLUME, 0x80 );                   // DAC_R1-->HPROUT, 0dB
    Codec_RSET( HPROUT_OUTPUT_LEVEL, 0x04 );                    // mute on, 0dB, power-down, hi-imp
    Codec_RSET( HPRCOM_OUTPUT_LEVEL, 0x04 );                    // mute on, 0dB, power-down, hi-imp

    Codec_RSET( DAC_L1_LEFT_LOPM_VOLUME, 0x80 );                // DAC_L1-->LEFT_LOP/M, 0dB
    Codec_RSET( LEFT_LOPMM_OUTPUT_LEVEL, 0x09 );                // mute off, 0dB, power-up
    Codec_RSET( DAC_R1_RIGHT_LOPM_VOLUME, 0x80 );               // DAC_R1-->RIGHT_LOP/M, 0dB
    Codec_RSET( RIGHT_LOPMM_OUTPUT_LEVEL, 0x09 );               // mute off, 0dB, power-up
}


		
