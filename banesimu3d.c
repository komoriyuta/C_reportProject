#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <math.h>

#include "wavesimu.h"
#include "xlibcolorgc.h"
#include "matrixcalculate.h"

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
    struct timespec lasttime,newtime;   

    timespec_get(&newtime, TIME_UTC); 
    newtime=lasttime;

	int x, y;
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
    float matrixZ[3][3]={{0.99984769515,-0.01745240643,0},
                            {0.01745240643,0.99984769515,0},
                            {0,0,1}};
    float matrixX[3][3]={{1,0,0},
                            {0,0.99984769515,0.01745240643},
                            {0,-0.01745240643,0.99984769515}};

    pointMass wavefront2d[100][100];
    for(int i=0;i<100;i++){for (int k=0;k<100; k++){pMReset(&wavefront2d[i][k],2);for(int j=0;j<3;j++){viewzahyou[i][k][j];}}}


    int j=0;
    long tmesin=0;
    setgausian2d(wavefront2d,50,50);
    for(int i=0;i<40;i++){
    matrixMultiple(view_matrix,matrixX);}
////////////////////////////////////////
    while (1){
        
        if(tmesin%100==0){
            matrixMultiple(view_matrix,matrixZ);
        }
            
        
        waveUpdate(wavefront2d);
        XSetForeground(dpy, gc, black);
        viewVectorsTrans(wavefront2d,viewzahyou,view_matrix);
        vecplot(viewzahyou,gc,dpy,buffer); 

        waveColourPlt(wavefront2d,gc,dpy,buffer);
        
        ++tmesin;
              
        
        //wavefront2d[50][50].posZ=2*sin(tmesin/500000.0);
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
