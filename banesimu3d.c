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
/////////////////////////////////////////////

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

    w = XCreateSimpleWindow(dpy, root, 200, 200, WIDTH, HIGHT, BORDER, black, white);

    gc = XCreateGC(dpy, w, 0, NULL);

    XMapWindow(dpy, w);

  	XSetForeground(dpy,gc,black);

////////////////////////////////////////

    pointMass wavefront2d[100][100];
    for(int i=0;i<100;i++){for (int k=0;k<100; k++){pMReset(&wavefront2d[i][k],2);}}
    //wavefront2d[25][25].posZ=10;

    //for(int i=100;i<200;i++){wavefront2d[100][i].posZ=0;}
int j=0;
long tmesin=0;
int itibuff[100][100];
////////////////////////////////////////
    while (1){
        //++tmesin;
            //    XClearWindow(dpy, w);

        //wavefront2d[50][50].posZ=1*sin(tmesin/1000);
        //wavefront2d[50][50].posZ=-sin(2*3.141592*0.00001*j);
        //j=j%30000;
        //j++;
        XSetForeground(dpy, gc, black);
        XFlush(dpy);
        //for(int i=230;i<270;i++){wavefront2d[235][i].posZ=0;}
        for(int t=0; t<20;t++){
            for(int i=1;i<99;++i){
                for (int k=1;k<99; ++k){wavefront2d[k][i].accel=0-(4*wavefront2d[k][i].posZ-(wavefront2d[k-1][i].posZ+wavefront2d[k][i-1].posZ+wavefront2d[k+1][i].posZ+wavefront2d[k][i+1].posZ))*0.5-wavefront2d[k][i].vel*0.03;
                pMintegral(&wavefront2d[k][i]);
                //XSetForeground(dpy,gc,wavefront2d[k][i].posZ*0.1);
                u_int8_t glay=wavefront2d[k][i].posZ*64+128;
                XSetForeground(dpy, gc, 0x010000 *glay + 0x0100 * glay + glay);
                //char moji[10];
                //sprintf(&moji,"%d",wavefront2d[k][i].posZ);
                //XDrawPoint(dpy,w,gc,10*k,10*i);
                //printf("loop1");
               drawPointGC9x9(3*i,3*k,gc,dpy,w);
                ++tmesin;
            }}}
           
           //if(tmesin<500000*3.15){
            wavefront2d[50][60].posZ=2*sin(tmesin/500000.0);
            wavefront2d[50][40].posZ=2*sin(tmesin/500000.0);
            for (int i = 0; i < 100; i++){
                wavefront2d[0][i].posZ=-wavefront2d[1][i].posZ;
                wavefront2d[99][i].posZ=-wavefront2d[98][i].posZ;
                wavefront2d[i][0].posZ=-wavefront2d[i][1].posZ;
                wavefront2d[i][99].posZ=-wavefront2d[i][98].posZ;
            }
            XClearWindow(dpy, w);
            for(int k=0;k<100;k++){
                float kf=k*0.004+0.996;
                for(int i=0; i<100;++i){
                    XSetForeground(dpy, gc, white);
                    drawPointGC9x9(9*i*kf,itibuff[k][i],gc,dpy,w);
                    XSetForeground(dpy, gc, black);
                    drawPointGC9x9(9*i*kf,400-wavefront2d[k][i].posZ*50+6*k,gc,dpy,w);
                    itibuff[k][i]=400-wavefront2d[k][i].posZ+50+6*k;
                    }
            }
        }   //printf("a");
}
