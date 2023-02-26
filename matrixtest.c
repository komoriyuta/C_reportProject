#include <stdio.h>
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
int main(){
    float  E[3][3]={ {1,0,0},
                     {0,1,0},
                     {0,0,1}};
    float  test[3][3]={{3,4,5},
                       {5,6,7},
                       {3,6,2}};
    float vector[3]={1,2,3};
    matrixMultiple(test,E);
    for (size_t i = 0; i < 3; i++){
        for(int k=0;k<3;k++)
        printf("%f\n",test[i][k]);
    }
    vecMatMultiple(vector,E);
    printf("\n");
    for(int i=0;i<3;i++){
        printf("%f",vector[i]);
    }
    
}