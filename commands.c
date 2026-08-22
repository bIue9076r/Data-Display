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
			printf("h / help\t\t|\tHelp\n");
			printf("v / version\t\t|\tVersion\n");
			printf("exit\t\t\t|\tExit\n");
		break;

		case 1:
			printf("Commands page %d - Display\n",i);
			printf("plot\t\t\t|\tPlot\n");
			printf("show\t\t\t|\tShow\n");
			printf("height\t\t\t|\tHeight\n");
			printf("width\t\t\t|\tWidth\n");
			printf("border\t\t\t|\tBorder\n");
			printf("border-left\t\t|\tBorder Left\n");
			printf("border-right\t\t|\tBorder Right\n");
			printf("border-up\t\t|\tBorder Up\n");
			printf("border-down\t\t|\tBorder Down\n");
			printf("border-color\t\t|\tBorder Color\n");
			printf("line-color\t\t|\tLine Color\n");
			printf("axis-color\t\t|\tAxis Color\n");
			printf("char-color\t\t|\tChar Color\n");
			printf("view-color\t\t|\tView Color\n");
			printf("x-start\t\t\t|\tX Start\n");
			printf("y-start\t\t\t|\tY Start\n");
			printf("x-end\t\t\t|\tX End\n");
			printf("y-end\t\t\t|\tY End\n");
			printf("x-range\t\t\t|\tX Range\n");
			printf("y-range\t\t\t|\tY Range\n");
			printf("x-padding\t\t|\tX Padding\n");
			printf("y-padding\t\t|\tY Padding\n");
			printf("x-lines\t\t\t|\tX Lines\n");
			printf("y-lines\t\t\t|\tY Lines\n");
			printf("x-lines-sy\t\t|\tX Lines Square y\n");
			printf("y-lines-sx\t\t|\tY Lines Square x\n");
			printf("char-size\t\t|\tChar Size\n");
			printf("line-width\t\t|\tLine Width\n");
			printf("axis-line-width\t\t|\tAxis Line Width\n");
			printf("x-figure-format\t\t|\tX Figure Format\n");
			printf("y-figure-format\t\t|\tY Figure Format\n");
			printf("figure-format\t\t|\tFigure Format\n");
			printf("show-x-lines\t\t|\tShow X Lines\n");
			printf("show-y-lines\t\t|\tShow Y Lines\n");
			printf("show-lines\t\t|\tShow Lines\n");
			printf("dashed-line\t\t|\tDashed Line\n");
			printf("show-x-axis\t\t|\tShow X Axis\n");
			printf("show-y-axis\t\t|\tShow Y Axis\n");
			printf("show-axis\t\t|\tShow Axis\n");
			printf("show-x-figures\t\t|\tShow X Figures\n");
			printf("show-y-figures\t\t|\tShow Y Figures\n");
			printf("show-figures\t\t|\tShow Figures\n");
		break;

		case 2:
			printf("Commands page %d - Ploting\n",i);
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

		printf("Ploted display to \"");
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


	// Invalid command
	printf("Unknown Command\n");
	printf("-> ");
	str_tprintln(command);
	return 0;
}

#endif
