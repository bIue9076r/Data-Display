#ifndef COMMANDS_C
#define COMMANDS_C
#include "commands.h"

// Commands
// v / version
// h / help
// exit
// plot

void showTrail(str_t* trail){
	if(trail->len > 0){
		printf("Warning: Trailing parameters\n");
		printf("-> ");
		str_tprintln(trail);
	}
}

void commandHelp(int i){
	switch(i){
		default:
		case 0:
			printf("Commands\n",i);
			printf("%-20s|%30s\n","h / help","Help");
			printf("%-20s|%30s\n","v / version","Version");
			printf("%-20s|%30s\n","exit","Exit");
		break;

		case 1:
			printf("Commands page %d - Display\n",i);
			printf("%-20s|%30s\n","plot","Plot");
			printf("%-20s|%30s\n","show","Show");
			printf("%-20s|%30s\n","height","Height");
			printf("%-20s|%30s\n","width","Width");
			printf("%-20s|%30s\n","border","Border");
			printf("%-20s|%30s\n","border-left","Border Left");
			printf("%-20s|%30s\n","border-right","Border Right");
			printf("%-20s|%30s\n","border-up","Border Up");
			printf("%-20s|%30s\n","border-down","Border Down");
			printf("%-20s|%30s\n","border-color","Border Color");
			printf("%-20s|%30s\n","line-color","Line Color");
			printf("%-20s|%30s\n","axis-color","Axis Color");
			printf("%-20s|%30s\n","char-color","Char Color");
			printf("%-20s|%30s\n","view-color","View Color");
			printf("%-20s|%30s\n","x-start","X Start");
			printf("%-20s|%30s\n","y-start","Y Start");
			printf("%-20s|%30s\n","x-end","X End");
			printf("%-20s|%30s\n","y-end","Y End");
			printf("%-20s|%30s\n","x-range","X Range");
			printf("%-20s|%30s\n","y-range","Y Range");
			printf("%-20s|%30s\n","x-padding","X Padding");
			printf("%-20s|%30s\n","y-padding","Y Padding");
			printf("%-20s|%30s\n","x-lines","X Lines");
			printf("%-20s|%30s\n","y-lines","Y Lines");
			printf("%-20s|%30s\n","x-lines-sy","X Lines Square y");
			printf("%-20s|%30s\n","y-lines-sx","Y Lines Square x");
			printf("%-20s|%30s\n","char-size","Char Size");
			printf("%-20s|%30s\n","line-width","Line Width");
			printf("%-20s|%30s\n","axis-line-width","Axis Line Width");
			printf("%-20s|%30s\n","x-figure-format","X Figure Format");
			printf("%-20s|%30s\n","y-figure-format","Y Figure Format");
			printf("%-20s|%30s\n","figure-format","Figure Format");
			printf("%-20s|%30s\n","show-x-lines","Show X Lines");
			printf("%-20s|%30s\n","show-y-lines","Show Y Lines");
			printf("%-20s|%30s\n","show-lines","Show Lines");
			printf("%-20s|%30s\n","dashed-line","Dashed Line");
			printf("%-20s|%30s\n","show-x-axis","Show X Axis");
			printf("%-20s|%30s\n","show-y-axis","Show Y Axis");
			printf("%-20s|%30s\n","show-axis","Show Axis");
			printf("%-20s|%30s\n","show-x-figures","Show X Figures");
			printf("%-20s|%30s\n","show-y-figures","Show Y Figures");
			printf("%-20s|%30s\n","show-figures","Show Figures");
		break;

		case 2:
			printf("Commands page %d - Ploting\n",i);
			printf("%-20s|%30s\n","hsv"," RGB to HSV");
			printf("%-20s|%30s\n","rgb"," HSV to RGB");
			printf("%-20s|%30s\n","flush","Flush Color Buffer");
			printf("%-20s|%30s\n","point","Plot Point");
			printf("%-20s|%30s\n","vline","Plot Vertical Line");
			printf("%-20s|%30s\n","hline","Plot Horizontal Line");
			printf("%-20s|%30s\n","vlines","Plot Vertical Lines");
			printf("%-20s|%30s\n","hlines","Plot Horizontal Lines");
			printf("%-20s|%30s\n","putc","Put Char");
			printf("%-20s|%30s\n","print","Print String");
			printf("%-20s|%30s\n","plot-xlines","Plot X Lines");
			printf("%-20s|%30s\n","plot-ylines","Plot Y Lines");
			printf("%-20s|%30s\n","plot-xaxis","Plot X Axis");
			printf("%-20s|%30s\n","plot-yaxis","Plot Y Axis");
			printf("%-20s|%30s\n","plot-lines","Plot Viewbox Lines");
			printf("%-20s|%30s\n","funct","Plot Function");
			printf("%-20s|%30s\n","refunct","Replot Function");
			printf("%-20s|%30s\n","inequ","Plot Inequality");
			printf("%-20s|%30s\n","reinequ","Replot Inequality");
		break;

		case 3:
			printf("Commands page %d - Data\n",i);
		break;
	}
}

void cmd_help(str_t* command, str_t* params){
	if(params->len > 0){
		commandHelp(str_ttoi(params));
	}else{
		commandHelp(0);
	}
}

void cmd_exit(str_t* command, str_t* params){
	gRunning = 0;
}

// Display Commands
void cmd_plot(str_t* command, str_t* params){
	if(params->len > 0){
		str_t trail = {.len = 0, .str = NULL};
		str_tsplit(params,&trail);

		char str[params->len + 1];
		for(int i = 0; i < params->len; i++){
			str[i] = params->str[i];
		}
		str[params->len] = 0;
		
		ShowColorBuffer(&gDisplay,str);

		printf("Plotted display to \"");
		str_tprint(params);
		printf("\"\n");

		if(trail.len > 0){
			printf("Warning: Trailing parameters\n");
			printf("-> ");
			str_tprintln(&trail);
		}
	}else{
		printf("Missing parameters for plot\n");
	}
}

void cmd_show(str_t* command, str_t* params){
	if(params->len > 0){
		str_t trail = {.len = 0, .str = NULL};
		str_tsplit(params,&trail);

		char str[params->len + 1];
		for(int i = 0; i < params->len; i++){
			str[i] = params->str[i];
		}
		str[params->len] = 0;
		
		ShowDataInfo(&gDisplay,str);

		printf("Logged info to \"");
		str_tprint(params);
		printf("\"\n");

		showTrail(&trail);
	}else{
		PrintDataInfo(&gDisplay);
	}
}

void cmd_height(str_t* command, str_t* params){
	if(params->len > 0){
		str_t trail = {.len = 0, .str = NULL};
		str_tsplit(params,&trail);

		gHeight = str_ttoi(params);
		if(gHeight <= 0){ gHeight = 400; }
		setDisplaySize(&gDisplay,gHeight,gWitdh);
		printf("Height: %d\n",gHeight);

		showTrail(&trail);
	}else{
		printf("Error: No Height given\n");
	}
}

void cmd_width(str_t* command, str_t* params){
	if(params->len > 0){
		str_t trail = {.len = 0, .str = NULL};
		str_tsplit(params,&trail);

		gWitdh = str_ttoi(params);
		if(gWitdh <= 0){ gWitdh = 600; }
		setDisplaySize(&gDisplay,gHeight,gWitdh);
		printf("Witdh: %d\n",gWitdh);

		showTrail(&trail);
	}else{
		printf("Error: No Width given\n");
	}
}

void cmd_border(str_t* command, str_t* params){
	if(params->len > 0){
		str_t trail = {.len = 0, .str = NULL};
		str_tsplit(params,&trail);

		int border = str_ttoi(params);
		if(border < 0){ border = 0; }
		setBorder(&gDisplay,border);
		printf("Border: %d\n",border);

		showTrail(&trail);
	}else{
		printf("Error: No Border given\n");
	}
}

void cmd_border_left(str_t* command, str_t* params){
	if(params->len > 0){
		str_t trail = {.len = 0, .str = NULL};
		str_tsplit(params,&trail);

		int border = str_ttoi(params);
		if(border < 0){ border = 0; }
		setBorderLeft(&gDisplay,border);
		printf("Left Border: %d\n",border);

		showTrail(&trail);
	}else{
		printf("Error: No Left Border given\n");
	}
}

void cmd_border_right(str_t* command, str_t* params){
	if(params->len > 0){
		str_t trail = {.len = 0, .str = NULL};
		str_tsplit(params,&trail);

		int border = str_ttoi(params);
		if(border < 0){ border = 0; }
		setBorderRight(&gDisplay,border);
		printf("Right Border: %d\n",border);

		showTrail(&trail);
	}else{
		printf("Error: No Right Border given\n");
	}
}

void cmd_border_up(str_t* command, str_t* params){
	if(params->len > 0){
		str_t trail = {.len = 0, .str = NULL};
		str_tsplit(params,&trail);

		int border = str_ttoi(params);
		if(border < 0){ border = 0; }
		setBorderUp(&gDisplay,border);
		printf("Up Border: %d\n",border);

		showTrail(&trail);
	}else{
		printf("Error: No Up Border given\n");
	}
}

void cmd_border_down(str_t* command, str_t* params){
	if(params->len > 0){
		str_t trail = {.len = 0, .str = NULL};
		str_tsplit(params,&trail);

		int border = str_ttoi(params);
		if(border < 0){ border = 0; }
		setBorderDown(&gDisplay,border);
		printf("Down Border: %d\n",border);

		showTrail(&trail);
	}else{
		printf("Error: No Down Border given\n");
	}
}

void cmd_border_color(str_t* command, str_t* params){
	if(params->len > 0){
		str_t params2 = {.len = 0, .str = NULL};
		str_tsplit(params,&params2);

		str_t params3 = {.len = 0, .str = NULL};
		str_tsplit(&params2,&params3);

		if(params3.len > 0){
			str_t trail = {.len = 0, .str = NULL};
			str_tsplit(&params3,&trail);

			int cr = str_ttoi(params);
			int cg = str_ttoi(&params2);
			int cb = str_ttoi(&params3);
			color3_t c = (color3_t){.red=cr,.green=cg,.blue=cb};
			setBorderColor(&gDisplay,&c);
			printf("Border Color: ");
			printColor3(&c);

			showTrail(&trail);
		}else{
			printf("Error: A Border Color needs 3 values\n");
		}
	}else{
		printf("Error: No Border Color given\n");
	}
}

void cmd_line_color(str_t* command, str_t* params){
	if(params->len > 0){
		str_t params2 = {.len = 0, .str = NULL};
		str_tsplit(params,&params2);

		str_t params3 = {.len = 0, .str = NULL};
		str_tsplit(&params2,&params3);

		if(params3.len > 0){
			str_t trail = {.len = 0, .str = NULL};
			str_tsplit(&params3,&trail);

			int cr = str_ttoi(params);
			int cg = str_ttoi(&params2);
			int cb = str_ttoi(&params3);
			color3_t c = (color3_t){.red=cr,.green=cg,.blue=cb};
			setLineColor(&gDisplay,&c);
			printf("Line Color: ");
			printColor3(&c);

			showTrail(&trail);
		}else{
			printf("Error: A Line Color needs 3 values\n");
		}
	}else{
		printf("Error: No Line Color given\n");
	}
}

void cmd_axis_color(str_t* command, str_t* params){
	if(params->len > 0){
		str_t params2 = {.len = 0, .str = NULL};
		str_tsplit(params,&params2);

		str_t params3 = {.len = 0, .str = NULL};
		str_tsplit(&params2,&params3);

		if(params3.len > 0){
			str_t trail = {.len = 0, .str = NULL};
			str_tsplit(&params3,&trail);

			int cr = str_ttoi(params);
			int cg = str_ttoi(&params2);
			int cb = str_ttoi(&params3);
			color3_t c = (color3_t){.red=cr,.green=cg,.blue=cb};
			setAxisColor(&gDisplay,&c);
			printf("Axis Color: ");
			printColor3(&c);

			showTrail(&trail);
		}else{
			printf("Error: An Axis Color needs 3 values\n");
		}
	}else{
		printf("Error: No Axis Color given\n");
	}
}

void cmd_char_color(str_t* command, str_t* params){
	if(params->len > 0){
		str_t params2 = {.len = 0, .str = NULL};
		str_tsplit(params,&params2);

		str_t params3 = {.len = 0, .str = NULL};
		str_tsplit(&params2,&params3);

		if(params3.len > 0){
			str_t trail = {.len = 0, .str = NULL};
			str_tsplit(&params3,&trail);

			int cr = str_ttoi(params);
			int cg = str_ttoi(&params2);
			int cb = str_ttoi(&params3);
			color3_t c = (color3_t){.red=cr,.green=cg,.blue=cb};
			setCharColor(&gDisplay,&c);
			printf("Char Color: ");
			printColor3(&c);

			showTrail(&trail);
		}else{
			printf("Error: A Char Color needs 3 values\n");
		}
	}else{
		printf("Error: No Char Color given\n");
	}
}

void cmd_view_color(str_t* command, str_t* params){
	if(params->len > 0){
		str_t params2 = {.len = 0, .str = NULL};
		str_tsplit(params,&params2);

		str_t params3 = {.len = 0, .str = NULL};
		str_tsplit(&params2,&params3);

		if(params3.len > 0){
			str_t trail = {.len = 0, .str = NULL};
			str_tsplit(&params3,&trail);

			int cr = str_ttoi(params);
			int cg = str_ttoi(&params2);
			int cb = str_ttoi(&params3);
			color3_t c = (color3_t){.red=cr,.green=cg,.blue=cb};
			setViewColor(&gDisplay,&c);
			printf("View Color: ");
			printColor3(&c);

			showTrail(&trail);
		}else{
			printf("Error: A View Color needs 3 values\n");
		}
	}else{
		printf("Error: No View Color given\n");
	}
}

void cmd_x_start(str_t* command, str_t* params){
	if(params->len > 0){
		str_t trail = {.len = 0, .str = NULL};
		str_tsplit(params,&trail);

		float x = str_ttof(params);
		setXstart(&gDisplay,x);
		printf("X Start: %f\n",x);

		showTrail(&trail);
	}else{
		printf("Error: No X Start given\n");
	}
}

void cmd_y_start(str_t* command, str_t* params){
	if(params->len > 0){
		str_t trail = {.len = 0, .str = NULL};
		str_tsplit(params,&trail);

		float y = str_ttof(params);
		setYstart(&gDisplay,y);
		printf("Y Start: %f\n",y);

		showTrail(&trail);
	}else{
		printf("Error: No Y Start given\n");
	}
}

void cmd_x_end(str_t* command, str_t* params){
	if(params->len > 0){
		str_t trail = {.len = 0, .str = NULL};
		str_tsplit(params,&trail);

		float x = str_ttof(params);
		setXend(&gDisplay,x);
		printf("X End: %f\n",x);

		showTrail(&trail);
	}else{
		printf("Error: No X End given\n");
	}
}

void cmd_y_end(str_t* command, str_t* params){
	if(params->len > 0){
		str_t trail = {.len = 0, .str = NULL};
		str_tsplit(params,&trail);

		float y = str_ttof(params);
		setYend(&gDisplay,y);
		printf("Y End: %f\n",y);

		showTrail(&trail);
	}else{
		printf("Error: No Y End given\n");
	}
}

void cmd_x_range(str_t* command, str_t* params){
	if(params->len > 0){
		str_t params2 = {.len = 0, .str = NULL};
		str_tsplit(params,&params2);

		if(params2.len > 0){
			str_t trail = {.len = 0, .str = NULL};
			str_tsplit(&params2,&trail);

			float xs = str_ttof(params);
			float xe = str_ttof(&params2);
			setXrange(&gDisplay,xs,xe);
			printf("X Range: %f to %f\n",xs,xe);

			showTrail(&trail);
		}else{
			printf("Error: A Range needs 2 values\n");
		}
	}else{
		printf("Error: No Range given\n");
	}
}

void cmd_y_range(str_t* command, str_t* params){
	if(params->len > 0){
		str_t params2 = {.len = 0, .str = NULL};
		str_tsplit(params,&params2);

		if(params2.len > 0){
			str_t trail = {.len = 0, .str = NULL};
			str_tsplit(&params2,&trail);

			float ys = str_ttof(params);
			float ye = str_ttof(&params2);
			setYrange(&gDisplay,ys,ye);
			printf("Y Range: %f to %f\n",ys,ye);

			showTrail(&trail);
		}else{
			printf("Error: A Range needs 2 values\n");
		}
	}else{
		printf("Error: No Range given\n");
	}
}

void cmd_x_padding(str_t* command, str_t* params){
	if(params->len > 0){
		str_t trail = {.len = 0, .str = NULL};
		str_tsplit(params,&trail);

		float x = str_ttof(params);
		if(x < 0.0){ x = 0.0; }
		setXpad(&gDisplay,x);
		printf("X Padding: %f\n",x);

		showTrail(&trail);
	}else{
		printf("Error: No X Padding given\n");
	}
}

void cmd_y_padding(str_t* command, str_t* params){
	if(params->len > 0){
		str_t trail = {.len = 0, .str = NULL};
		str_tsplit(params,&trail);

		float y = str_ttof(params);
		if(y < 0.0){ y = 0.0; }
		setYpad(&gDisplay,y);
		printf("Y Padding: %f\n",y);

		showTrail(&trail);
	}else{
		printf("Error: No Y Padding given\n");
	}
}

void cmd_x_lines(str_t* command, str_t* params){
	if(params->len > 0){
		str_t trail = {.len = 0, .str = NULL};
		str_tsplit(params,&trail);

		int x = str_ttoi(params);
		if(x < 0){ x = 0; }
		setXlines(&gDisplay,x);
		printf("X Lines: %d\n",x);

		showTrail(&trail);
	}else{
		printf("Error: No X Lines given\n");
	}
}

void cmd_y_lines(str_t* command, str_t* params){
	if(params->len > 0){
		str_t trail = {.len = 0, .str = NULL};
		str_tsplit(params,&trail);

		int y = str_ttoi(params);
		if(y < 0){ y = 0; }
		setYlines(&gDisplay,y);
		printf("Y Lines: %d\n",y);

		showTrail(&trail);
	}else{
		printf("Error: No Y Lines given\n");
	}
}

void cmd_x_lines_sy(str_t* command, str_t* params){
	if(params->len > 0){
		str_t trail = {.len = 0, .str = NULL};
		str_tsplit(params,&trail);

		int x = str_ttoi(params);
		if(x < 0){ x = 0; }
		setXlinesSy(&gDisplay,x);
		printf("X Lines: %d\n",x);
		printf("Y Lines: %d\n",gDisplay.viewbox.y_lines);

		showTrail(&trail);
	}else{
		printf("Error: No X Lines given\n");
	}
}

void cmd_y_lines_sx(str_t* command, str_t* params){
	if(params->len > 0){
		str_t trail = {.len = 0, .str = NULL};
		str_tsplit(params,&trail);

		int y = str_ttoi(params);
		if(y < 0){ y = 0; }
		setYlinesSx(&gDisplay,y);
		printf("Y Lines: %d\n",y);
		printf("X Lines: %d\n",gDisplay.viewbox.x_lines);

		showTrail(&trail);
	}else{
		printf("Error: No Y Lines given\n");
	}
}

void cmd_char_size(str_t* command, str_t* params){
	if(params->len > 0){
		str_t trail = {.len = 0, .str = NULL};
		str_tsplit(params,&trail);

		int s = str_ttoi(params);
		if(s <= 0){ s = 1; }
		setCharsize(&gDisplay,s);
		printf("Char Size: %d\n",s);

		showTrail(&trail);
	}else{
		printf("Error: No Char Size given\n");
	}
}

void cmd_line_width(str_t* command, str_t* params){
	if(params->len > 0){
		str_t trail = {.len = 0, .str = NULL};
		str_tsplit(params,&trail);

		int w = str_ttoi(params);
		if(w <= 0){ w = 1; }
		setLineWidth(&gDisplay,w);
		printf("Line Width: %d\n",w);

		showTrail(&trail);
	}else{
		printf("Error: No Line Width given\n");
	}
}

void cmd_axis_line_width(str_t* command, str_t* params){
	if(params->len > 0){
		str_t trail = {.len = 0, .str = NULL};
		str_tsplit(params,&trail);

		int w = str_ttoi(params);
		if(w <= 0){ w = 1; }
		setAxisLineWidth(&gDisplay,w);
		printf("Axis Line Width: %d\n",w);

		showTrail(&trail);
	}else{
		printf("Error: No Axis Line Width given\n");
	}
}

void cmd_x_figure_format(str_t* command, str_t* params){
	if(params->len > 0){
		str_t trail = {.len = 0, .str = NULL};
		str_tsplit(params,&trail);

		char str[params->len + 1];
		for(int i = 0; i < params->len; i++){
			str[i] = params->str[i];
		}
		str[params->len] = 0;

		setXFigureFormat(&gDisplay,str);
		printf("X Figure Format: [%s]\n",str);

		showTrail(&trail);
	}else{
		printf("Error: No X Figure Format given\n");
	}
}

void cmd_y_figure_format(str_t* command, str_t* params){
	if(params->len > 0){
		str_t trail = {.len = 0, .str = NULL};
		str_tsplit(params,&trail);

		char str[params->len + 1];
		for(int i = 0; i < params->len; i++){
			str[i] = params->str[i];
		}
		str[params->len] = 0;

		setYFigureFormat(&gDisplay,str);
		printf("Y Figure Format: [%s]\n",str);

		showTrail(&trail);
	}else{
		printf("Error: No Y Figure Format given\n");
	}
}

void cmd_figure_format(str_t* command, str_t* params){
	if(params->len > 0){
		str_t trail = {.len = 0, .str = NULL};
		str_tsplit(params,&trail);

		char str[params->len + 1];
		for(int i = 0; i < params->len; i++){
			str[i] = params->str[i];
		}
		str[params->len] = 0;

		setFigureFormat(&gDisplay,str);
		printf("Figure Format: [%s]\n",str);

		showTrail(&trail);
	}else{
		printf("Error: No Figure Format given\n");
	}
}

void cmd_show_x_lines(str_t* command, str_t* params){
	if(params->len > 0){
		str_t trail = {.len = 0, .str = NULL};
		str_tsplit(params,&trail);

		int l = str_ttoi(params);
		if(str_tequ(params,&yes)){
			l = 1;
		}
		if(str_tequ(params,&nay)){
			l = 0;
		}

		showXlines(&gDisplay,l);
		printf("Show X Lines: [%s]\n",(l)?("Yes"):("Nay"));

		showTrail(&trail);
	}else{
		char s = gDisplay.viewbox.show_x_lines;
		showXlines(&gDisplay,!s);
		printf("Show X Lines: [%s]\n",(!s)?("Yes"):("Nay"));
	}
}

void cmd_show_y_lines(str_t* command, str_t* params){
	if(params->len > 0){
		str_t trail = {.len = 0, .str = NULL};
		str_tsplit(params,&trail);

		int l = str_ttoi(params);
		if(str_tequ(params,&yes)){
			l = 1;
		}
		if(str_tequ(params,&nay)){
			l = 0;
		}

		showYlines(&gDisplay,l);
		printf("Show Y Lines: [%s]\n",(l)?("Yes"):("Nay"));

		showTrail(&trail);
	}else{
		char s = gDisplay.viewbox.show_y_lines;
		showYlines(&gDisplay,!s);
		printf("Show Y Lines: [%s]\n",(!s)?("Yes"):("Nay"));
	}
}

void cmd_show_lines(str_t* command, str_t* params){
	if(params->len > 0){
		str_t trail = {.len = 0, .str = NULL};
		str_tsplit(params,&trail);

		int l = str_ttoi(params);
		if(str_tequ(params,&yes)){
			l = 1;
		}
		if(str_tequ(params,&nay)){
			l = 0;
		}

		showLines(&gDisplay,l);
		printf("Show Lines: [%s]\n",(l)?("Yes"):("Nay"));

		showTrail(&trail);
	}else{
		char s = gDisplay.viewbox.show_x_lines;
		showXlines(&gDisplay,!s);
		printf("Show X Lines: [%s]\n",(!s)?("Yes"):("Nay"));
		s = gDisplay.viewbox.show_y_lines;
		showYlines(&gDisplay,!s);
		printf("Show Y Lines: [%s]\n",(!s)?("Yes"):("Nay"));
	}
}

void cmd_dashed_line(str_t* command, str_t* params){
	if(params->len > 0){
		str_t trail = {.len = 0, .str = NULL};
		str_tsplit(params,&trail);

		int l = str_ttoi(params);
		if(str_tequ(params,&yes)){
			l = 1;
		}
		if(str_tequ(params,&nay)){
			l = 0;
		}

		dashedLine(&gDisplay,l);
		printf("Dashed Lines: [%s]\n",(l)?("Yes"):("Nay"));

		showTrail(&trail);
	}else{
		char s = gDisplay.viewbox.dashed_line;
		dashedLine(&gDisplay,!s);
		printf("Dashed Lines: [%s]\n",(!s)?("Yes"):("Nay"));
	}
}

void cmd_show_x_axis(str_t* command, str_t* params){
	if(params->len > 0){
		str_t trail = {.len = 0, .str = NULL};
		str_tsplit(params,&trail);

		int l = str_ttoi(params);
		if(str_tequ(params,&yes)){
			l = 1;
		}
		if(str_tequ(params,&nay)){
			l = 0;
		}

		showXAxis(&gDisplay,l);
		printf("Show X Axis: [%s]\n",(l)?("Yes"):("Nay"));

		showTrail(&trail);
	}else{
		char s = gDisplay.viewbox.show_x_axis;
		showXAxis(&gDisplay,!s);
		printf("Show X Axis: [%s]\n",(!s)?("Yes"):("Nay"));
	}
}

void cmd_show_y_axis(str_t* command, str_t* params){
	if(params->len > 0){
		str_t trail = {.len = 0, .str = NULL};
		str_tsplit(params,&trail);

		int l = str_ttoi(params);
		if(str_tequ(params,&yes)){
			l = 1;
		}
		if(str_tequ(params,&nay)){
			l = 0;
		}

		showYAxis(&gDisplay,l);
		printf("Show Y Axis: [%s]\n",(l)?("Yes"):("Nay"));

		showTrail(&trail);
	}else{
		char s = gDisplay.viewbox.show_y_axis;
		showYAxis(&gDisplay,!s);
		printf("Show Y Axis: [%s]\n",(!s)?("Yes"):("Nay"));
	}
}

void cmd_show_axis(str_t* command, str_t* params){
	if(params->len > 0){
		str_t trail = {.len = 0, .str = NULL};
		str_tsplit(params,&trail);

		int l = str_ttoi(params);
		if(str_tequ(params,&yes)){
			l = 1;
		}
		if(str_tequ(params,&nay)){
			l = 0;
		}

		showAxis(&gDisplay,l);
		printf("Show Axis: [%s]\n",(l)?("Yes"):("Nay"));

		showTrail(&trail);
	}else{
		char s = gDisplay.viewbox.show_x_axis;
		showXAxis(&gDisplay,!s);
		printf("Show X Axis: [%s]\n",(!s)?("Yes"):("Nay"));
		s = gDisplay.viewbox.show_y_axis;
		showYAxis(&gDisplay,!s);
		printf("Show Y Axis: [%s]\n",(!s)?("Yes"):("Nay"));
	}
}

void cmd_show_x_figures(str_t* command, str_t* params){
	if(params->len > 0){
		str_t trail = {.len = 0, .str = NULL};
		str_tsplit(params,&trail);

		int l = str_ttoi(params);
		if(str_tequ(params,&yes)){
			l = 1;
		}
		if(str_tequ(params,&nay)){
			l = 0;
		}

		showXFigures(&gDisplay,l);
		printf("Show X Figures: [%s]\n",(l)?("Yes"):("Nay"));

		showTrail(&trail);
	}else{
		char s = gDisplay.viewbox.show_x_figures;
		showXFigures(&gDisplay,!s);
		printf("Show X Figures: [%s]\n",(!s)?("Yes"):("Nay"));
	}
}

void cmd_show_y_figures(str_t* command, str_t* params){
	if(params->len > 0){
		str_t trail = {.len = 0, .str = NULL};
		str_tsplit(params,&trail);

		int l = str_ttoi(params);
		if(str_tequ(params,&yes)){
			l = 1;
		}
		if(str_tequ(params,&nay)){
			l = 0;
		}

		showYFigures(&gDisplay,l);
		printf("Show Y Figures: [%s]\n",(l)?("Yes"):("Nay"));

		showTrail(&trail);
	}else{
		char s = gDisplay.viewbox.show_y_figures;
		showYFigures(&gDisplay,!s);
		printf("Show Y Figures: [%s]\n",(!s)?("Yes"):("Nay"));
	}
}

void cmd_show_figures(str_t* command, str_t* params){
	if(params->len > 0){
		str_t trail = {.len = 0, .str = NULL};
		str_tsplit(params,&trail);

		int l = str_ttoi(params);
		if(str_tequ(params,&yes)){
			l = 1;
		}
		if(str_tequ(params,&nay)){
			l = 0;
		}

		showFigures(&gDisplay,l);
		printf("Show Figures: [%s]\n",(l)?("Yes"):("Nay"));

		showTrail(&trail);
	}else{
		char s = gDisplay.viewbox.show_x_figures;
		showXFigures(&gDisplay,!s);
		printf("Show X Figures: [%s]\n",(!s)?("Yes"):("Nay"));
		s = gDisplay.viewbox.show_y_figures;
		showYFigures(&gDisplay,!s);
		printf("Show Y Figures: [%s]\n",(!s)?("Yes"):("Nay"));
	}
}

// Plotting Commands
void cmd_hsv(str_t* command, str_t* params){
	if(params->len > 0){
		str_t params2 = {.len = 0, .str = NULL};
		str_tsplit(params,&params2);

		str_t params3 = {.len = 0, .str = NULL};
		str_tsplit(&params2,&params3);

		if(params3.len > 0){
			str_t trail = {.len = 0, .str = NULL};
			str_tsplit(&params3,&trail);

			int cr = str_ttoi(params);
			int cg = str_ttoi(&params2);
			int cb = str_ttoi(&params3);
			color3_t c = (color3_t){.red=cr,.green=cg,.blue=cb};
			colorHSV3_t v = RGBtoHSV(&c);
			printf("HSV Color: ");
			printColorHSV3(&v);

			showTrail(&trail);
		}else{
			printf("Error: A Color needs 3 values\n");
		}
	}else{
		printf("Error: No Color given\n");
	}
}

void cmd_rgb(str_t* command, str_t* params){
	if(params->len > 0){
		str_t params2 = {.len = 0, .str = NULL};
		str_tsplit(params,&params2);

		str_t params3 = {.len = 0, .str = NULL};
		str_tsplit(&params2,&params3);

		if(params3.len > 0){
			str_t trail = {.len = 0, .str = NULL};
			str_tsplit(&params3,&trail);

			int cr = str_ttof(params);
			int cg = str_ttof(&params2);
			int cb = str_ttof(&params3);
			colorHSV3_t c = (colorHSV3_t){.Hue=cr,.Sat=cg,.Val=cb};
			color3_t v = HSVtoRGB(&c);
			printf("RGB Color: ");
			printColor3(&v);

			showTrail(&trail);
		}else{
			printf("Error: A Color needs 3 values\n");
		}
	}else{
		printf("Error: No Color given\n");
	}
}

void cmd_flush(str_t* command, str_t* params){
	if(params->len > 0){
		str_t params2 = {.len = 0, .str = NULL};
		str_tsplit(params,&params2);

		str_t params3 = {.len = 0, .str = NULL};
		str_tsplit(&params2,&params3);

		if(params3.len > 0){
			str_t trail = {.len = 0, .str = NULL};
			str_tsplit(&params3,&trail);

			int cr = str_ttoi(params);
			int cg = str_ttoi(&params2);
			int cb = str_ttoi(&params3);
			color3_t c = (color3_t){.red=cr,.green=cg,.blue=cb};
			flushColorBuffer(&gDisplay,&c);
			printf("Color: ");
			printColor3(&c);

			showTrail(&trail);
		}else{
			printf("Error: A Color needs 3 values\n");
		}
	}else{
		printf("Error: No Color given\n");
	}
}

void cmd_point(str_t* command, str_t* params){
	if(params->len > 0){
		str_t params2 = {.len = 0, .str = NULL};
		str_tsplit(params,&params2);

		str_t params3 = {.len = 0, .str = NULL};
		str_tsplit(&params2,&params3);

		str_t params4 = {.len = 0, .str = NULL};
		str_tsplit(&params3,&params4);

		str_t params5 = {.len = 0, .str = NULL};
		str_tsplit(&params4,&params5);

		if(params5.len > 0){
			str_t trail = {.len = 0, .str = NULL};
			str_tsplit(&params5,&trail);

			int cr = str_ttoi(params);
			int cg = str_ttoi(&params2);
			int cb = str_ttoi(&params3);

			int x = str_ttoi(&params4);
			int y = str_ttoi(&params5);
			color3_t c = (color3_t){.red=cr,.green=cg,.blue=cb};
			Point_Bound(&gDisplay,&c,x,y);
			printf("Plotted point at (%d,%d)\n",x,y);

			showTrail(&trail);
		}else{
			printf("Error: A Point needs 5 (r,g,b) (x,y) values\n");
		}
	}else{
		printf("Error: No Color or Point given\n");
	}
}

void cmd_vline(str_t* command, str_t* params){
	if(params->len > 0){
		str_t trail = {.len = 0, .str = NULL};
		str_tsplit(params,&trail);

		int x = str_ttoi(params);
		Vline(&gDisplay,x);
		printf("Plotted Vertical line at %d\n",x);

		showTrail(&trail);
	}else{
		printf("Error: No position given\n");
	}
}

void cmd_hline(str_t* command, str_t* params){
	if(params->len > 0){
		str_t trail = {.len = 0, .str = NULL};
		str_tsplit(params,&trail);

		int y = str_ttoi(params);
		Hline(&gDisplay,y);
		printf("Plotted Horizontal line at %d\n",y);

		showTrail(&trail);
	}else{
		printf("Error: No position given\n");
	}
}

void cmd_vlines(str_t* command, str_t* params){
	if(params->len > 0){
		str_t trail = {.len = 0, .str = NULL};
		str_tsplit(params,&trail);

		int n = str_ttoi(params);
		Vlines(&gDisplay,n);
		printf("Plotted Vertical lines\n");

		showTrail(&trail);
	}else{
		printf("Error: No number given\n");
	}
}

void cmd_hlines(str_t* command, str_t* params){
	if(params->len > 0){
		str_t trail = {.len = 0, .str = NULL};
		str_tsplit(params,&trail);

		int n = str_ttoi(params);
		Hlines(&gDisplay,n);
		printf("Plotted Horizontal lines\n");

		showTrail(&trail);
	}else{
		printf("Error: No number given\n");
	}
}

void cmd_putc(str_t* command, str_t* params){
	if(params->len > 0){
		str_t params2 = {.len = 0, .str = NULL};
		str_tsplit(params,&params2);

		str_t params3 = {.len = 0, .str = NULL};
		str_tsplit(&params2,&params3);

		if(params3.len > 0){
			str_t trail = {.len = 0, .str = NULL};
			str_tsplit(&params3,&trail);

			char c = params->str[0];
			int cx = str_ttoi(&params2);
			int cy = str_ttoi(&params3);

			printf("Put [%c] at (%d,%d)\n",c,cx,cy);
			BufPutc(&gDisplay,c,cx,cy);
			showTrail(&trail);
		}else{
			printf("Error: A Char needs 3 (c) (x,y) values\n");
		}
	}else{
		printf("Error: No char or point given\n");
	}
}

void cmd_print(str_t* command, str_t* params){
	if(params->len > 0){
		str_t params2 = {.len = 0, .str = NULL};
		str_tsplit(params,&params2);

		str_t params3 = {.len = 0, .str = NULL};
		str_tsplit(&params2,&params3);

		if(params3.len > 0){
			str_t trail = {.len = 0, .str = NULL};
			str_tsplit(&params3,&trail);

			char str[params->len + 1];
			for(int i = 0; i < params->len; i++){
				str[i] = params->str[i];
			}
			str[params->len] = 0;
			int cx = str_ttoi(&params2);
			int cy = str_ttoi(&params3);
			BufStrPrint(&gDisplay,str,cx,cy);
			printf("Put [%s] at (%d,%d)\n",str,cx,cy);

			showTrail(&trail);
		}else{
			printf("Error: A String needs 3 (s) (x,y) values\n");
		}
	}else{
		printf("Error: No string or point given\n");
	}
}

void cmd_plot_xlines(str_t* command, str_t* params){
	PlotXlines(&gDisplay);
	printf("Plotted X Lines\n");
}

void cmd_plot_ylines(str_t* command, str_t* params){
	PlotYlines(&gDisplay);
	printf("Plotted Y Lines\n");
}

void cmd_plot_xaxis(str_t* command, str_t* params){
	PlotXaxis(&gDisplay);
	printf("Plotted X Axis\n");
}

void cmd_plot_yaxis(str_t* command, str_t* params){
	PlotYaxis(&gDisplay);
	printf("Plotted Y Axis\n");
}

void cmd_plot_lines(str_t* command, str_t* params){
	PlotViewBoxLines(&gDisplay);
	printf("Plotted Viewbox Lines\n");
}

float executeFunc(float x){
	localSet(&gVars,&(str_t){.len=1,.str = "x"},VAR_TYPE_FLOAT,&x);
	return vstr_tfunc(&gFunct);
}

void cmd_funct(str_t* command, str_t* params){
	if(params->len > 0){
		str_t params2 = {.len = 0, .str = NULL};
		str_tsplit(params,&params2);

		str_t params3 = {.len = 0, .str = NULL};
		str_tsplit(&params2,&params3);

		str_t params4 = {.len = 0, .str = NULL};
		str_tsplit(&params3,&params4);

		if(params4.len > 0){
			int cr = str_ttoi(params);
			int cg = str_ttoi(&params2);
			int cb = str_ttoi(&params3);

			str_tcopy(&params4,&gFunct);
			color3_t c = (color3_t){.red=cr,.green=cg,.blue=cb};
			
			PlotFunc_Color(&gDisplay,&c,&executeFunc);
			printf("Plotted function\n");
			str_tprintln(&params4);
		}else{
			printf("Error: A Function needs 4 (r,g,b) f(x) values\n");
		}
	}else{
		printf("Error: No Color or Function given\n");
	}
}

void cmd_refunct(str_t* command, str_t* params){
	if(params->len > 0){
		str_t params2 = {.len = 0, .str = NULL};
		str_tsplit(params,&params2);

		str_t params3 = {.len = 0, .str = NULL};
		str_tsplit(&params2,&params3);

		str_t params4 = {.len = 0, .str = NULL};
		str_tsplit(&params3,&params4);

		if(params4.len > 0){
			int cr = str_ttoi(params);
			int cg = str_ttoi(&params2);
			int cb = str_ttoi(&params3);

			str_tcopy(&params4,&gFunct);
			color3_t c = (color3_t){.red=cr,.green=cg,.blue=cb};
			
			RePlotFunc_Color(&gDisplay,&c,&executeFunc);
			printf("Plotted function\n");
			str_tprintln(&params4);
		}else{
			printf("Error: A Function needs 4 (r,g,b) f(x) values\n");
		}
	}else{
		printf("Error: No Color or Function given\n");
	}
}

void cmd_inequ(str_t* command, str_t* params){
	if(params->len > 0){
		str_t params2 = {.len = 0, .str = NULL};
		str_tsplit(params,&params2);

		str_t params3 = {.len = 0, .str = NULL};
		str_tsplit(&params2,&params3);

		str_t params4 = {.len = 0, .str = NULL};
		str_tsplit(&params3,&params4);

		str_t params5 = {.len = 0, .str = NULL};
		str_tsplit(&params4,&params5);

		if(params5.len > 0){
			int cr = str_ttoi(params);
			int cg = str_ttoi(&params2);
			int cb = str_ttoi(&params3);

			int ty = INEQ_TYPE_LESS_THAN;
			if(params4.len > 1){
				if(params4.str[0] == '<'){
					ty = INEQ_TYPE_LESS_THAN;
					if(params4.str[0] == '='){
						ty = INEQ_TYPE_LESS_THAN_OR_EQU;
					}
				}

				if(params4.str[0] == '>'){
					ty = INEQ_TYPE_GREATER_THAN;
					if(params4.str[0] == '='){
						ty = INEQ_TYPE_GREATER_THAN_OR_EQU;
					}
				}
			}

			str_tcopy(&params5,&gFunct);
			color3_t c = (color3_t){.red=cr,.green=cg,.blue=cb};
			
			PlotIneq_Color(&gDisplay,&c,&executeFunc,ty);
			printf("Plotted inequality\n");
			str_tprintln(&params5);
		}else{
			printf("Error: An Inequality needs 5 (r,g,b) (< > <= >=) f(x) values\n");
		}
	}else{
		printf("Error: No Color or Inequality given\n");
	}
}

void cmd_reinequ(str_t* command, str_t* params){
	if(params->len > 0){
		str_t params2 = {.len = 0, .str = NULL};
		str_tsplit(params,&params2);

		str_t params3 = {.len = 0, .str = NULL};
		str_tsplit(&params2,&params3);

		str_t params4 = {.len = 0, .str = NULL};
		str_tsplit(&params3,&params4);

		str_t params5 = {.len = 0, .str = NULL};
		str_tsplit(&params4,&params5);

		if(params5.len > 0){
			int cr = str_ttoi(params);
			int cg = str_ttoi(&params2);
			int cb = str_ttoi(&params3);

			int ty = INEQ_TYPE_LESS_THAN;
			if(params4.len > 1){
				if(params4.str[0] == '<'){
					ty = INEQ_TYPE_LESS_THAN;
					if(params4.str[0] == '='){
						ty = INEQ_TYPE_LESS_THAN_OR_EQU;
					}
				}

				if(params4.str[0] == '>'){
					ty = INEQ_TYPE_GREATER_THAN;
					if(params4.str[0] == '='){
						ty = INEQ_TYPE_GREATER_THAN_OR_EQU;
					}
				}
			}

			str_tcopy(&params5,&gFunct);
			color3_t c = (color3_t){.red=cr,.green=cg,.blue=cb};
			
			PlotIneq_Color(&gDisplay,&c,&executeFunc,ty);
			printf("Plotted inequality\n");
			str_tprintln(&params5);
		}else{
			printf("Error: An Inequality needs 5 (r,g,b) (< > <= >=) f(x) values\n");
		}
	}else{
		printf("Error: No Color or Inequality given\n");
	}
}

// Data Commands


str_t commands[] = {
	(str_t){.len=7,.str="version"},
	(str_t){.len=1,.str="v"},
	(str_t){.len=4,.str="help"},
	(str_t){.len=1,.str="h"},
	(str_t){.len=4,.str="exit"},
	(str_t){.len=4,.str="plot"},
	(str_t){.len=4,.str="show"},
	(str_t){.len=6,.str="height"},
	(str_t){.len=5,.str="width"},
	(str_t){.len=6,.str="border"},
	(str_t){.len=11,.str="border-left"},
	(str_t){.len=12,.str="border-right"},
	(str_t){.len=9,.str="border-up"},
	(str_t){.len=11,.str="border-down"},
	(str_t){.len=12,.str="border-color"},
	(str_t){.len=10,.str="line-color"},
	(str_t){.len=10,.str="axis-color"},
	(str_t){.len=10,.str="char-color"},
	(str_t){.len=10,.str="view-color"},
	(str_t){.len=7,.str="x-start"},
	(str_t){.len=7,.str="y-start"},
	(str_t){.len=5,.str="x-end"},
	(str_t){.len=5,.str="y-end"},
	(str_t){.len=7,.str="x-range"},
	(str_t){.len=7,.str="y-range"},
	(str_t){.len=9,.str="x-padding"},
	(str_t){.len=9,.str="y-padding"},
	(str_t){.len=7,.str="x-lines"},
	(str_t){.len=7,.str="y-lines"},
	(str_t){.len=10,.str="x-lines-sy"},
	(str_t){.len=10,.str="y-lines-sx"},
	(str_t){.len=9,.str="char-size"},
	(str_t){.len=10,.str="line-width"},
	(str_t){.len=15,.str="axis-line-width"},
	(str_t){.len=15,.str="x-figure-format"},
	(str_t){.len=15,.str="y-figure-format"},
	(str_t){.len=13,.str="figure-format"},
	(str_t){.len=13,.str="show-x-lines"},
	(str_t){.len=13,.str="show-y-lines"},
	(str_t){.len=10,.str="show-lines"},
	(str_t){.len=15,.str="dashed-line"},
	(str_t){.len=11,.str="show-x-axis"},
	(str_t){.len=11,.str="show-y-axis"},
	(str_t){.len=9,.str="show-axis"},
	(str_t){.len=14,.str="show-x-figures"},
	(str_t){.len=14,.str="show-y-figures"},
	(str_t){.len=12,.str="show-figures"},
	(str_t){.len=3,.str="hsv"},
	(str_t){.len=3,.str="rgb"},
	(str_t){.len=5,.str="flush"},
	(str_t){.len=5,.str="point"},
	(str_t){.len=5,.str="vline"},
	(str_t){.len=5,.str="hline"},
	(str_t){.len=6,.str="vlines"},
	(str_t){.len=6,.str="hlines"},
	(str_t){.len=4,.str="putc"},
	(str_t){.len=5,.str="print"},
	(str_t){.len=11,.str="plot-xlines"},
	(str_t){.len=11,.str="plot-ylines"},
	(str_t){.len=10,.str="plot-xaxis"},
	(str_t){.len=10,.str="plot-yaxis"},
	(str_t){.len=17,.str="plot-lines"},
	(str_t){.len=5,.str="funct"},
	(str_t){.len=7,.str="refunct"},
	(str_t){.len=5,.str="inequ"},
	(str_t){.len=7,.str="reinequ"},
};

int runCommand(str_t* command, str_t* params){
	if(CMD(CMD_VER1) || CMD(CMD_VER2)){
		version();
		return 0;
	}

	if(CMD(CMD_HELP1) || CMD(CMD_HELP2)){
		cmd_help(command,params);
		return 0;
	}

	if(CMD(CMD_EXIT)){
		cmd_exit(command,params);
		return 0;
	}

	if(CMD(CMD_PLOT)){
		cmd_plot(command,params);
		return 0;
	}

	if(CMD(CMD_SHOW)){
		cmd_show(command,params);
		return 0;
	}

	if(CMD(CMD_HEIGHT)){
		cmd_height(command,params);
		return 0;
	}

	if(CMD(CMD_WIDTH)){
		cmd_width(command,params);
		return 0;
	}

	if(CMD(CMD_BORDER)){
		cmd_border(command,params);
		return 0;
	}

	if(CMD(CMD_BORDER_LEFT)){
		cmd_border_left(command,params);
		return 0;
	}

	if(CMD(CMD_BORDER_RIGHT)){
		cmd_border_right(command,params);
		return 0;
	}

	if(CMD(CMD_BORDER_UP)){
		cmd_border_up(command,params);
		return 0;
	}

	if(CMD(CMD_BORDER_DOWN)){
		cmd_border_down(command,params);
		return 0;
	}

	if(CMD(CMD_BORDER_COLOR)){
		cmd_border_color(command,params);
		return 0;
	}

	if(CMD(CMD_LINE_COLOR)){
		cmd_line_color(command,params);
		return 0;
	}

	if(CMD(CMD_AXIS_COLOR)){
		cmd_axis_color(command,params);
		return 0;
	}

	if(CMD(CMD_CHAR_COLOR)){
		cmd_char_color(command,params);
		return 0;
	}

	if(CMD(CMD_VIEW_COLOR)){
		cmd_view_color(command,params);
		return 0;
	}

	if(CMD(CMD_X_START)){
		cmd_x_start(command,params);
		return 0;
	}

	if(CMD(CMD_Y_START)){
		cmd_y_start(command,params);
		return 0;
	}

	if(CMD(CMD_X_END)){
		cmd_x_end(command,params);
		return 0;
	}

	if(CMD(CMD_Y_END)){
		cmd_y_end(command,params);
		return 0;
	}

	if(CMD(CMD_X_RANGE)){
		cmd_x_range(command,params);
		return 0;
	}

	if(CMD(CMD_Y_RANGE)){
		cmd_y_range(command,params);
		return 0;
	}

	if(CMD(CMD_X_PADDING)){
		cmd_x_padding(command,params);
		return 0;
	}

	if(CMD(CMD_Y_PADDING)){
		cmd_y_padding(command,params);
		return 0;
	}

	if(CMD(CMD_X_LINES)){
		cmd_x_lines(command,params);
		return 0;
	}

	if(CMD(CMD_Y_LINES)){
		cmd_y_lines(command,params);
		return 0;
	}

	if(CMD(CMD_X_LINES_SY)){
		cmd_x_lines_sy(command,params);
		return 0;
	}

	if(CMD(CMD_Y_LINES_SX)){
		cmd_y_lines_sx(command,params);
		return 0;
	}

	if(CMD(CMD_CHAR_SIZE)){
		cmd_char_size(command,params);
		return 0;
	}

	if(CMD(CMD_LINE_WIDTH)){
		cmd_line_width(command,params);
		return 0;
	}

	if(CMD(CMD_AXIS_LINE_WIDTH)){
		cmd_axis_line_width(command,params);
		return 0;
	}

	if(CMD(CMD_X_FIGURE_FORMAT)){
		cmd_x_figure_format(command,params);
		return 0;
	}

	if(CMD(CMD_Y_FIGURE_FORMAT)){
		cmd_y_figure_format(command,params);
		return 0;
	}

	if(CMD(CMD_FIGURE_FORMAT)){
		cmd_figure_format(command,params);
		return 0;
	}

	if(CMD(CMD_SHOW_X_LINES)){
		cmd_show_x_lines(command,params);
		return 0;
	}

	if(CMD(CMD_SHOW_Y_LINES)){
		cmd_show_y_lines(command,params);
		return 0;
	}

	if(CMD(CMD_SHOW_LINES)){
		cmd_show_lines(command,params);
		return 0;
	}

	if(CMD(CMD_DASHED_LINE)){
		cmd_dashed_line(command,params);
		return 0;
	}

	if(CMD(CMD_SHOW_X_AXIS)){
		cmd_show_x_axis(command,params);
		return 0;
	}

	if(CMD(CMD_SHOW_Y_AXIS)){
		cmd_show_y_axis(command,params);
		return 0;
	}

	if(CMD(CMD_SHOW_AXIS)){
		cmd_show_axis(command,params);
		return 0;
	}

	if(CMD(CMD_SHOW_X_FIGURES)){
		cmd_show_x_figures(command,params);
		return 0;
	}

	if(CMD(CMD_SHOW_Y_FIGURES)){
		cmd_show_y_figures(command,params);
		return 0;
	}

	if(CMD(CMD_SHOW_FIGURES)){
		cmd_show_figures(command,params);
		return 0;
	}

	if(CMD(CMD_HSV)){
		cmd_hsv(command,params);
		return 0;
	}

	if(CMD(CMD_RGB)){
		cmd_rgb(command,params);
		return 0;
	}

	if(CMD(CMD_FLUSH)){
		cmd_flush(command,params);
		return 0;
	}

	if(CMD(CMD_POINT)){
		cmd_point(command,params);
		return 0;
	}

	if(CMD(CMD_VLINE)){
		cmd_vline(command,params);
		return 0;
	}

	if(CMD(CMD_HLINE)){
		cmd_hline(command,params);
		return 0;
	}

	if(CMD(CMD_VLINES)){
		cmd_vlines(command,params);
		return 0;
	}

	if(CMD(CMD_HLINES)){
		cmd_hlines(command,params);
		return 0;
	}

	if(CMD(CMD_PUTC)){
		cmd_putc(command,params);
		return 0;
	}

	if(CMD(CMD_PRINT)){
		cmd_print(command,params);
		return 0;
	}

	if(CMD(CMD_PLOT_XLINES)){
		cmd_plot_xlines(command,params);
		return 0;
	}

	if(CMD(CMD_PLOT_YLINES)){
		cmd_plot_ylines(command,params);
		return 0;
	}

	if(CMD(CMD_PLOT_XAXIS)){
		cmd_plot_xaxis(command,params);
		return 0;
	}

	if(CMD(CMD_PLOT_YAXIS)){
		cmd_plot_yaxis(command,params);
		return 0;
	}

	if(CMD(CMD_PLOT_LINES)){
		cmd_plot_lines(command,params);
		return 0;
	}

	if(CMD(CMD_FUNCT)){
		cmd_funct(command,params);
		return 0;
	}

	if(CMD(CMD_REFUNCT)){
		cmd_refunct(command,params);
		return 0;
	}

	if(CMD(CMD_INEQU)){
		cmd_inequ(command,params);
		return 0;
	}

	if(CMD(CMD_REINEQU)){
		cmd_reinequ(command,params);
		return 0;
	}

	// Invalid command
	printf("Unknown Command\n");
	printf("-> ");
	str_tprintln(command);
	return 0;
}

#endif
