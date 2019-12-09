/***********************************************************
* 	
*	Codec Initialization & Control Module Header 
*                              
*	File Name : Codec.h
*	Date Created :
*	Last modified :
*
************************************************************/

#ifndef _CODEC_H_
#define _CODEC_H_

#include "L138_common.h"

void CodecInit( unsigned int sampling_freq, Uint8 word_len, Uint8 input );
void ResetCodec( void );
void CodecInputVolume( Uint8 vol );
void CodecOutputAttenuation( Uint8 vol );
void CodecInputSelect( Uint8 input_sel );
void CodecSetHPFilter( Uint8 mode );
void CodecSampleRate44100( unsigned int sampleRate);
void CodecSampleRate48000( unsigned int sampleRate);

#define SAMPLING_FREQ_48000			48000
#define SAMPLING_FREQ_32000			32000
#define SAMPLING_FREQ_16000			16000
#define SAMPLING_FREQ_8000			8000

#define SAMPLING_FREQ_48KHz         0x00
#define SAMPLING_FREQ_24KHz         0x22
#define SAMPLING_FREQ_16KHz         0x44
#define SAMPLING_FREQ_12KHz         0x66
#define SAMPLING_FREQ_8KHz          0xAA

#define SAMPLING_FREQ_44100         44100
#define SAMPLING_FREQ_22050         22050
#define SAMPLING_FREQ_11025         11025

#define WORD_LEN_16BIT				0x48
#define WORD_LEN_20BIT				0x58
#define WORD_LEN_24BIT				0x68
#define WORD_LEN_32BIT				0x78

#define HPF_DISABLE					0x00
#define HPF_0045					0x50
#define HPF_0125					0xA0
#define HPF_025						0xF0

#define MIC							0x01
#define LINE_IN						0x02


#define AIC3106_I2C_ADDR	0x18    // I2C addr


/* AIC3106 Register Define */

#define PAGE_SELECT					0
#define SOFT_RESET					1
#define CODEC_SAMPLE_RATE_SEL		2
#define PLL_PROGRAMMING_A			3
#define PLL_PROGRAMMING_B			4
#define PLL_PROGRAMMING_C			5
#define PLL_PROGRAMMING_D			6
#define CODEC_DATAPATH_SETUP		7
#define AUDIO_SERIAL_DATA_INTFACE_A	8
#define AUDIO_SERIAL_DATA_INTFACE_B	9
#define AUDIO_SERIAL_DATA_INTFACE_C	10
#define AUDIO_CODEC_OVERFLOW		11
#define AUDIO_CODEC_DIGITAL_FILTER	12

#define LEFT_ADC_PGA_GAIN			15
#define RIGHT_ADC_PGA_GAIN			16
#define MIC3LR_LEFT_ADC				17
#define MIC3LR_RIGHT_ADC			18
#define LINE1L_LEFT_ADC				19
#define LINE2L_LEFT_ADC				20
#define LINE1R_LEFT_ADC				21
#define LINE1R_RIGHT_ADC			22
#define LINE2R_RIGHT_ADC			23
#define LINE1L_RIGHT_ADC			24

#define MICBIAS						25

#define LEFT_AGC_A					26
#define LEFT_AGC_B					27
#define LEFT_AGC_C					28
#define RIGHT_AGC_A					29
#define RIGHT_AGC_B					30
#define RIGHT_AGC_C					31

#define DAC_POWER_OUTPUT_DRIVER		37
#define HIGHPOWER_OUTPUT_DRIVER		38

#define DAC_OUTPUT_SWITCHING		41
#define LEFT_DAC_VOLUME				43
#define RIGHT_DAC_VOLUME			44

#define LINE2L_HPLOUT_VOLUME		45
#define PGA_L_HPLOUT_VOLUME			46
#define DAC_L1_HPLOUT_VOLUME		47
#define LINE2R_HPLOUT_VOLUME		48
#define PGA_R_HPLOUT_VOLUME			49
#define DAC_R1_HPLOUT_VOLUME		50
#define HPLOUT_OUTPUT_LEVEL			51

#define LINE2L_HPLCOM_VOLUME		52
#define PGA_L_HPLCOM_VOLUME			53
#define DAC_L1_HPLCOM_VOLUME		54
#define LINE2R_HPLCOM_VOLUME		55
#define PGA_R_HPLCOM_VOLUME			56
#define DAC_R1_HPLCOM_VOLUME		57
#define HPLCOM_OUTPUT_LEVEL			58

#define LINE2L_HPROUT_VOLUME		59
#define PGA_L_HPROUT_VOLUME			60
#define DAC_L1_HPROUT_VOLUME		61
#define LINE2R_HPROUT_VOLUME		62
#define PGA_R_HPROUT_VOLUME			63
#define DAC_R1_HPROUT_VOLUME		64
#define HPROUT_OUTPUT_LEVEL			65

#define LINE2L_HPRCOM_VOLUME		66
#define PGA_L_HPRCOM_VOLUME			67
#define DAC_L1_HPRCOM_VOLUME		68
#define LINE2R_HPRCOM_VOLUME		69
#define PGA_R_HPRCOM_VOLUME			70
#define DAC_R1_HPRCOM_VOLUME		71
#define HPRCOM_OUTPUT_LEVEL			72

#define LINE2L_MONOLOPM_VOLUME		73
#define PGA_L_MONOLOPM_VOLUME		74
#define DAC_L1_MONOLOPM_VOLUME		75
#define LINE2R_MONOLOPM_VOLUME		76
#define PGA_R_MONOLOPMT_VOLUME		77
#define DAC_R1_MONOLOPM_VOLUME		78
#define MONOLOPM_OUTPUT_LEVEL		79

#define LINE2L_LEFT_LOPM_VOLUME		80
#define PGA_L_LEFT_LOPM_VOLUME		81
#define DAC_L1_LEFT_LOPM_VOLUME		82
#define LINE2R_LEFT_LOPM_VOLUME		83
#define PGA_R_LEFT_LOPM_VOLUME		84
#define DAC_R1_LEFT_LOPM_VOLUME		85
#define LEFT_LOPMM_OUTPUT_LEVEL		86

#define LINE2L_RIGHT_LOPM_VOLUME	87
#define PGA_L_RIGHT_LOPM_VOLUME		88
#define DAC_L1_RIGHT_LOPM_VOLUME	89
#define LINE2R_RIGHT_LOPM_VOLUME	90
#define PGA_R_RIGHT_LOPM_VOLUME		91
#define DAC_R1_RIGHT_LOPM_VOLUME	92
#define RIGHT_LOPMM_OUTPUT_LEVEL	93

#define GPIO1						98
#define GPIO2						99
#define ADDITIONAL_GPIO_A			100
#define ADDITIONAL_GPIO_B			101
#define CLOCK_GENERATION			102


/*
** Register Address for AIC31 Codec
*/
#define AIC31_P0_REG0               (0)  /* Page Select  */
#define AIC31_P0_REG1               (1)  /* Software Reset */
#define AIC31_P0_REG2               (2)  /* Codec Sample Rate Select */
#define AIC31_P0_REG3               (3)  /* PLL Programming A */
#define AIC31_P0_REG4               (4)  /* PLL Programming B */
#define AIC31_P0_REG5               (5)  /* PLL Programming C */
#define AIC31_P0_REG6               (6)  /* PLL Programming D */
#define AIC31_P0_REG7               (7)  /* Codec Datapath Setup */
#define AIC31_P0_REG8               (8)  /* Audio Serial Data I/f Control A */
#define AIC31_P0_REG9               (9)  /* Audio Serial Data I/f Control B */
#define AIC31_P0_REG10              (10) /* Audio Serial Data I/f Control C */
#define AIC31_P0_REG11              (11) /* Audio Codec Overflow Flag */
#define AIC31_P0_REG12              (12) /* Audio Codec Digital Filter Ctrl */
#define AIC31_P0_REG13              (13) /* Headset / Button Press Detect A */
#define AIC31_P0_REG14              (14) /* Headset / Button Press Detect B */
#define AIC31_P0_REG15              (15) /* Left ADC PGA Gain Control */
#define AIC31_P0_REG16              (16) /* Right ADC PGA Gain Control */
#define AIC31_P0_REG17              (17) /* MIC3L/R to Left ADC Control */
#define AIC31_P0_REG18              (18) /* MIC3L/R to Right ADC Control */
#define AIC31_P0_REG19              (19) /* LINE1L to Left ADC Control */
#define AIC31_P0_REG20              (20) /* LINE2L to Left ADC Control */
#define AIC31_P0_REG21              (21) /* LINE1R to Left ADC Control */
#define AIC31_P0_REG22              (22) /* LINE1R to Right ADC Control */
#define AIC31_P0_REG23              (23) /* LINE2R to Right ADC Control */
#define AIC31_P0_REG24              (24) /* LINE1L to Right ADC Control */
#define AIC31_P0_REG25              (25) /* MICBIAS Control */
#define AIC31_P0_REG26              (26) /* Left AGC Control A */
#define AIC31_P0_REG27              (27) /* Left AGC Control B */
#define AIC31_P0_REG28              (28) /* Left AGC Control C */
#define AIC31_P0_REG29              (29) /* Right AGC Control A */
#define AIC31_P0_REG30              (30) /* Right AGC Control B */
#define AIC31_P0_REG31              (31) /* Right AGC Control C */
#define AIC31_P0_REG32              (32) /* Left AGC Gain */
#define AIC31_P0_REG33              (33) /* Right AGC Gain */
#define AIC31_P0_REG34              (34) /* Left AGC Noise Gate Debounce */
#define AIC31_P0_REG35              (35) /* Right AGC Noise Gate Debounce */
#define AIC31_P0_REG36              (36) /* ADC Flag */
#define AIC31_P0_REG37              (37) /* DAC Power and Output Driver Control */
#define AIC31_P0_REG38              (38) /* High Power Output Driver Control*/
#define AIC31_P0_REG40              (40) /* High Power Output Stage Control*/
#define AIC31_P0_REG41              (41) /* DAC Output Switching Control */
#define AIC31_P0_REG42              (42) /* Output Driver Pop Reduction */
#define AIC31_P0_REG43              (43) /* Left DAC Digital Volume Control */
#define AIC31_P0_REG44              (44) /* Right DAC Digital Volume Control */
#define AIC31_P0_REG45              (45) /* LINE2L to HPLOUT Volume Control */
#define AIC31_P0_REG46              (46) /* PGA_L to HPLOUT Volume Control */
#define AIC31_P0_REG47              (47) /* DAC_L1 to HPLOUT Volume Control */
#define AIC31_P0_REG48              (48) /* LINE2R to HPLOUT Volume Control */
#define AIC31_P0_REG49              (49) /* PGA_R to HPLOUT Volume Control */
#define AIC31_P0_REG50              (50) /* DAC_R1 to HPLOUT Volume Control */
#define AIC31_P0_REG51              (51) /* HPLOUT Output Level Control */
#define AIC31_P0_REG52              (52) /* LINE2L to HPLCOM Volume Control */
#define AIC31_P0_REG53              (53) /* PGA_L to HPLCOM Volume Control */
#define AIC31_P0_REG54              (54) /* DAC_L1 to HPLCOM Volume Control */
#define AIC31_P0_REG55              (55) /* LINE2R to HPLCOM Volume Control */
#define AIC31_P0_REG56              (56) /* PGA_R to HPLCOM Volume Control */
#define AIC31_P0_REG57              (57) /* DAC_R1 to HPLCOM Volume Control */
#define AIC31_P0_REG58              (58) /* HPLCOM Output Level Control */
#define AIC31_P0_REG59              (59) /* LINE2L to HPROUT Volume Control */
#define AIC31_P0_REG60              (60) /* PGA_L to HPROUT Volume Control */
#define AIC31_P0_REG61              (61) /* DAC_L1 to HPROUT Volume Control */
#define AIC31_P0_REG62              (62) /* LINE2R to HPROUT Volume Control */
#define AIC31_P0_REG63              (63) /* PGA_R to HPROUT Volume Control  */
#define AIC31_P0_REG64              (64) /* DAC_R1 to HPROUT Volume Control */
#define AIC31_P0_REG65              (65) /* HPROUT Output Level Control */
#define AIC31_P0_REG66              (66) /* LINE2L to HPRCOM Volume Control  */
#define AIC31_P0_REG67              (67) /* PGA_L to HPRCOM Volume Control */
#define AIC31_P0_REG68              (68) /* DAC_L1 to HPRCOM Volume Control */
#define AIC31_P0_REG69              (69) /* LINE2R to HPRCOM Volume Control */
#define AIC31_P0_REG70              (70) /* PGA_R to HPRCOM Volume Control */
#define AIC31_P0_REG71              (71) /* DAC_R1 to HPRCOM Volume Control */
#define AIC31_P0_REG72              (72) /* HPRCOM Output Level Control */
#define AIC31_P0_REG73              (73) /* LINE2L to MONO_LOP/M Volume Control*/
#define AIC31_P0_REG74              (74) /* PGA_L to MONO_LOP/M Volume Control */
#define AIC31_P0_REG75              (75) /* DAC_L1 to MONO_LOP/M Volume Control */
#define AIC31_P0_REG76              (76) /* LINE2R to MONO_LOP/M Volume Control */
#define AIC31_P0_REG77              (77) /* PGA_R to MONO_LOP/M Volume Control */
#define AIC31_P0_REG78              (78) /* DAC_R1 to MONO_LOP/M Volume Control */
#define AIC31_P0_REG79              (79) /* MONO_LOP/M Output Level Control */
#define AIC31_P0_REG80              (80) /* LINE2L to LEFT_LOP/M Volume Control */
#define AIC31_P0_REG81              (81) /* PGA_L to LEFT_LOP/M Volume Control */
#define AIC31_P0_REG82              (82) /* DAC_L1 to LEFT_LOP/M Volume Control */
#define AIC31_P0_REG83              (83) /* LINE2R to LEFT_LOP/M Volume Control */
#define AIC31_P0_REG84              (84) /* PGA_R to LEFT_LOP/M Volume Control */
#define AIC31_P0_REG85              (85) /* DAC_R1 to LEFT_LOP/M Volume Control */
#define AIC31_P0_REG86              (86) /* LEFT_LOP/M Output Level Control */
#define AIC31_P0_REG87              (87) /* LINE2L to RIGHT_LOP/M Volume Control */
#define AIC31_P0_REG88              (88) /* PGA_L to RIGHT_LOP/M Volume Control */
#define AIC31_P0_REG89              (89) /* DAC_L1 to RIGHT_LOP/M Volume Control */
#define AIC31_P0_REG90              (90) /* LINE2R to RIGHT_LOP/M Volume Control */
#define AIC31_P0_REG91              (91) /* PGA_R to RIGHT_LOP/M Volume Control */
#define AIC31_P0_REG92              (92) /* DAC_R1 to RIGHT_LOP/M Volume Control*/
#define AIC31_P0_REG93              (93) /* RIGHT_LOP/M Output Level Control */
#define AIC31_P0_REG94              (94) /* Module Power Status */
#define AIC31_P0_REG95              (95) /**< O/P Driver Short Circuit Detection Status*/
#define AIC31_P0_REG96              (96) /* Sticky Interrupt Flags */
#define AIC31_P0_REG97              (97) /* Real-time Interrupt Flags  */
#define AIC31_P0_REG98              (98) /* GPIO1 Control */
#define AIC31_P0_REG99              (99) /* GPIO2 Control */
#define AIC31_P0_REG100             (100)  /* Additional GPIO Control A */
#define AIC31_P0_REG101             (101)  /* Additional GPIO Control B */
#define AIC31_P0_REG102             (102)  /* Clock Generation Control */
#define AIC31_P0_REG109             (109)  /* DAC Quiescent Current Adjustment */

#endif
