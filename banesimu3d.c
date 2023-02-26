#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <math.h>

#include "wavesimu.h"
#include "xlibcolorgc.h"

#define WIDTH 1000
#define HIGHT 1000 
#define BORDER 2


int main(int argc, char **argv){
    Display *dpy;
	Window w, quit;
 	Window root;
 	int screen;
 	unsigned long black, white;
 	GC gc;
 	XEvent e;
    
	int i, x, y;
	dpy = XOpenDisplay("");
	root = DefaultRootWindow(dpy);
	screen = DefaultScreen(dpy);
	white = WhitePixel(dpy, screen);
	black = BlackPixel(dpy, screen);

    w = XCreateSimpleWindow(dpy, root, 200, 200, WIDTH*2, HIGHT*2, BORDER, black, white);
    gc = XCreateGC(dpy, w, 0, NULL);
    XSetForeground(dpy, gc, white);

    XMapWindow(dpy, w);
  	XSetForeground(dpy,gc,black);

    Pixmap buffer=XCreatePixmap(dpy,w,WIDTH,HIGHT,DefaultDepth(dpy,0));
    //XFillRectangle(dpy,buffer,gc,0,0,WIDTH,HIGHT);
////////////////////////////////////////

    float viewzahyou[100][100][3];
    float view_matrix[3][3]={{1,0,0},
                            {0,1,0},
                            {0,0,1}};

    XPoint renzokuiti[10000];
    pointMass wavefront2d[100][100];
    
    for(int i=0;i<100;i++){for (int k=0;k<100; k++){pMReset(&wavefront2d[i][k],2);for(int j=0;j<3;j++){viewzahyou[i][k][j];}}}
    int j=0;
    long tmesin=0;
////////////////////////////////////////
    while (1){
        XSetForeground(dpy, gc, black);
        XFlush(dpy);
        //for(int i=230;i<270;i++){wavefront2d[235][i].posZ=0;}
        //for(int t=0; t<20;t++){
            waveUpdate(wavefront2d);
            for(int i=1;i<99;++i){
                float i_f=i*0.009+0.991;
                for (int k=1;k<99; ++k){
                    //wavefront2d[k][i].accel=0-(4*wavefront2d[k][i].posZ-(wavefront2d[k-1][i].posZ+wavefront2d[k][i-1].posZ+wavefront2d[k+1][i].posZ+wavefront2d[k][i+1].posZ))*0.5-wavefront2d[k][i].vel*0.05;
                    //pMintegral(&wavefront2d[k][i]);
                    u_int8_t glay=wavefront2d[k][i].posZ*64+128;
                    XSetForeground(dpy, gc, 0x010000 *glay + 0x0100 * glay + glay);
                    
                    drawPointGC9x9(3*i,3*k,gc,dpy,buffer);
                    //renzokuiti[k+i*100].x=9*k*i_f-2*i;
                    //renzokuiti[k+i*100].y=400-wavefront2d[i][k].posZ*80+6*i;
                    drawPointGC9x9(5*k*i_f-i*2.2+240,400-wavefront2d[i][k].posZ*20+3*i,gc,dpy,buffer);
                    ++tmesin;
                }
            }
            XDrawPoints(dpy,buffer,gc,renzokuiti,10000, CoordModeOrigin);
        
        wavefront2d[50][50].posZ=2*sin(tmesin/500000.0);
        for (int i = 0; i < 100; i++){
            wavefront2d[0][i].posZ=-wavefront2d[1][i].posZ;
            wavefront2d[99][i].posZ=-wavefront2d[98][i].posZ;
            wavefront2d[i][0].posZ=-wavefront2d[i][1].posZ;
            wavefront2d[i][99].posZ=-wavefront2d[i][98].posZ;
        }
        XSetGraphicsExposures(dpy,gc,False);

        XCopyArea(dpy,buffer,w,gc,0,0,WIDTH,HIGHT,0,0);
        XSetForeground(dpy, gc, white);
        XFillRectangle(dpy,buffer,gc,0,0,WIDTH,HIGHT);

    }
}
