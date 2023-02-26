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
            wavefront[i][k].accel=-(4*wavefront[i][k].posZ-(wavefront[i-1][k].posZ+wavefront[(i+1)][k].posZ+wavefront[i][k-1].posZ+wavefront[i][k+1].posZ))*0.5-wavefront[i][k].vel*0.01;
            pMintegral(&wavefront[i][k]);
        }
    }
}