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

#define PI		3.141592654f
#define MAX_AMP	0.99f

int GenSine( float *buf, float freq, float sampling_freq, int len, int index )
{
	int i;
	float w=2.f*PI*freq/sampling_freq;

	for(i=0; i < len; i++)
	{
		buf[i] = MAX_AMP*sinf(w*index++);
		if( index == sampling_freq )
			index = 0;
	}

	return index;
}
