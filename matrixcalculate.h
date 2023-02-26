#ifndef matrix_calculate_h_
#define matrix_calculate_h_

#include <math.h>
#include "wavesimu.h"

void matrixMultiple(float Matrix1[3][3], float Matrix2[3][3]);
void vecMatMultiple(float *Vector1,float Matrix1[3][3]);
void vecMatMultiple_elm(float Vec_0,float Vec_1,float Vec_2,float *Vector1,float Matrix1[][3]);

void matScaMultiple(int *Matrix1, int atai);

void viewVectorsTrans(pointMass waveSurf[100][100],float viewVector[100][100][3],float viewMatrix[3][3]);

#endif