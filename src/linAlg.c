#include "linAlg.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAX_ARRAY 256


		/* MATRIX OPERATIONS */
void setIdentity(double *matrix, uint8_t rowsM1, uint8_t colsM1)
{
	for (int i = 0; i< rowsM1; i++)
	{
		for (int j = 0; j < colsM1; j++ )
		{
			matrix[i * (colsM1) + j] = 0;
			matrix[i * (colsM1) + i] = 1;
		}
	}
}

void setZero(double *matrix, uint8_t rowsM1, uint8_t colsM1)
{
	for (int i = 0; i< rowsM1; i++)
	{
		for (int j = 0; j < colsM1; j++ )
		{
			matrix[i * (colsM1) + j] = 0;
		}
	}
}

void matrixMultiply(double *matrix1, double *matrix2, double *result, uint8_t rowsM1, uint8_t colsM1, uint8_t rowsM2, uint8_t colsM2)
{
	if (colsM1 != rowsM2)
	{
		printf("(cols, rows)\n");
		printf("\n ERROR matrixMultiply \n INCORRECT DIMENSION \n");
		exit(1);
	}
	for (int i = 0; i < rowsM1; ++i)
	{
		for (int j = 0; j < colsM2; ++j) 
		{
			result[i*(colsM2) +j] = 0;
			for (int l = 0; l < colsM1; ++l)
			{
				result[i*(colsM2) + j] += matrix1[i*(colsM1) + l] * matrix2[l*(colsM1)+j];
			}
		}
	}
}

void setZeroVector(double *vector, uint8_t dimension)
{
	for (int i = 0; i< dimension; i++)
	{
		vector[i] = 0;
	}
}

void vectorMatrixMultiply(double *matrix, double *vector, double *result, uint8_t rowsM1, uint8_t colsM1, uint8_t dimensionV1)
{
	if (colsM1 != dimensionV1)
	{
		printf("\n ERROR vectorMultiply \n INCORRECT DIMENSION \n");
		exit(1);
	}
	for (int i = 0; i < rowsM1; i++)
	{
		result[i] = 0;
		for(int j = 0; j < colsM1; j++)
		{
			result[i] += matrix[i*(colsM1) + j] * vector[j];
		}
	}
}

void vectorAdd(double *vector1, double *vector2, double *result, uint8_t dimension)
{
	for (int i = 0; i < dimension; i++)
	{
		result[i] = vector2[i] + vector1[i];
	}
}

void vectorSubtract(double *vector1, double *vector2, double *result, uint8_t dimension)
{
	for (int i = 0; i < dimension; i++)
	{
		result[i] = vector2[i] - vector1[i];
	}
}

void matrixAdd( double *matrix1, double *matrix2, double *result, uint8_t rowsM1, uint8_t colsM1, uint8_t rowsM2, uint8_t colsM2)
{
	if (rowsM1 != rowsM2 && colsM2 != colsM1)
	{
		printf("\n ERROR matrixAdd \n INCORRECT DIMENSION \n");
		exit(1);
	}

	for (int i = 0; i< rowsM1; ++i)
	{
		for (int j = 0; j< colsM2; ++j)
		{
			result[i*(colsM1) +j] = matrix1[i* (colsM1) +j ] + matrix2[i*(colsM2) + j];
		}
	}
}

void matrixSubtract( double *matrix1, double *matrix2, double *result, uint8_t rowsM1, uint8_t colsM1, uint8_t rowsM2, uint8_t colsM2)
{
	if (rowsM1 != rowsM2 && colsM2 != colsM1)
	{
		printf("\n ERROR matrixAdd \n INCORRECT DIMENSION \n");
		exit(1);
	}

	for (int i = 0; i< rowsM1; ++i)
	{
		for (int j = 0; j< colsM2; ++j)
		{
			result[i*(colsM1) +j] =  matrix2[i*(colsM2) + j] - matrix1[i* (colsM1) +j ];
		}
	}
}

void matrixCopy(double *matrix, double *result, uint8_t rowsM1, uint8_t colsM1)
{
	for (int i = 0; i < rowsM1; i++)
	{
		for (int j = 0; j < colsM1; j++)
		{
			result[i * (colsM1) + j] = matrix[i * (colsM1) + j];
		}
	}
}

void matrixTranspose(double *matrix, double *result, uint8_t rowsR1, uint8_t colsR1)
{
	for ( int i = 0; i < rowsR1; i++)
	{
		for (int  j = 0; j < colsR1; j++)
		{
			result[i * colsR1 + j] = matrix[j * colsR1 + i];
		}
	}
}

			/* MATRIX INVERSION */
void choleskyDecomp(double *matrix, double *result, uint8_t rowsM1, uint8_t colsM1)
{
	if (rowsM1 != colsM1)
	{
		printf("\n ERROR choleskyDecomp \n INCORRECT DIMENSION \n");
		exit(1);
	}
	double sum;
	int n = rowsM1;
	setZero(result, sizeof(result)/sizeof(result[0]), sizeof(result)/sizeof(result[0]));
	for(int i = 0; i < n; i++)
	{
		for (int j = 0; j < (i+1) ; j++)
		{
			sum = 0.0;
			for (int k = 0; k < j; k++)
			{
				sum += result[ i * n +k] * result[j * n + k];
			}
			if ( i == j)
			{
				result[i * n + j] = sqrt(matrix[i * n + i] - sum);
			}
			else
			{
				result[i * n + j] = (1.0 / result[j * n + j]) * (matrix[ i * n + j] - sum);
			}
		}
	}
}


void forwardSubsitution(double *matrix, double*e, double *X, uint8_t rowsM1, uint8_t colsM1)
{
	if (rowsM1 != colsM1)
	{
		printf("\n ERROR forwardSubsitution \n INCORRECT DIMENSION \n");
		exit(1);
	}
	for (int i = 0; i < rowsM1; i++)
	{
		double sum = e[i];
		for ( int j = 0; j <= (i-1); j++)
		{
			sum -= matrix[i*(colsM1) +j ] * X[j];
		}
		X[i] = sum / matrix[i*(colsM1)+i];
	}	
}

void backSubsitution(double *matrix, double *e, double *X, uint8_t rowsM1, uint8_t colsM1) 
{
	if (rowsM1 != colsM1)
	{
		printf("\n ERROR backSubsitution \n INCORRECT DIMENSION \n");
		exit(1);
	}
	for (int i = (rowsM1) - 1; i >= 0; i--)
	{
		double sum = e[i];
		for (int j = i+1; j < (colsM1); j++)
		{
			sum -= matrix[i*(colsM1) + j] * X[j];
		}
		X[i] = sum / matrix[i*(colsM1) + i];
	}	
}

void matrixInverse(double *matrix, double *result, uint8_t rowsM1, uint8_t colsM1)
{
	if (rowsM1 != colsM1)
	{
		printf("\n ERROR matrixInverse \n INCORRECT DIMENSION \n");
		exit(1);
	}
	double L[rowsM1*colsM1];
	double transposeL[rowsM1*colsM1];

	choleskyDecomp(matrix, L, rowsM1, colsM1);
	matrixTranspose(L, transposeL, rowsM1, colsM1);


	for (int j = 0; j < rowsM1; j++)
	{
		double e[colsM1];
		double x[colsM1];
		double y[colsM1];
		//Memset them 

		e[j] = 1.0;
		forwardSubsitution(L, e, x, rowsM1, colsM1);
		backSubsitution(transposeL, x, y, rowsM1, colsM1);
		for (int k = (rowsM1)-1; k >=0 ; k--)
		{
			result[k*(rowsM1)+j] = y[k];
			//printf("result: %fl\n y: %fl\n", result->data[k*(matrix->rows)+j], y->data[k]);
		}

	}
}

