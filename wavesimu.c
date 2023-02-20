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