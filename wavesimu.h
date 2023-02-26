#ifndef _banesimu_h
#define _banesimu_h

#define DELTA_T 0.015

struct _pointmass_          //situten
{
    float posZ;             //iti
    float vel;              //sokudo
    float velBuf;           //sokudo buffer (sekibun you)
    float accel;            //kasokudo 
    float accelBuf;         //kasokudo buffer(sekibunyou)
    float mass;             //omosa
};

typedef struct _pointmass_ pointMass; 

void pMReset(pointMass *resetpoint,float situryou);
void pMintegral(pointMass *integralpoint);
void waveUpdate(pointMass wavefront[100][100]);
void setgausian2d(pointMass wavefront[100][100],int x,int y);

#endif