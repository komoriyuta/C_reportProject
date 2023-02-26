#ifndef _xlibcolorgc_h
#define _xlibcolorgc_h

#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "wavesimu.h"
//int setGrayscaleGC(u_int8_t lux,GC gc,Display *display);
void drawPointGC9x9(int x,int y,GC gc,Display *display,Window w);
void vecplot(float vector[100][100][3],GC gc,Display *display,Window w);
void waveColourPlt(pointMass wavesurf[100][100],GC gc,Display *display,Window w);

#endif