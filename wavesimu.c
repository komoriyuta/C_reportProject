#include "wavesimu.h"
#include <stdio.h>
#include <math.h>


void pMReset(pointMass *resetpoint,float situryou){
    resetpoint->mass = situryou;
    resetpoint->accel = 0;
    resetpoint->accelBuf = 0;
    resetpoint->vel = 0;
    resetpoint->velBuf = 0;
    resetpoint->posZ = 0;
}

void pMintegral(pointMass *integralpoint){
    integralpoint->vel += (integralpoint->accel+integralpoint->accelBuf)*DELTA_T;
    integralpoint->posZ += (integralpoint->vel+integralpoint->velBuf)*DELTA_T;

    integralpoint->accelBuf=integralpoint->accel;
    integralpoint->velBuf=integralpoint->vel;
}


void waveUpdate(pointMass wavefront[100][100]){
    for(int i=1;i<100-1;i++){
        for (int k=1;k<100-1;k++){
            wavefront[i][k].accel=-(4*wavefront[i][k].posZ-(wavefront[i-1][k].posZ+wavefront[(i+1)][k].posZ+wavefront[i][k-1].posZ+wavefront[i][k+1].posZ))*0.6-wavefront[i][k].vel*0.08;
            pMintegral(&wavefront[i][k]);
        }
    }
}
void setgausian2d(pointMass wavefront[100][100],int x,int y){
    for(int i=-5;i<6;i++){
        for(int k=-5;k<6;k++){
            float r2=i*i+k*k;
            if(x+i>0||x+i<100||y+k>0||y+k<100){
                wavefront[x+i][y+k].posZ+=2*exp(-r2/(2*10*10));
            }
        }
    }
}