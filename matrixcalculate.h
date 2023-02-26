#ifndef matrix_calculate_h_
#define matrix_calculate_h_

void matrixMultiple(float Matrix1[][3], float Matrix2[][3]);
void vecMatMultiple(float *Vector1,float Matrix1[][3]);
void vecMatMultiple_elm(float Vec_0,float Vec_1,float Vec_2,float *Vector1,float Matrix1[][3]);
void matrixAdd(int *Matrix1, int *Matrix2);
void matrixSubtract(int *Matrix1, int *Matrix2);
void matScaMultiple(int *Matrix1, int atai);
void vecplot(int vector[100][100][3]);
#endif