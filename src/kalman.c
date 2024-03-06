#include "kalman.h"
#include "linAlg.h"


//  https://ahrs.readthedocs.io/en/latest/?

void kalman(kalmanData *kf, Vector *data)
{
	/*	COVARIANCE UPDATE
			
						*/

	double temp1[STATES*STATES];
	matrixMultiply(  kf->F,   kf->P,  temp1,  STATES, STATES, STATES, STATES);
	matrixTranspose( kf->F,   kf->Ft, STATES,  STATES);
	matrixMultiply(  temp1,   kf->Ft, kf->Pp, STATES, STATES, STATES, STATES);
	matrixAdd(       kf->Pp,  kf->Q,  kf->Pp, STATES, STATES, STATES, STATES);
	
	
	/* KALMAN GAIN*/
	double temp2[STATES*MEASURED];
	double temp3[MEASURED*STATES];
	double temp4[MEASURED*MEASURED];
	matrixTranspose( kf->H,   kf->Ht,        STATES,   MEASURED);
	matrixMultiply(  kf->Pp,  kf->Ht, temp2, STATES,   STATES,   STATES,   MEASURED);
	matrixMultiply(  kf->H,   kf->Pp, temp3, MEASURED, STATES,   STATES,   STATES);
	matrixMultiply(  temp3,   kf->Ht, temp4, MEASURED, STATES,   STATES,   MEASURED);
	matrixAdd(       temp4,   kf->R,  temp4, MEASURED, MEASURED, MEASURED, MEASURED );
	matrixInverse(   temp4,   temp4,		 MEASURED, MEASURED);
	matrixMultiply ( temp2,   temp4,  kf->K, STATES,   MEASURED, MEASURED, MEASURED);
	
	//State Update
	double temp5[MEASURED];
	double temp6[STATES];
	double temp7[MEASURED];
	vectorMatrixMultiply( kf->H,   kf->X,  temp7, MEASURED,   STATES, STATES);
	vectorSubtract(       temp7,   data,   temp5, MEASURED);
	vectorMatrixMultiply( kf->K,   temp5,  temp6, STATES,   MEASURED, STATES); 
	vectorAdd(			  kf->fx,  temp6,  kf->X, STATES);

	double id[STATES*STATES];
	setIdentity(id, STATES, STATES);
	matrixMultiply(kf->K, kf->H,  temp1, STATES, MEASURED, MEASURED, STATES);
	matrixSubtract(id,    temp1,  temp1, STATES,   STATES,   STATES, STATES);
	matrixMultiply(temp1, kf->Pp, kf->P, STATES,   STATES, STATES, STATES);
}
