#include "xlibcolorgc.h"
#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
/*
int setGrayscaleGC(u_int8_t lux,GC gc,Display *display){
    Colormap cmap;
    XColor c0, c1;
    cmap = DefaultColormap(display, 0);
    char str[19];
    sprintf(str, "rgb:%02X/%02X/%02X",lux,lux,lux);
    XAllocNamedColor(display, cmap, &str, &c1, &c0);
    return c1.pixel;
}*/
void drawPointGC9x9(int x,int y,GC gc,Display *display,Window w){
    XDrawPoint(display, w, gc,x,y);
    XDrawPoint(display, w, gc,x,y+1);
    XDrawPoint(display, w, gc,x,y+2);
    XDrawPoint(display, w, gc,x-1,y);
    XDrawPoint(display, w, gc,x-1,y+1);
    XDrawPoint(display, w, gc,x-1,y+2);
    XDrawPoint(display, w, gc,x-2,y);
    XDrawPoint(display, w, gc,x-2,y+1);
    XDrawPoint(display, w, gc,x-2,y+2);
}