#ifndef DISPLAY_C
#define DISPLAY_C
#include "display.h"

#ifdef DISPLAY_STB_IMAGE
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#endif

int invalidDisplay(display_t* dis){
	return (dis->colorBuffer == NULL);
}

void fprintColor3(FILE* file, color3_t* c){
	fprintf(file,"%d %d %d\n",c->red,c->green,c->blue);
}

void printColor3(color3_t* c){
	printf("%d %d %d\n",c->red,c->green,c->blue);
}

void printColorHSV3(colorHSV3_t* c){
	printf("%f %f %f\n",c->Hue,c->Sat,c->Val);
}

int ShowColorBuffer_Ppm(display_t* dis, char* path){
	if(invalidDisplay(dis)){
		printf("Error: Invalid display");
		return 1;
	}
	
	FILE* file = fopen(path,"w");
	if(file == NULL){
		printf("Error: Unable to open file");
		return 1;
	}

	int WX = dis->borders.left + dis->viewbox.width + dis->borders.right;
	int HY = dis->borders.up + dis->viewbox.height + dis->borders.down;

	fprintf(file,"P3\n%d %d\n255\n",WX,HY);

	for(int y = 0; y < HY; y++){
		for(int x = 0; x < WX; x++){
			if(y < dis->borders.up){
				// Up Border
				fprintColor3(file,&dis->border_color);
			}else{
				if(y < (dis->borders.up + dis->viewbox.height)){
					if(x < dis->borders.left){
						// Left Border
						fprintColor3(file,&dis->border_color);
					}else{
						if(x < (dis->borders.left + dis->viewbox.width)){
							// Viewbox
							fprintColor3(file,&dis->colorBuffer[toColorBufferIndex(dis,(x - dis->borders.left),(y - dis->borders.up))]);
						}else{
							// Right Border
							fprintColor3(file,&dis->border_color);
						}
					}
				}else{
					// Down Border
					fprintColor3(file,&dis->border_color);
				}
			}
		}
	}

	fclose(file);
	return 0;
}

int ShowDataInfo(display_t* dis, char* path){
	FILE* file = fopen(path,"w");
	if(file == NULL){
		printf("Error: Unable to open file");
		return 1;
	}

	fprintf(file,"Display Info\n");
	fprintf(file,"Borders:\n\tLeft: %d\n\tRight: %d\n\tUp: %d\n\tDown: %d\n\t",dis->borders.left,dis->borders.right,dis->borders.up,dis->borders.down);
	fprintf(file,"Color: "); fprintColor3(file,&dis->border_color);
	fprintf(file,"Viewbox:\n\tWidth: %d\n\tHeight: %d\n\t",dis->viewbox.width,dis->viewbox.height);
	fprintf(file,"X range: (%.5f, %.5f)\n\tY range: (%.5f, %.5f)\n\t",dis->viewbox.x_start,dis->viewbox.x_end,dis->viewbox.y_end,dis->viewbox.y_start);
	fprintf(file,"Y padding: %.5f\t\n\t",dis->viewbox.y_pad);
	fprintf(file,"X padding: %.5f\t\n",dis->viewbox.x_pad);
	fprintf(file,"Lines:\n\t\tX: %s\n\t\tY: %s\n",(dis->viewbox.show_x_lines)?("YES"):("NAY"),(dis->viewbox.show_y_lines)?("YES"):("NAY"));
	fprintf(file,"\t\tLine Color: "); fprintColor3(file,&dis->line_color);
	fprintf(file,"\t\tLine Width: %d\n",dis->viewbox.line_width);
	if(dis->viewbox.show_x_lines){
		fprintf(file,"\t\tX lines: %d\n",dis->viewbox.x_lines);
	}
	if(dis->viewbox.show_y_lines){
		fprintf(file,"\t\tY lines: %d\n",dis->viewbox.y_lines);
	}
	fprintf(file,"Axis:\n\t\tX: %s\n\t\tY: %s\n",(dis->viewbox.show_x_axis)?("YES"):("NAY"),(dis->viewbox.show_y_axis)?("YES"):("NAY"));
	fprintf(file,"\t\tAxis Color: "); fprintColor3(file,&dis->axis_color);
	fprintf(file,"\t\tAxis Line Width: %d\n",dis->viewbox.axis_line_width);
	fprintf(file,"Dashed Lines: %s\n",(dis->viewbox.dashed_line)?("YES"):("NAY"));
	fprintf(file,"Char Color: "); fprintColor3(file,&dis->char_color);

	return 0;
}

void PrintDataInfo(display_t* dis){
	printf("Display Info\n");
	printf("Borders:\n\tLeft: %d\n\tRight: %d\n\tUp: %d\n\tDown: %d\n\t",dis->borders.left,dis->borders.right,dis->borders.up,dis->borders.down);
	printf("Color: "); printColor3(&dis->border_color);
	printf("Viewbox:\n\tWidth: %d\n\tHeight: %d\n\t",dis->viewbox.width,dis->viewbox.height);
	printf("X range: (%.5f, %.5f)\n\tY range: (%.5f, %.5f)\n\t",dis->viewbox.x_start,dis->viewbox.x_end,dis->viewbox.y_end,dis->viewbox.y_start);
	printf("Y padding: %.5f\t\n\t",dis->viewbox.y_pad);
	printf("X padding: %.5f\t\n",dis->viewbox.x_pad);
	printf("Lines:\n\t\tX: %s\n\t\tY: %s\n",(dis->viewbox.show_x_lines)?("YES"):("NAY"),(dis->viewbox.show_y_lines)?("YES"):("NAY"));
	printf("\t\tLine Color: "); printColor3(&dis->line_color);
	printf("\t\tLine Width: %d\n",dis->viewbox.line_width);
	if(dis->viewbox.show_x_lines){
		printf("\t\tX lines: %d\n",dis->viewbox.x_lines);
	}
	if(dis->viewbox.show_y_lines){
		printf("\t\tY lines: %d\n",dis->viewbox.y_lines);
	}
	printf("Axis:\n\t\tX: %s\n\t\tY: %s\n",(dis->viewbox.show_x_axis)?("YES"):("NAY"),(dis->viewbox.show_y_axis)?("YES"):("NAY"));
	printf("\t\tAxis Color: "); printColor3(&dis->axis_color);
	printf("\t\tAxis Line Width: %d\n",dis->viewbox.axis_line_width);
	printf("Dashed Lines: %s\n",(dis->viewbox.dashed_line)?("YES"):("NAY"));
	printf("Char Color: "); printColor3(&dis->char_color);
}

void setBorderColor(display_t* dis, color3_t* clr){
	dis->border_color = *clr;
}

void setLineColor(display_t* dis, color3_t* clr){
	dis->line_color = *clr;
}

void setAxisColor(display_t* dis, color3_t* clr){
	dis->axis_color = *clr;
}

void setCharColor(display_t* dis, color3_t* clr){
	dis->char_color = *clr;
}

void setViewColor(display_t* dis, color3_t* clr){
	dis->view_color = *clr;
}

void setBorder(display_t* dis, int b){
	dis->borders = (border_t){b,b,b,b};
}

void setBorderLeft(display_t* dis, int b){
	dis->borders.left = b;
}

void setBorderRight(display_t* dis, int b){
	dis->borders.right = b;
}

void setBorderUp(display_t* dis, int b){
	dis->borders.up = b;
}

void setBorderDown(display_t* dis, int b){
	dis->borders.down = b;
}

void setDisplaySize(display_t* dis, int h, int w){
	dis->viewbox.width = w;
	dis->viewbox.height = h;
	freeColorBuffer(dis);
	dis->colorBuffer = newColorBuffer(dis);
}

void setDisplayHeight(display_t* dis, int h){
	setDisplaySize(dis,h,dis->viewbox.width);
}

void setDisplayWidth(display_t* dis, int w){
	setDisplaySize(dis,dis->viewbox.height,w);
}

void setXstart(display_t* dis, float x){
	dis->viewbox.x_start = x;
}

void setYstart(display_t* dis, float y){
	dis->viewbox.y_start = y;
}

void setXend(display_t* dis, float x){
	dis->viewbox.x_end = x;
}

void setYend(display_t* dis, float y){
	dis->viewbox.y_end = y;
}

void setXrange(display_t* dis, float xs, float xe){
	setXstart(dis,xs);
	setXend(dis,xe);
}

void setYrange(display_t* dis, float ys, float ye){
	setYstart(dis,ys);
	setYend(dis,ye);
}

void setYpad(display_t* dis, float y){
	dis->viewbox.y_pad = y;
}

void setXpad(display_t* dis, float x){
	dis->viewbox.x_pad = x;
}

void setXlines(display_t* dis, int l){
	dis->viewbox.x_lines = l;
}

void setYlines(display_t* dis, int l){
	dis->viewbox.y_lines = l;
}

void setXlinesSy(display_t* dis, int l){
	dis->viewbox.x_lines = l;
	dis->viewbox.y_lines = toSquareY(dis,l);
}

void setYlinesSx(display_t* dis, int l){
	dis->viewbox.y_lines = l;
	dis->viewbox.x_lines = toSquareX(dis,l);
}

void setCharsize(display_t* dis, int s){
	dis->viewbox.charsize = s;
}

void setLineWidth(display_t* dis, int lw){
	dis->viewbox.line_width = lw;
}

void setAxisLineWidth(display_t* dis, int lw){
	dis->viewbox.axis_line_width = lw;
}

void setXFigureFormat(display_t* dis, char* f){
	dis->viewbox.x_figure_fmt = (f != NULL)?(f):("%.2f");
}

void setYFigureFormat(display_t* dis, char* f){
	dis->viewbox.y_figure_fmt = (f != NULL)?(f):("%.2f");
}

void setFigureFormat(display_t* dis, char* f){
	setXFigureFormat(dis,f);
	setYFigureFormat(dis,f);
}

void showXlines(display_t* dis, char b){
	dis->viewbox.show_x_lines = b;
}

void showYlines(display_t* dis, char b){
	dis->viewbox.show_y_lines = b;
}

void showLines(display_t* dis, char b){
	showXlines(dis,b);
	showYlines(dis,b);
}

void dashedLine(display_t* dis, char b){
	dis->viewbox.dashed_line = b;
}

void showXAxis(display_t* dis, char b){
	dis->viewbox.show_x_axis = b;
}

void showYAxis(display_t* dis, char b){
	dis->viewbox.show_y_axis = b;
}

void showAxis(display_t* dis, char b){
	showXAxis(dis,b);
	showYAxis(dis,b);
}

void showXFigures(display_t* dis, char b){
	dis->viewbox.show_x_figures = b;
}

void showYFigures(display_t* dis, char b){
	dis->viewbox.show_y_figures = b;
}

void showFigures(display_t* dis, char b){
	showXFigures(dis,b);
	showYFigures(dis,b);
}

void newDisplay(display_t* dis, int h, int w){
	setBorderColor(dis,&(color3_t){0,0,0});
	setLineColor(dis,&(color3_t){150,150,150});
	setAxisColor(dis,&(color3_t){0,0,0});
	setCharColor(dis,&(color3_t){100,100,100});
	setViewColor(dis,&(color3_t){255,255,255});
	setBorder(dis,20);
	setDisplaySize(dis,h,w);
	setXrange(dis,-10,10);
	setYrange(dis,5,-5);
	setYpad(dis,0.1);
	setXpad(dis,0);
	setXlinesSy(dis,10);
	setCharsize(dis,2);
	setLineWidth(dis,1);
	setAxisLineWidth(dis,1);
	setFigureFormat(dis,NULL);
	showLines(dis,YES);
	dashedLine(dis,NAY);
	showAxis(dis,NAY);
	showYFigures(dis,YES);
	showXFigures(dis,NAY);
	flushColorBuffer(dis,&dis->view_color);
}


#ifdef DISPLAY_STB_IMAGE

int ShowColorBuffer_Png(display_t* dis, char* path){
	if(invalidDisplay(dis)){
		printf("Error: Invalid display");
		return 1;
	}

	int WX = dis->borders.left + dis->viewbox.width + dis->borders.right;
	int HY = dis->borders.up + dis->viewbox.height + dis->borders.down;
	color3_t data[WX * HY];

	for(int y = 0; y < HY; y++){
		for(int x = 0; x < WX; x++){
			if(y < dis->borders.up){
				// Up Border
				data[x + (y * WX)] = dis->border_color;
			}else{
				if(y < (dis->borders.up + dis->viewbox.height)){
					if(x < dis->borders.left){
						// Left Border
						data[x + (y * WX)] = dis->border_color;
					}else{
						if(x < (dis->borders.left + dis->viewbox.width)){
							// Viewbox
							data[x + (y * WX)] = dis->colorBuffer[toColorBufferIndex(dis,(x - dis->borders.left),(y - dis->borders.up))];
						}else{
							// Right Border
							data[x + (y * WX)] = dis->border_color;
						}
					}
				}else{
					// Down Border
					data[x + (y * WX)] = dis->border_color;
				}
			}
		}
	}

	stbi_write_png(path,WX,HY,3,&data,WX * sizeof(color3_t));
	return 0;
}

int ShowColorBuffer_Jpg(display_t* dis, char* path){
	if(invalidDisplay(dis)){
		printf("Error: Invalid display");
		return 1;
	}

	int WX = dis->borders.left + dis->viewbox.width + dis->borders.right;
	int HY = dis->borders.up + dis->viewbox.height + dis->borders.down;
	color3_t data[WX * HY];

	for(int y = 0; y < HY; y++){
		for(int x = 0; x < WX; x++){
			if(y < dis->borders.up){
				// Up Border
				data[x + (y * WX)] = dis->border_color;
			}else{
				if(y < (dis->borders.up + dis->viewbox.height)){
					if(x < dis->borders.left){
						// Left Border
						data[x + (y * WX)] = dis->border_color;
					}else{
						if(x < (dis->borders.left + dis->viewbox.width)){
							// Viewbox
							data[x + (y * WX)] = dis->colorBuffer[toColorBufferIndex(dis,(x - dis->borders.left),(y - dis->borders.up))];
						}else{
							// Right Border
							data[x + (y * WX)] = dis->border_color;
						}
					}
				}else{
					// Down Border
					data[x + (y * WX)] = dis->border_color;
				}
			}
		}
	}

	stbi_write_jpg(path,WX,HY,3,&data,WX * sizeof(color3_t));
	return 0;
}

int ShowColorBuffer(display_t* dis, char* path){
	return ShowColorBuffer_Png(dis,path);
}

#endif

#endif