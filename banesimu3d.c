#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xlocale.h>
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
    struct timeval lasttime,newtime;   

     
    newtime=lasttime;

	int x, y;
	dpy = XOpenDisplay("");
	root = DefaultRootWindow(dpy);
	screen = DefaultScreen(dpy);
	white = WhitePixel(dpy, screen);
	black = BlackPixel(dpy, screen);
    w = XCreateSimpleWindow(dpy, root, 200, 200, WIDTH*2, HIGHT*2, BORDER, black, white);
    quit = XCreateSimpleWindow(dpy, w, 3, 3, 30, 12, BORDER, black, white);

    gc = XCreateGC(dpy, w, 0, NULL);
    XSetForeground(dpy, gc, white);

    XMapWindow(dpy, w);
    XMapSubwindows(dpy, w);
  	XSetForeground(dpy,gc,black);

    XSelectInput(dpy, w, ButtonPressMask|KeyPressMask|KeyReleaseMask);
    XSelectInput(dpy, quit, ButtonPressMask);
    

    Pixmap buffer=XCreatePixmap(dpy,w,WIDTH,HIGHT,DefaultDepth(dpy,0));
    //XFillRectangle(dpy,buffer,gc,0,0,WIDTH,HIGHT);
////////////////////////////////////////

    float viewzahyou[100][100][3];
    float view_matrix[3][3]={{1,0,0},
                            {0,1,0},
                            {0,0,1}};
    float viewX_matrix[3][3]={{1,0,0},
                            {0,1,0},
                            {0,0,1}};
    float viewZ_matrix[3][3]={{1,0,0},
                            {0,1,0},
                            {0,0,1}};
    float matrixplusZ[3][3]={{0.99984769515,-0.01745240643,0},
                            {0.01745240643,0.99984769515,0},
                            {0,0,1}};
    float matrixplusX[3][3]={{1,0,0},
                            {0,0.99984769515,0.01745240643},
                            {0,-0.01745240643,0.99984769515}};

    float matrixminusZ[3][3]={{0.99984769515,0.01745240643,0},
                            {-0.01745240643,0.99984769515,0},
                            {0,0,1}};
    float matrixminusX[3][3]={{1,0,0},
                            {0,0.99984769515,-0.01745240643},
                            {0,+0.01745240643,0.99984769515}};
    pointMass wavefront2d[100][100];
    for(int i=0;i<100;i++){for (int k=0;k<100; k++){pMReset(&wavefront2d[i][k],2);for(int j=0;j<3;j++){viewzahyou[i][k][j];}}}

    float scale=1;

    int j=0;
    long tmesin=0;
    //setgausian2d(wavefront2d,50,50);
    for(int i=0;i<40;i++){
    matrixMultiple(viewX_matrix,matrixplusX);}
    int sinmode=0;
////////////////////////////////////////
    while (1){
        gettimeofday(&newtime,NULL);
        XSetForeground(dpy, gc, black);
        XDrawString(dpy,buffer,gc,300,20,"WASD:rotate,MouseWheel:scaling,ClickGrayArea:make wave,R:reset,NumberKey:change mode",84);
        if(sinmode==0){
            XDrawString(dpy,buffer,gc,300,40,"Normalmode",10);
        }else if (sinmode==1){
            XDrawString(dpy,buffer,gc,300,40,"center sin mode",15);
        }else XDrawString(dpy,buffer,gc,300,40,"two sin mode",13);
        
        XDrawString(dpy, quit, gc, 4, 10, "Exit", 4);
        if(XCheckMaskEvent(dpy,ButtonPressMask|KeyPressMask,&e)){
            switch(e.type){
                case ButtonPress:
                    if (e.xany.window == quit) return 0;
                    printf("X:%dY:%d\n",e.xbutton.x,e.xbutton.y);
                    switch (e.xbutton.button){
                        case 1:
                            if(e.xbutton.x<300&&e.xbutton.y<300){
                            setgausian2d(wavefront2d,e.xbutton.y/3,e.xbutton.x/3);
                            }
                            break;
                        case 4:
                            scale+=0.1;
                            break;
                        case 5:
                            scale-=0.1;
                            break;
                        default:
                            break;
                    }
                    
                    break;
                case KeyPress : 
                    printf("keycode=%d \n", e.xkey.keycode);
                    switch (e.xkey.keycode){
                        case 25:
                            matrixMultiple(viewX_matrix,matrixplusX);
                            break;
                        case 38:
                            matrixMultiple(viewZ_matrix,matrixminusZ);
                            break;
                        case 39:
                            matrixMultiple(viewX_matrix,matrixminusX);
                            break;
                        case 40:
                            matrixMultiple(viewZ_matrix,matrixplusZ);
                            break;
                        case 27:
                            for(int i=0;i<100;i++){for (int k=0;k<100; k++){pMReset(&wavefront2d[i][k],2);for(int j=0;j<3;j++){viewzahyou[i][k][j];}}}
                            break;
                        case 10:
                            sinmode=0;
                            break;
                        case 11: 
                            sinmode=1;
                            break;
                        case 12: 
                            sinmode=2;
                            break;
                        default:
                            break;
                    }
                    break;
            }
        }
       
       matrixMultiple_dainyu(view_matrix,viewX_matrix,viewZ_matrix);
       matScaMultiple(view_matrix,scale);
        waveUpdate(wavefront2d);
        XSetForeground(dpy, gc, black);
        viewVectorsTrans(wavefront2d,viewzahyou,view_matrix);
        vecplot(viewzahyou,gc,dpy,buffer); 

        waveColourPlt(wavefront2d,gc,dpy,buffer);
        
        ++tmesin;
              
        
        if(sinmode==1)wavefront2d[50][50].posZ=2*sin(tmesin/50.0);
        if(sinmode==2){
            wavefront2d[30][50].posZ=2*sin(tmesin/50.0);
            wavefront2d[70][50].posZ=2*sin(tmesin/50.0);
        }
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
        
        lasttime=newtime;
        while(1){
            gettimeofday(&newtime,NULL);printf("%d\n",newtime.tv_usec-lasttime.tv_usec);
            if(!((newtime.tv_usec-lasttime.tv_usec)>500000)){break;}
            
        }
    }
}
