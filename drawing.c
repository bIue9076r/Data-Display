#ifndef DRAWING_C
#define DRAWING_C
#include "drawing.h"

colorHSV3_t RGBtoHSV(color3_t* clr){
	float red = clr->red/255.0;
	float green = clr->green/255.0;
	float blue = clr->blue/255.0;

	float hue = 0;
	float cmax = 0;
	float cmin = 0;

	if(red < green){
		if(red < blue){
			cmin = red;
		}else{
			cmin = blue;
		}
	}else{
		if(green < blue){
			cmin = green;
		}else{
			cmin = blue;
		}
	}

	if(red > green){
		if(red > blue){
			cmax = red;
			hue = 60 * f_mod((green - blue)/(cmax - cmin),6);
		}else{
			cmax = blue;
			hue = 60 * (((red - green)/(cmax - cmin)) + 4);
		}
	}else{
		if(green > blue){
			cmax = green;
			hue = 60 * (((blue - red)/(cmax - cmin)) + 2);
		}else{
			cmax = blue;
			hue = 60 * (((red - green)/(cmax - cmin)) + 4);
		}
	}

	float sat = 0;
	if(f_abs(cmax) < 0.0001){
		sat = 0;
	}else{
		sat = (cmax - cmin)/cmax;
	}

	float v = cmax;

	while(hue >= 360){
		hue = hue - 360;
	}

	return (colorHSV3_t){hue,sat,v};
}

color3_t HSVtoRGB(colorHSV3_t* hsv){
	while(hsv->Hue >= 360){
		hsv->Hue = hsv->Hue - 360;
	}

	if(hsv->Sat > 1){
		hsv->Sat = 1;
	}

	if(hsv->Val > 1){
		hsv->Val = 1;
	}

	if(hsv->Sat < 0){
		hsv->Sat = 0;
	}

	if(hsv->Val < 0){
		hsv->Val = 0;
	}

	float c = hsv->Val * hsv->Sat;
	float x = c * (1 - f_abs(f_mod(hsv->Hue/60,1) - 1));
	float m = hsv->Val - c;

	float red = 0.0;
	float green = 0.0;
	float blue = 0.0;

	if(hsv->Hue >= 0.0 && hsv->Hue < 60.0){
		red = c;
		green = x;
		blue = 0.0;
	}
	if(hsv->Hue >= 60.0 && hsv->Hue < 120.0){
		red = x;
		green = c;
		blue = 0.0;
	}
	if(hsv->Hue >= 120.0 && hsv->Hue < 180.0){
		red = 0.0;
		green = c;
		blue = x;
	}
	if(hsv->Hue >= 180.0 && hsv->Hue < 240.0){
		red = 0.0;
		green = x;
		blue = c;
	}
	if(hsv->Hue >= 240.0 && hsv->Hue < 300.0){
		red = x;
		green = 0.0;
		blue = c;
	}
	if(hsv->Hue >= 300.0 && hsv->Hue < 360.0){
		red = c;
		green = 0.0;
		blue = x;
	}

	return (color3_t){255*(red+m),255*(green+m),255*(blue+m)};
}

color3_t* newColorBuffer(display_t* dis){
	return malloc(dis->viewbox.width * dis->viewbox.height * sizeof(color3_t));
}

void freeColorBuffer(display_t* dis){
	if(dis->colorBuffer != NULL){
		free(dis->colorBuffer);
	}
}

int toColorBufferIndex(display_t* dis, int x, int y){
	return x + (y * dis->viewbox.width);
}

void flushColorBuffer(display_t* dis, color3_t* clr){
	if(dis->colorBuffer != NULL){
		for(int y = 0; y < dis->viewbox.height; y++){
			for(int x = 0; x < dis->viewbox.width; x++){
				dis->colorBuffer[toColorBufferIndex(dis,x,y)] = *clr;
			}
		}
	}else{
		printf("Error: Null Color Buffer");
		return;
	}
}

void Point(display_t* dis, color3_t* clr, int x, int y){
	dis->colorBuffer[toColorBufferIndex(dis,x,y)] = *clr;
}

void Point_Xbound(display_t* dis, color3_t* clr, int x, int y){
	if(x >= 0 && x < dis->viewbox.width){
		Point(dis,clr,x,y);
	}
}

void Point_Ybound(display_t* dis, color3_t* clr, int x, int y){
	if(y >= 0 && y < dis->viewbox.height){
		Point(dis,clr,x,y);
	}
}

void Point_Bound(display_t* dis, color3_t* clr, int x, int y){
	if(y >= 0 && y < dis->viewbox.height){
		if(x >= 0 && x < dis->viewbox.width){
			Point(dis,clr,x,y);
		}
	}
}

void Vline_Color(display_t* dis, color3_t* clr, int x){
	for(int v = 0; v < dis->viewbox.height; v++){
		Point(dis,clr,x,v);
	}
}

void Vline(display_t* dis, int x){
	color3_t clr = (color3_t){150,150,150};
	Vline_Color(dis,&clr,x);
}

void Hline_Color(display_t* dis, color3_t* clr, int y){
	for(int v = 0; v < dis->viewbox.width; v++){
		Point(dis,clr,v,y);
	}
}

void Hline(display_t* dis, int y){
	color3_t clr = (color3_t){150,150,150};
	Hline_Color(dis,&clr,y);
}

void Vlines_Color(display_t* dis, color3_t* clr, int n){
	int inv = dis->viewbox.width / (n + 1);
	for(int i = 1; i < (n + 1); i++){
		for(int l = 0; l < dis->viewbox.axis_line_width; l++){
			int x = inv*i - (dis->viewbox.axis_line_width/2) + l;
			if(x >= 0 && x < dis->viewbox.width){
				Vline_Color(dis,clr,x);
			}
		}
	}
}

void Vlines(display_t* dis, int n){
	int inv = dis->viewbox.width / (n + 1);
	for(int i = 1; i < (n + 1); i++){
		Vline(dis,inv*i);
	}
}

void Hlines_Color(display_t* dis, color3_t* clr, int n){
	int inv = dis->viewbox.height / (n + 1);
	for(int i = 1; i < (n + 1); i++){
		for(int l = 0; l < dis->viewbox.axis_line_width; l++){
			int y = inv*i - (dis->viewbox.axis_line_width/2) + l;
			if(y >= 0 && y < dis->viewbox.height){
				Hline_Color(dis,clr,y);
			}
		}
	}
}

void Hlines(display_t* dis, int n){
	int inv = dis->viewbox.height / (n + 1);
	for(int i = 1; i < (n + 1); i++){
		Hline(dis,inv*i);
	}
}

void BufPutc_Color(display_t* dis, color3_t* clr, char c, int cx, int cy){
	char* C = getBitmap(c);
	for(int i = 0; i < dis->viewbox.charsize; i++){
		for(int j = 0; j < dis->viewbox.charsize; j++){
			for(int iy = 0; iy < 5; iy++){
				for(int jx = 0; jx < 5; jx++){
					if(C[jx + 5*iy]){
						int x = cx + j + jx*dis->viewbox.charsize;
						int y = cy + i + iy*dis->viewbox.charsize;

						if(y >= 0 && y < dis->viewbox.height){
							if(x >= 0 && x < dis->viewbox.width){
								Point(dis,clr,x,y);
							}
						}
					}
				}
			}
		}
	}
}

void BufPutc(display_t* dis, char c, int cx, int cy){
	color3_t clr = (color3_t){100,100,100};
	BufPutc_Color(dis,&clr,c,cx,cy);
}

void BufStrPrint_Color(display_t* dis, color3_t* clr, char* str, int cx, int cy){
	int sx = cx;
	while(*str != 0){
		if(*str == '\n'){
			cy = cy + 6*dis->viewbox.charsize;
			cx = sx;
			str++;
			continue;
		}

		BufPutc_Color(dis,clr,*str,cx,cy);
		str++;
		cx = cx + 5*dis->viewbox.charsize;
	}
}

void BufStrPrint(display_t* dis, char* str, int cx, int cy){
	color3_t clr = (color3_t){100,100,100};
	BufStrPrint_Color(dis,&clr,str,cx,cy);
}

void PlotXlines_Color(display_t* dis, color3_t* clr){
	char nums[255];
	for(int i = 0; i < dis->viewbox.x_lines; i++){
		float tx = lerp(i,0,dis->viewbox.x_lines,dis->viewbox.x_start,dis->viewbox.x_end);
		int x = lerp(tx,dis->viewbox.x_start,dis->viewbox.x_end,0,dis->viewbox.width);
		
		if(x >= 0 && x < dis->viewbox.width){
			for(int l = 0; l < dis->viewbox.axis_line_width; l++){
				int fx = x - (dis->viewbox.axis_line_width/2) + l;
				if(fx >= 0 && fx < dis->viewbox.width){
					Vline_Color(dis,clr,fx);
				}
			}
			if(dis->viewbox.show_x_figures){
				char* fmt = dis->viewbox.x_figure_fmt;
				if(fmt == NULL){fmt = "%.2f";}

				snprintf(nums,255,fmt,tx);
				BufStrPrint_Color(dis,&dis->char_color,nums,x,0);
			}
		}
	}
}

void PlotXlines(display_t* dis){
	color3_t clr = (color3_t){150,150,150};
	PlotXlines_Color(dis,&clr);
}

void PlotYlines_Color(display_t* dis, color3_t* clr){
	char nums[255];
	for(int i = 0; i < dis->viewbox.y_lines; i++){
		float ty = lerp(i,dis->viewbox.y_lines,0,dis->viewbox.y_end,dis->viewbox.y_start);
		int y = lerp(ty,dis->viewbox.y_end,dis->viewbox.y_start,dis->viewbox.height,0);
		
		if(y >= 0 && y < dis->viewbox.height){
			for(int l = 0; l < dis->viewbox.axis_line_width; l++){
				int fy = y - (dis->viewbox.axis_line_width/2) + l;
				if(fy >= 0 && fy < dis->viewbox.height){
					Hline_Color(dis,clr,fy);
				}
			}
			if(dis->viewbox.show_y_figures){
				char* fmt = dis->viewbox.y_figure_fmt;
				if(fmt == NULL){fmt = "%.2f";}

				snprintf(nums,255,fmt,ty);
				BufStrPrint_Color(dis,&dis->char_color,nums,0,y);
			}
		}
	}
}

void PlotYlines(display_t* dis){
	color3_t clr = (color3_t){150,150,150};
	PlotYlines_Color(dis,&clr);
}

void PlotXaxis_Color(display_t* dis, color3_t* clr){
	float xmax = dis->viewbox.x_start;
	float xmin = dis->viewbox.x_end;

	int tx = lerp(0,xmin,xmax,0,dis->viewbox.width);
	for(int l = 0; l < dis->viewbox.axis_line_width; l++){
		int fx = tx - (dis->viewbox.axis_line_width/2) + l;
		if(fx >= 0 && fx < dis->viewbox.width){
			Vline_Color(dis,clr,fx);
		}
	}
}

void PlotXaxis(display_t* dis){
	color3_t clr = (color3_t){0,0,0};
	PlotXaxis_Color(dis,&clr);
}

void PlotYaxis_Color(display_t* dis, color3_t* clr){
	float ymax = dis->viewbox.y_start;
	float ymin = dis->viewbox.y_end;

	int ty = lerp(0,ymin,ymax,dis->viewbox.height,0);
	for(int l = 0; l < dis->viewbox.axis_line_width; l++){
		int fy = ty - (dis->viewbox.axis_line_width/2) + l;
		if(fy >= 0 && fy < dis->viewbox.width){
			Hline_Color(dis,clr,fy);
		}
	}
}

void PlotYaxis(display_t* dis){
	color3_t clr = (color3_t){0,0,0};
	PlotYaxis_Color(dis,&clr);
}

void PlotViewBoxLines(display_t* dis){
	if(dis->viewbox.show_x_lines){
		PlotXlines_Color(dis,&dis->line_color);
	}

	if(dis->viewbox.show_y_lines){
		PlotYlines_Color(dis,&dis->line_color);
	}

	if(dis->viewbox.show_x_axis){
		PlotXaxis_Color(dis,&dis->axis_color);
	}

	if(dis->viewbox.show_y_axis){
		PlotYaxis_Color(dis,&dis->axis_color);
	}
}

void PlotFunc_Color(display_t* dis, color3_t* clr, func* fun){
	flushColorBuffer(dis,&dis->view_color);
	float ymax = fun(dis->viewbox.x_start);
	float ymin = fun(dis->viewbox.x_start);
	float ypad = dis->viewbox.y_pad;
	float* ys = malloc(sizeof(float) * dis->viewbox.width);
	for(int i = 0; i < dis->viewbox.width; i++){
		float x = lerp(i,0,dis->viewbox.width,dis->viewbox.x_start,dis->viewbox.x_end);
		ys[i] = fun(x);
		if(ys[i] > ymax){ymax = ys[i];}
		if(ys[i] < ymin){ymin = ys[i];}
	}
	dis->viewbox.y_start = ymax + ypad;
	dis->viewbox.y_end = ymin - ypad;

	PlotViewBoxLines(dis);

	for(int i = 0; i < dis->viewbox.width; i++){
		int ty = (int)lerp(ys[i],ymin - ypad, ymax + ypad, dis->viewbox.height, 0);
		for(int lx = 0; lx < dis->viewbox.line_width; lx++){
			for(int ly = 0; ly < dis->viewbox.line_width; ly++){
				int fx = i  - (dis->viewbox.line_width/2) + lx;
				int fy = ty - (dis->viewbox.line_width/2) + ly;
				if(dis->viewbox.dashed_line){
					if(i/(4 * i_max(1,dis->viewbox.line_width)) % 2 != 0){
						continue;
					}
				}

				Point_Bound(dis,clr,fx,fy);
			}
		}
	}
	free(ys);
}

void PlotFunc(display_t* dis, func* fun){
	color3_t clr = (color3_t){0,0,0};
	PlotFunc_Color(dis,&clr,fun);
}

void RePlotFunc_Color(display_t* dis, color3_t* clr, func* fun){
	float ymax = dis->viewbox.y_start;
	float ymin = dis->viewbox.y_end;

	float* ys = malloc(sizeof(float) * dis->viewbox.width);
	for(int i = 0; i < dis->viewbox.width; i++){
		float x = lerp(i,0,dis->viewbox.width,dis->viewbox.x_start,dis->viewbox.x_end);
		ys[i] = fun(x);
	}

	for(int i = 0; i < dis->viewbox.width; i++){
		int ty = (int)lerp(ys[i], ymin, ymax, dis->viewbox.height, 0);
		for(int lx = 0; lx < dis->viewbox.line_width; lx++){
			for(int ly = 0; ly < dis->viewbox.line_width; ly++){
				int fx = i  - (dis->viewbox.line_width/2) + lx;
				int fy = ty - (dis->viewbox.line_width/2) + ly;
				if(dis->viewbox.dashed_line){
					if(i/(4 * i_max(1,dis->viewbox.line_width)) % 2 != 0){
						continue;
					}
				}
				
				Point_Bound(dis,clr,fx,fy);
			}
		}
	}
	free(ys);
}

void RePlotFunc(display_t* dis, func* fun){
	color3_t clr = (color3_t){0,0,0};
	RePlotFunc_Color(dis,&clr,fun);
}

void PlotIneq_Color(display_t* dis, color3_t* clr, func* fun, int type){
	flushColorBuffer(dis,&dis->view_color);
	float ymax = fun(dis->viewbox.x_start);
	float ymin = fun(dis->viewbox.x_start);
	float ypad = dis->viewbox.y_pad;
	float* ys = malloc(sizeof(float) * dis->viewbox.width);
	for(int i = 0; i < dis->viewbox.width; i++){
		float x = lerp(i,0,dis->viewbox.width,dis->viewbox.x_start,dis->viewbox.x_end);
		ys[i] = fun(x);
		if(ys[i] > ymax){ymax = ys[i];}
		if(ys[i] < ymin){ymin = ys[i];}
	}
	dis->viewbox.y_start = ymax + ypad;
	dis->viewbox.y_end = ymin - ypad;

	PlotViewBoxLines(dis);

	colorHSV3_t hs = RGBtoHSV(clr);
	hs.Hue = hs.Hue + 30;
	color3_t shifted = HSVtoRGB(&hs);

	for(int i = 0; i < dis->viewbox.width; i++){
		for(int y = 0; y < dis->viewbox.height; y++){
			float iy = lerp(y,dis->viewbox.height,0,ymin - ypad, ymax + ypad);
			switch(type){
				case INEQ_TYPE_LESS_THAN:
				case INEQ_TYPE_LESS_THAN_OR_EQU:
					if(iy < ys[i]){
						Point(dis,&shifted,i,y);
					}
				break;

				case INEQ_TYPE_GREATER_THAN:
				case INEQ_TYPE_GREATER_THAN_OR_EQU:
					if(iy > ys[i]){
						Point(dis,&shifted,i,y);
					}
				break;
			}
		}

		int ty = (int)lerp(ys[i],ymin - ypad, ymax + ypad, dis->viewbox.height, 0);
		if(ty >= 0 && ty < dis->viewbox.height){
			if(type == INEQ_TYPE_LESS_THAN || type == INEQ_TYPE_GREATER_THAN){
				if(i/(4 * i_max(1,dis->viewbox.line_width)) % 2 != 0){
					continue;
				}
			}
			
			for(int lx = 0; lx < dis->viewbox.line_width; lx++){
				for(int ly = 0; ly < dis->viewbox.line_width; ly++){
					int fx = i  - (dis->viewbox.line_width/2) + lx;
					int fy = ty - (dis->viewbox.line_width/2) + ly;

					Point_Bound(dis,clr,fx,fy);
				}
			}
		}
	}
	free(ys);
}

void PlotIneq(display_t* dis, func* fun, int type){
	color3_t clr = (color3_t){0,0,0};
	PlotIneq_Color(dis,&clr,fun,type);
}

void RePlotIneq_Color(display_t* dis, color3_t* clr, func* fun, int type){
	float ymax = dis->viewbox.y_start;
	float ymin = dis->viewbox.y_end;
	
	float* ys = malloc(sizeof(float) * dis->viewbox.width);
	for(int i = 0; i < dis->viewbox.width; i++){
		float x = lerp(i,0,dis->viewbox.width,dis->viewbox.x_start,dis->viewbox.x_end);
		ys[i] = fun(x);
	}

	colorHSV3_t hs = RGBtoHSV(clr);
	hs.Hue = hs.Hue + 30;
	color3_t shifted = HSVtoRGB(&hs);

	for(int i = 0; i < dis->viewbox.width; i++){
		for(int y = 0; y < dis->viewbox.height; y++){
			float iy = lerp(y,dis->viewbox.height,0,ymin, ymax);
			switch(type){
				case INEQ_TYPE_LESS_THAN:
				case INEQ_TYPE_LESS_THAN_OR_EQU:
					if(iy < ys[i]){
						Point(dis,&shifted,i,y);
					}
				break;

				case INEQ_TYPE_GREATER_THAN:
				case INEQ_TYPE_GREATER_THAN_OR_EQU:
					if(iy > ys[i]){
						Point(dis,&shifted,i,y);
					}
				break;
			}
		}

		int ty = (int)lerp(ys[i],ymin, ymax, dis->viewbox.height, 0);
		if(ty >= 0 && ty < dis->viewbox.height){
			if(type == INEQ_TYPE_LESS_THAN || type == INEQ_TYPE_GREATER_THAN){
				if(i/(4 * i_max(1,dis->viewbox.line_width)) % 2 != 0){
					continue;
				}
			}
			
			for(int lx = 0; lx < dis->viewbox.line_width; lx++){
				for(int ly = 0; ly < dis->viewbox.line_width; ly++){
					int fx = i  - (dis->viewbox.line_width/2) + lx;
					int fy = ty - (dis->viewbox.line_width/2) + ly;

					Point_Bound(dis,clr,fx,fy);
				}
			}
		}
	}
	free(ys);
}

void RePlotIneq(display_t* dis, func* fun, int type){
	color3_t clr = (color3_t){0,0,0};
	RePlotIneq_Color(dis,&clr,fun,type);
}

int toSquareY(display_t* dis, int n){
	return (dis->viewbox.height * n)/(dis->viewbox.width);
}

int toSquareX(display_t* dis, int n){
	return (dis->viewbox.width * n)/(dis->viewbox.height);
}

#endif