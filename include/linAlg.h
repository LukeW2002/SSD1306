#ifndef LINEAR_ALG
#define LINEAR_ALG
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include <errno.h>


		/* MATHS STRUCTURES DEFINITIONS */


typedef struct {
 double *data;
 int rows;
 int cols; 
}Matrix;

typedef struct {
 double *data;
 int dimension;
}Vector;

void *allocateMemory( size_t size);
Vector *allocateVector(int dimension);
Vector *assignVector(int dimension, double *data);
double *assigndouble(int rows, int cols, double *data);
double *allocatedouble(int rows, int cols);

void freedouble(double *matrix);
void freeVector(Vector *vector);
void printdouble(double *matrix);
void printVector(Vector *vector);

		/* MATRIX OPERATIONS */
	
void vectorSubtract(double *vector1, double *vector2, double *result, uint8_t dimension); // Define with vector2 - vector1
void vectorAdd(double *vector1, double *vector2, double *result, uint8_t dimension);
void setZeroVector(double *vector, uint8_t dimension);

void vectorMatrixMultiply(double *matrix, double *vector, double *result, uint8_t rowsM1, uint8_t colsM1, uint8_t dimension);
void matrixMultiply( double *matrix1, double *matrix2, double *result, uint8_t rowsM1, uint8_t colsM1, uint8_t rowsM2, uint8_t colsM2); // Defined with right hand multiplication of matrix1 to matrix2
void matrixAdd( double *matrix, double *matrix2, double *result, uint8_t rowsM1, uint8_t colsM1, uint8_t rowsM2, uint8_t colsM2);
void matrixSubtract( double *matrix, double *matrix2, double *result, uint8_t rowsM1, uint8_t colsM1, uint8_t rowsM2, uint8_t colsM2);
void matrixTranspose(double *matrix, double *result, uint8_t rowsM1, uint8_t colsM1);
void matrixCopy(double *matrix, double *result, uint8_t rowsM1, uint8_t colsM1);
void setIdentity(double *matrix, uint8_t rowsM1, uint8_t colsM1);
void setZero(double *matrix, uint8_t rowsM1, uint8_t colsM1);

			/* MATRIX INVERSION */
void choleskyDecomp(double *matrix, double *result, uint8_t rowsM1, uint8_t colsM1);
void forwardSubsitution(double *matrix, double *e, double *X, uint8_t rowsM1, uint8_t colsM1);
void backSubsitution(double *matrix, double *e, double *X, uint8_t rowsM1, uint8_t colsM1);
void matrixInverse(double *A, double *result, uint8_t rowsM1, uint8_t colsM1);


#endif

