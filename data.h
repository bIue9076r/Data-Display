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

#endif
