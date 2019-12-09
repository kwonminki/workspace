#ifndef _FILTER_H__
#define _FILTER_H__

#include <ti/pspiom/cslr/tistdtypes.h>

typedef struct f_coef
	{
		double a[2];
		double b[3];
	} F_COEF;			// 부동소수점 필터 계수를 위한 구조체 

void ClearFilterBuf( float *x, Int32 len );
void FIRFilter( Int16 *x, const float *h, Int16 *r, float *dbuff, Int32 nh, Int32 nx  );
void IIRFilter( Int16 *x, const F_COEF *coef, Int16 *r, float (*dbuff)[2], Int32 nbiq, Int32 nx );

#define NBIQ	3

#endif
