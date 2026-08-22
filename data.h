#ifndef DATA_H
#define DATA_H
#include <stdio.h>
#include <stdlib.h>
#include "dtypes.h"
#include "drawing.h"

// [1, 2, 3, 4, 5, 6, 7]
// [1.0, 1.5, 2.0, 2.5, 3.0]

// [[10.0, 0],[0, 10.0]]


// [1,2,...]

// [[1,2],[2,3],...]

#define DP_TYPE_DEC 0
#define DP_TYPE_FRA 1
#define DP_TYPE_LLD 2
#define DP_TYPE_FFA 3
#define DP_TYPE_LST 4

typedef unsigned int index_t;

struct data_s;

typedef struct data_list_s {
	int lenght;
	struct data_s* list;
} data_list_t;

typedef union data_point_u {
	int dec;
	float frac;
	long long lld;
	double ff;
	data_list_t points;
} data_point_t;

typedef struct data_s {
	char type;
	data_point_t data;
} data_t;

//	[1,[2,3],0]

//	3
//	*[0] = {
//		DP_TYPE_DEC
//		1
//	}
//	*[1] = {
//		DP_TYPE_LST
//		{
//			2
//			*[0] = {
//				DP_TYPE_DEC
//				2
//			}
//			*[1] = {
//				DP_TYPE_DEC
//				3
//			}
//		}
//	}
//	*[2] = {
//		DP_TYPE_DEC
//		0
//	}


data_list_t newDataList(void);
int isDataListEmpty(data_list_t* list);
index_t appendDataToList(data_list_t* list, data_t* dat);
void changeDataInList(data_list_t* list, data_t* dat, index_t index);
void PlotXList_Color(display_t* dis, color3_t* clr, data_list_t* xlist);
void PlotXList(display_t* dis, data_list_t* xlist);
void PlotYList_Color(display_t* dis, color3_t* clr, data_list_t* ylist);
void PlotYList(display_t* dis, data_list_t* ylist);
void PlotXYList_Color(display_t* dis, color3_t* clr, data_list_t* xlist, data_list_t* ylist);
void PlotXYList(display_t* dis, data_list_t* xlist, data_list_t* ylist);
void PlotList_Combined_Color(display_t* dis, color3_t* clr, data_list_t* list);
void PlotList_Combined(display_t* dis, data_list_t* list);
void RePlotXList_Color(display_t* dis, color3_t* clr, data_list_t* xlist);
void RePlotXList(display_t* dis, data_list_t* xlist);
void RePlotYList_Color(display_t* dis, color3_t* clr, data_list_t* ylist);
void RePlotYList(display_t* dis, data_list_t* ylist);
void RePlotXYList_Color(display_t* dis, color3_t* clr, data_list_t* xlist, data_list_t* ylist);
void RePlotXYList(display_t* dis, data_list_t* xlist, data_list_t* ylist);
void RePlotList_Combined_Color(display_t* dis, color3_t* clr, data_list_t* list);
void RePlotList_Combined(display_t* dis, data_list_t* list);

#endif
