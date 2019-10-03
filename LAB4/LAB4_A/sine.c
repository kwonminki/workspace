/***********************************************************
*
*	Sine Generation Module
*
*	File Name : sine.c
*	Date Created :
*	Last modified :
*
************************************************************/

#include <math.h>

#define PI		3.141592654
#define MAX_AMP	28000

int GenSine( short *buf, float freq, float sampling_freq, int len, int index )
{
	int i;
	float w=2.*PI*freq/sampling_freq;

	for(i=0; i < len; i++)
	{
		buf[i] = (short)(MAX_AMP*sin(w*index++));
		if( index == sampling_freq )
			index = 0;
	}

	return index;
}
