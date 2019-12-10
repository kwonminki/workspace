#include "filter.h"

void ClearFilterBuf( float *x, Int32 len )
{
	Int32 i;

	for( i=0; i< len; i++ )
		x[i] = 0.f;
}


void FIRFilter( Int16 *x, const float *h, Int16 *r, float *dbuff, Int32 nh, Int32 nx  )
{
	Int32 i, j;
	float sum;

	for( i = 0; i < nx; i++ )
	{
		dbuff[0] = (float)x[i];
		sum = 0.f;
		
		for(j=0; j < nh; j++ )
			sum += h[j] * dbuff[j];

		for(j= nh-1; j > 0; j-- )
			dbuff[j] = dbuff[j-1]; //한칸씩 과거값들로 쉬프팅
			
		r[i] = (Int16)sum;
	}  
}

	
void IIRFilter( Int16 *x, const F_COEF *coef, Int16 *r, float (*dbuff)[2], Int32 nbiq, Int32 nx  )
{
	Int32 i, j;
	float ar, f_temp;
	
	for( j=0; j < nx; j++ )				// 입력 데이터 수만큼 반복
	{
		f_temp = (float)x[j];			// 새로운 입력
		for( i=0; i < nbiq; i++ )		// biquad 수만큼 반복
		{								// biquad를 direct form II 구조를 이용하여 연산
			ar = f_temp - coef[i].a[0]*dbuff[i][0] - coef[i].a[1]*dbuff[i][1];		
			f_temp = coef[i].b[0]*ar + coef[i].b[1]*dbuff[i][0] + coef[i].b[2]*dbuff[i][1];
		
			dbuff[i][1] = dbuff[i][0];
			dbuff[i][0] = ar;
		}	
		
		r[j] = (Int16)f_temp;
	}
}


