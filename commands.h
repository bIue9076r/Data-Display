#ifndef COMMANDS_H
#define COMMANDS_H
#include "gdeclare.h"
#include "strlib.h"

#define CMD_VER1	0
#define CMD_VER2	1
#define CMD_HELP1	2
#define CMD_HELP2	3
#define CMD_EXIT	4

#define CMD_PLOT	5
#define CMD_SHOW	6
#define CMD_HEIGHT	7
#define CMD_WIDTH	8
#define CMD_BORDER	9
#define CMD_BORDER_LEFT	10
#define CMD_BORDER_RIGHT	11
#define CMD_BORDER_UP	12
#define CMD_BORDER_DOWN	13
#define CMD_BORDER_COLOR	14
#define CMD_LINE_COLOR	15
#define CMD_AXIS_COLOR	16
#define CMD_CHAR_COLOR	17
#define CMD_VIEW_COLOR	18
#define CMD_X_START	19
#define CMD_Y_START	20
#define CMD_X_END	21
#define CMD_Y_END	22
#define CMD_X_RANGE	23
#define CMD_Y_RANGE	24
#define CMD_X_PADDING	25
#define CMD_Y_PADDING	26
#define CMD_X_LINES	27
#define CMD_Y_LINES	28
#define CMD_X_LINES_SY	29
#define CMD_Y_LINES_SX	30
#define CMD_CHAR_SIZE	31
#define CMD_LINE_WIDTH	32
#define CMD_AXIS_LINE_WIDTH	33
#define CMD_X_FIGURE_FORMAT	34
#define CMD_Y_FIGURE_FORMAT	35
#define CMD_FIGURE_FORMAT	36
#define CMD_SHOW_X_LINES	37
#define CMD_SHOW_Y_LINES	38
#define CMD_SHOW_LINES	39
#define CMD_DASHED_LINE	40
#define CMD_SHOW_X_AXIS	41
#define CMD_SHOW_Y_AXIS	42
#define CMD_SHOW_AXIS	43
#define CMD_SHOW_X_FIGURES	44
#define CMD_SHOW_Y_FIGURES	45
#define CMD_SHOW_FIGURES	46

#define CMD(C) str_tequ(command,&commands[C])

void commandHelp(int i);
void cmd_help(str_t* command, str_t* params);
void cmd_exit(str_t* command, str_t* params);

// Display comands
void cmd_plot(str_t* command, str_t* params);
void cmd_show(str_t* command, str_t* params);
void cmd_height(str_t* command, str_t* params);
void cmd_width(str_t* command, str_t* params);
void cmd_border(str_t* command, str_t* params);
void cmd_border_left(str_t* command, str_t* params);
void cmd_border_right(str_t* command, str_t* params);
void cmd_border_up(str_t* command, str_t* params);
void cmd_border_down(str_t* command, str_t* params);
void cmd_border_color(str_t* command, str_t* params);
void cmd_line_color(str_t* command, str_t* params);
void cmd_axis_color(str_t* command, str_t* params);
void cmd_char_color(str_t* command, str_t* params);
void cmd_view_color(str_t* command, str_t* params);
void cmd_x_start(str_t* command, str_t* params);
void cmd_y_start(str_t* command, str_t* params);
void cmd_x_end(str_t* command, str_t* params);
void cmd_y_end(str_t* command, str_t* params);
void cmd_x_range(str_t* command, str_t* params);
void cmd_y_range(str_t* command, str_t* params);
void cmd_x_padding(str_t* command, str_t* params);
void cmd_y_padding(str_t* command, str_t* params);
void cmd_x_lines(str_t* command, str_t* params);
void cmd_y_lines(str_t* command, str_t* params);
void cmd_x_lines_sy(str_t* command, str_t* params);
void cmd_y_lines_sx(str_t* command, str_t* params);
void cmd_char_size(str_t* command, str_t* params);
void cmd_line_width(str_t* command, str_t* params);
void cmd_axis_line_width(str_t* command, str_t* params);
void cmd_x_figure_format(str_t* command, str_t* params);
void cmd_y_figure_format(str_t* command, str_t* params);
void cmd_figure_format(str_t* command, str_t* params);
void cmd_show_x_lines(str_t* command, str_t* params);
void cmd_show_y_lines(str_t* command, str_t* params);
void cmd_show_lines(str_t* command, str_t* params);
void cmd_dashed_line(str_t* command, str_t* params);
void cmd_show_x_axis(str_t* command, str_t* params);
void cmd_show_y_axis(str_t* command, str_t* params);
void cmd_show_axis(str_t* command, str_t* params);
void cmd_show_x_figures(str_t* command, str_t* params);
void cmd_show_y_figures(str_t* command, str_t* params);
void cmd_show_figures(str_t* command, str_t* params);

int runCommand(str_t* command, str_t* params);

extern str_t yes;
extern str_t nay;


#endif
