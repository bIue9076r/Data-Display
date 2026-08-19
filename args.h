#ifndef ARGS_H
#define ARGS_H
#include "gdeclare.h"
#include "strlib.h"

#define ARG_HELP 0
#define ARG_VERSION 2
#define ARG_INPUT 4
#define ARG_HEIGHT 6
#define ARG_WITDH 8
#define ARG_BORDER 10
#define ARG_BORDER_LEFT 12
#define ARG_BORDER_RIGHT 14
#define ARG_BORDER_UP 16
#define ARG_BORDER_DOWN 18
#define ARG_BORDER_COLOR 20
#define ARG_LINE_COLOR 22
#define ARG_AXIS_COLOR 24
#define ARG_CHAR_COLOR 26
#define ARG_VIEW_COLOR 28
#define ARG_X_START 30
#define ARG_Y_START 32
#define ARG_X_END 34
#define ARG_Y_END 36
#define ARG_X_RANGE 38
#define ARG_Y_RANGE 40
#define ARG_X_PADDING 42
#define ARG_Y_PADDING 44
#define ARG_X_LINES 46
#define ARG_Y_LINES 48
#define ARG_X_LINES_SY 50
#define ARG_Y_LINES_SX 52
#define ARG_CHAR_SIZE 54
#define ARG_LINE_WIDTH 56
#define ARG_AXIS_LINE_WIDTH 58
#define ARG_X_FIGURE_FORMAT 60
#define ARG_Y_FIGURE_FORMAT 62
#define ARG_FIGURE_FORMAT 64
#define ARG_SHOW_X_LINES 66
#define ARG_SHOW_Y_LINES 68
#define ARG_SHOW_LINES 70
#define ARG_DASHED_LINE 72
#define ARG_SHOW_X_AXIS 74
#define ARG_SHOW_Y_AXIS 76
#define ARG_SHOW_AXIS 78
#define ARG_SHOW_X_FIGURES 80
#define ARG_SHOW_Y_FIGURES 82
#define ARG_SHOW_FIGURES 84

#define ARG(n) str_tequ(&a,&arg_strings[n]) || str_tequ(&a,&arg_strings[n + 1])

#endif
