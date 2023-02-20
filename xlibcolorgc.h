#ifndef _xlibcolorgc_h
#define _xlibcolorgc_h

#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

//int setGrayscaleGC(u_int8_t lux,GC gc,Display *display);
void drawPointGC9x9(int x,int y,GC gc,Display *display,Window w);


#endif