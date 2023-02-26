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
void vecplot(float vector[100][100][3],GC gc,Display *display,Window w){
    for(int i=0;i<100;i++){
        for(int k=0;k<100;k++){
            drawPointGC9x9(10*vector[i][k][0]*(vector[i][k][1]*0.009+0.991)+500,400-vector[i][k][2]*10*(vector[i][k][1]*0.009+0.991),gc,display,w);
            //drawPointGC9x9(5*k*i_f-i*2.2+240,400-wavefront2d[i][k].posZ*20+3*i,gc,dpy,buffer);
        }
    }
}
void waveColourPlt(pointMass wavesurf[100][100],GC gc,Display *display,Window w){
    for(int i=0;i<100;i++){
        for(int k=0;k<100;k++){
            u_int8_t glay=wavesurf[k][i].posZ*64+128;
            XSetForeground(display, gc, 0x010000 *glay + 0x0100 * glay + glay);
            drawPointGC9x9(3*i,3*k,gc,display,w);

        }
    }
}
