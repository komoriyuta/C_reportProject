#include "matrixcalculate.h"
#include <math.h>

void matrixMultiple(float Matrix1[3][3], float Matrix2[3][3]){
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
void matrixMultiple_dainyu(float Matrix0[3][3],float Matrix1[3][3], float Matrix2[3][3]){
    float _matrixbuf[3][3];
    for(int i=0;i<3;i++){for(int k=0;k<3;k++){_matrixbuf[i][k]=Matrix1[i][k];}}
    for(int i=0;i<3;i++){
        for(int k=0;k<3;k++){
            Matrix0[i][k]=0;
            for(int j=0;j<3;j++){
                Matrix0[i][k]+=_matrixbuf[i][j]*Matrix2[j][k];
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
void viewVectorsTrans(pointMass waveSurf[100][100],float viewVector[100][100][3],float viewMatrix[3][3]){
     for(int i=0;i<100;++i){
        for (int k=0;k<100; ++k){
            vecMatMultiple_elm((i-50)/2,(k-50)/2,waveSurf[i][k].posZ*20,&viewVector[i][k][3],viewMatrix);

        }
     }
}

void matScaMultiple(float Matrix1[3][3], float atai){
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            Matrix1[i][j]*=atai;
        }
        
    }
    
}