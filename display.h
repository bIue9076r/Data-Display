#ifndef DISPLAY_H
#define DISPLAY_H
#include "drawing.h"

#define YES 1
#define NAY 0

int invalidDisplay(display_t* dis);
void fprintColor3(FILE* file, color3_t* c);
int ShowColorBuffer_Ppm(display_t* dis, char* path);
int ShowDataInfo(display_t* dis, char* path);
void setBorderColor(display_t* dis, color3_t* clr);
void setLineColor(display_t* dis, color3_t* clr);
void setAxisColor(display_t* dis, color3_t* clr);
void setCharColor(display_t* dis, color3_t* clr);
void setViewColor(display_t* dis, color3_t* clr);
void setBorder(display_t* dis, int b);
void setBorderLeft(display_t* dis, int b);
void setBorderRight(display_t* dis, int b);
void setBorderUp(display_t* dis, int b);
void setBorderDown(display_t* dis, int b);
void setDisplaySize(display_t* dis, int h, int w);
void setDisplayHeight(display_t* dis, int h);
void setDisplayWidth(display_t* dis, int w);
void setXstart(display_t* dis, float x);
void setYstart(display_t* dis, float y);
void setXend(display_t* dis, float x);
void setYend(display_t* dis, float y);
void setXrange(display_t* dis, float xs, float xe);
void setYrange(display_t* dis, float ys, float ye);
void setYpad(display_t* dis, float y);
void setXpad(display_t* dis, float x);
void setXlines(display_t* dis, int l);
void setYlines(display_t* dis, int l);
void setXlinesSy(display_t* dis, int l);
void setYlinesSx(display_t* dis, int l);
void setCharsize(display_t* dis, int s);
void setLineWidth(display_t* dis, int lw);
void setAxisLineWidth(display_t* dis, int lw);
void showXlines(display_t* dis, char b);
void showYlines(display_t* dis, char b);
void showLines(display_t* dis, char b);
void dashedLine(display_t* dis, char b);
void showXAxis(display_t* dis, char b);
void showYAxis(display_t* dis, char b);
void showAxis(display_t* dis, char b);
void newDisplay(display_t* dis, int h, int w);

#define DISPLAY_STB_IMAGE
#ifdef DISPLAY_STB_IMAGE
int ShowColorBuffer_Png(display_t* dis, char* path);
int ShowColorBuffer_Jpg(display_t* dis, char* path);
int ShowColorBuffer(display_t* dis, char* path);
#endif

#endif