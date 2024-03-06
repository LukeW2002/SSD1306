#pragma once
#include "linAlg.h"

#define STATES 7
#define MEASURED 3
#define DT 0.1

typedef struct KalmanData{
	double X[STATES];    // State Vector
	double Xp[STATES];   // Predicted State Vector
	double P[STATES*STATES]; 		// Prediction Error Covariance */
	double Q[STATES*STATES]; 		// Process noise Covariance
	double R[MEASURED*MEASURED]; 		// Measurement Error Covariance 
	double K[STATES*MEASURED]; 		// Kalman Gain
	double F[STATES*STATES]; 		// Jacobian of process Noise
	double H[MEASURED*STATES]; 		// Jacobian of Measurenment Noise
	double Ht[STATES*MEASURED]; 	// Transpose of the Jacobian
	double Ft[STATES*STATES]; 	// Transpose of the process Jacobian
	double Pp[STATES*STATES]; 	// Prediction Errror Covariance after prediction but before the update
	double fx[STATES]; 	// model state
	double hx[MEASURED]; 	// model Measurement Function
}kalmanData;

void kalman(kalmanData *kf, Vector *data);