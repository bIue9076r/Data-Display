#include <stdio.h>
#include <stdlib.h>

#include "genlib.c"
#include "letters.c"
#include "drawing.c"
#include "data.c"
#include "display.c"

// 2(x^2) - x - 2
float f(float x){
	return 2*x*x - x - 2;
}

// f(2x) = 2(2x)^2 - 2x - 2
float g(float x){
	return f(2*x);
}

int main(int argc, char** argv){
	display_t di;
	newDisplay(&di,400,600);
	// showAxis(&di,YES);
	setXrange(&di,-0.06,0.06);
	setYrange(&di,0.06,-0.06);
	setLineWidth(&di,5);
	// setXpad(&di,0.1);
	showYFigures(&di,NAY);
	

	data_list_t xlist;
	data_list_t ylist;
	xlist.lenght = 10;
	ylist.lenght = 10;
	data_t xl[10];
	data_t yl[10];
	for(int i = 0; i < 10; i++){
		xl[i].type = DP_TYPE_FRA;
		xl[i].data.frac = i;//lerp(i,0,9,-0.05,0.05);
		yl[i].type = DP_TYPE_FRA;
		yl[i].data.frac = g(i);//lerp(i,0,9,-0.05,0.05);
	}
	xlist.list = xl;
	ylist.list = yl;

	PlotXYList(&di,&xlist,&ylist);

	// PlotXList_Color(&di,&(color3_t){255,0,0},&xlist);
	// RePlotYList(&di,&ylist);

	color3_t clr = (color3_t){255,100,0};
	// RePlotIneq_Color(&di, &clr, f, INEQ_TYPE_GREATER_THAN);
	setLineWidth(&di,1);
	RePlotFunc_Color(&di, &(color3_t){0,0,255}, g);
	
	ShowColorBuffer_Ppm(&di,"Out.ppm");
	ShowColorBuffer_Png(&di,"Output.png");
	ShowDataInfo(&di,"OutDat.txt");
	freeColorBuffer(&di);
	return 0;
}