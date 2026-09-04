#ifndef DRAWING_H
#define DRAWING_H
#include <stdio.h>
#include <stdlib.h>
#include "genlib.h"
#include "letters.h"
#include "dtypes.h"

colorHSV3_t RGBtoHSV(color3_t* clr);
color3_t HSVtoRGB(colorHSV3_t* hsv);
color3_t* newColorBuffer(display_t* dis);
void freeColorBuffer(display_t* dis);
int toColorBufferIndex(display_t* dis, int x, int y);
void flushColorBuffer(display_t* dis, color3_t* clr);
void Point(display_t* dis, color3_t* clr, int x, int y);
void Point_Xbound(display_t* dis, color3_t* clr, int x, int y);
void Point_Ybound(display_t* dis, color3_t* clr, int x, int y);
void Point_Bound(display_t* dis, color3_t* clr, int x, int y);
void Vline_Color(display_t* dis, color3_t* clr, int x);
void Vline(display_t* dis, int x);
void Hline_Color(display_t* dis, color3_t* clr, int y);
void Hline(display_t* dis, int y);
void Vlines_Color(display_t* dis, color3_t* clr, int n);
void Vlines(display_t* dis, int n);
void Hlines_Color(display_t* dis, color3_t* clr, int n);
void Hlines(display_t* dis, int n);
void BufPutc_Color(display_t* dis, color3_t* clr, char c, int cx, int cy);
void BufPutc(display_t* dis, char c, int cx, int cy);
void BufStrPrint_Color(display_t* dis, color3_t* clr, char* str, int cx, int cy);
void BufStrPrint(display_t* dis, char* str, int cx, int cy);
void PlotXlines_Color(display_t* dis, color3_t* clr);
void PlotXlines(display_t* dis);
void PlotYlines_Color(display_t* dis, color3_t* clr);
void PlotYlines(display_t* dis);
void PlotXaxis_Color(display_t* dis, color3_t* clr);
void PlotXaxis(display_t* dis);
void PlotYaxis_Color(display_t* dis, color3_t* clr);
void PlotYaxis(display_t* dis);
void PlotViewBoxLines(display_t* dis);
void PlotFunc_Color(display_t* dis, color3_t* clr, func_t* fun);
void PlotFunc(display_t* dis, func_t* fun);
void RePlotFunc_Color(display_t* dis, color3_t* clr, func_t* fun);
void RePlotFunc(display_t* dis, func_t* fun);
void PlotIneq_Color(display_t* dis, color3_t* clr, func_t* fun, int type);
void PlotIneq(display_t* dis, func_t* fun, int type);
void RePlotIneq_Color(display_t* dis, color3_t* clr, func_t* fun, int type);
void RePlotIneq(display_t* dis, func_t* fun, int type);
int toSquareY(display_t* dis, int n);
int toSquareX(display_t* dis, int n);

#define INEQ_TYPE_LESS_THAN	0
#define INEQ_TYPE_GREATER_THAN	1
#define INEQ_TYPE_LESS_THAN_OR_EQU	2
#define INEQ_TYPE_GREATER_THAN_OR_EQU	3

#endif