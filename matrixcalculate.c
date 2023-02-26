#include "matrixcalculate.h"
#include "xlibcolorgc.h"

void matrixMultiple(float Matrix1[][3], float Matrix2[][3]){
    float _matrixbuf[3][3];
    for(int i=0;i<3;i++){for(int k=0;k<3;k++){_matrixbuf[i][k]=Matrix1[i][k];}}
    for(int i=0;i<3;i++){
        for(int k=0;k<3;k++){
            Matrix1[i][k]=0;
            for(int j=0;j<3;j++){
                Matrix1[i][k]+=_matrixbuf[i][j]*Matrix2[j][k];
            }
        }
    }
}
void vecMatMultiple(float *Vector1,float Matrix1[][3]){
    float _vecbuf[3];
    for(int i=0;i<3;i++){_vecbuf[i]=Vector1[i];}
    for (int i = 0;i<3; i++){
        Vector1[i]=0;
        for(int k=0;k<3;k++){
            Vector1[i]+=_vecbuf[k]*Matrix1[i][k];
        }
    }
    
}
void vecMatMultiple_elm(float Vec_0,float Vec_1,float Vec_2,float *Vector1,float Matrix1[][3]){
    float _vecbuf[3]={Vec_0,Vec_1,Vec_2};
    for (int i = 0;i<3; i++){
        Vector1[i]=0;
        for(int k=0;k<3;k++){
            Vector1[i]+=_vecbuf[k]*Matrix1[i][k];
        }
    }
}

void vecplot(int vector[100][100][3]){
    for(int i=0;i<100;i++){
        for(int k=0;k<100;k++){
            drawPointGC9x9(vector[i][k][0]*5*vector[i][k][0]+240,)
        }
    }
}

void matrixAdd(int *Matrix1, int *Matrix2){}
void matrixSubtract(int *Matrix1, int *Matrix2){}
void matScaMultiple(int *Matrix1, int atai){}