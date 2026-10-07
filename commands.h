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
#define CMD_HSV	47
#define CMD_RGB	48
#define CMD_FLUSH	49
#define CMD_POINT	50
#define CMD_VLINE	51
#define CMD_HLINE	52
#define CMD_VLINES	53
#define CMD_HLINES	54
#define CMD_PUTC	55
#define CMD_PRINT	56
#define CMD_PLOT_XLINES	57
#define CMD_PLOT_YLINES	58
#define CMD_PLOT_XAXIS	59
#define CMD_PLOT_YAXIS	60
#define CMD_PLOT_LINES	61
#define CMD_FUNCT	62
#define CMD_REFUNCT	63
#define CMD_INEQU	64
#define CMD_REINEQU	65
#define CMD_NEW_LIST	66
#define CMD_EMPTY_LIST	67
#define CMD_APP_LIST	68
#define CMD_INX_LIST	69
#define CMD_PLOT_X_LIST	70
#define CMD_PLOT_Y_LIST	71
#define CMD_PLOT_XY_LIST	72
#define CMD_REPLOT_X_LIST	73
#define CMD_REPLOT_Y_LIST	74
#define CMD_REPLOT_XY_LIST	75
#define CMD_SHOW_LIST	76
#define CMD_SHOW_LISTN	77
#define CMD_VAR	78
#define CMD_SHOW_VAR	79

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

// Plotting Commands
void cmd_hsv(str_t* command, str_t* params);
void cmd_rgb(str_t* command, str_t* params);
void cmd_flush(str_t* command, str_t* params);
void cmd_point(str_t* command, str_t* params);
void cmd_vline(str_t* command, str_t* params);
void cmd_hline(str_t* command, str_t* params);
void cmd_vlines(str_t* command, str_t* params);
void cmd_hlines(str_t* command, str_t* params);
void cmd_putc(str_t* command, str_t* params);
void cmd_print(str_t* command, str_t* params);
void cmd_plot_xlines(str_t* command, str_t* params);
void cmd_plot_ylines(str_t* command, str_t* params);
void cmd_plot_xaxis(str_t* command, str_t* params);
void cmd_plot_yaxis(str_t* command, str_t* params);
void cmd_plot_lines(str_t* command, str_t* params);
float executeFunc(float x);
void cmd_funct(str_t* command, str_t* params);
void cmd_refunct(str_t* command, str_t* params);
void cmd_inequ(str_t* command, str_t* params);
void cmd_reinequ(str_t* command, str_t* params);

// Data Commands
void cmd_new_list(str_t* command, str_t* params);
void cmd_empty_list(str_t* command, str_t* params);
void cmd_app_list(str_t* command, str_t* params);
void cmd_inx_list(str_t* command, str_t* params);
void cmd_plot_x_list(str_t* command, str_t* params);
void cmd_plot_y_list(str_t* command, str_t* params);
void cmd_plot_xy_list(str_t* command, str_t* params);
void cmd_replot_x_list(str_t* command, str_t* params);
void cmd_replot_y_list(str_t* command, str_t* params);
void cmd_replot_xy_list(str_t* command, str_t* params);
void cmd_show_list(str_t* command, str_t* params);
void cmd_show_list(str_t* command, str_t* params);
void cmd_var(str_t* command, str_t* params);
void cmd_show_var(str_t* command, str_t* params);

int runCommand(str_t* command, str_t* params);

extern str_t yes;
extern str_t nay;


#endif
