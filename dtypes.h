#ifndef DTYPES_H
#define DTYPES_H

typedef struct color3_s {
	unsigned char red;
	unsigned char green;
	unsigned char blue;
} color3_t;

typedef struct colorHSV3_s {
	float Hue;
	float Sat;
	float Val;
} colorHSV3_t;

typedef struct border_s {
	int left;
	int right;
	int up;
	int down;
} border_t;

typedef struct viewbox_s {
	int height;
	int width;

	float x_start;
	float y_start;
	float x_end;
	float y_end;

	float y_pad;
	float x_pad;

	int x_lines;
	int y_lines;

	int charsize;
	int line_width;
	int axis_line_width;
	char* x_figure_fmt;
	char* y_figure_fmt;

	char show_x_lines;
	char show_y_lines;
	char dashed_line;
	char show_x_axis;
	char show_y_axis;
	char show_x_figures;
	char show_y_figures;
} viewbox_t;

typedef struct display_s {
	viewbox_t viewbox;
	border_t borders;
	color3_t* colorBuffer;

	color3_t border_color;
	color3_t line_color;
	color3_t axis_color;
	color3_t char_color;
	color3_t view_color;
} display_t;

typedef float func_t(float);

#endif