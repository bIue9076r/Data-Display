#ifndef DATA_C
#define DATA_C
#include "data.h"

data_list_t newDataList(void){
	return (data_list_t){0,NULL};
}

int isDataListEmpty(data_list_t* list){
	return (list->list == NULL);
}

index_t appendDataToList(data_list_t* list, data_t* dat){
	if(isDataListEmpty(list)){
		list->list = malloc(sizeof(data_t));
		list->list[0].type = dat->type;
		list->list[0].data = dat->data;
	}else{
		data_t* tmp = malloc((list->lenght + 1) * sizeof(data_t));
		for(int i = 0; i < list->lenght; i++){
			tmp[i].type = list->list[i].type;
			tmp[i].data = list->list[i].data;
		}

		tmp[list->lenght].type = dat->type;
		tmp[list->lenght].data = dat->data;
		free(list->list);
		list->list = tmp;
	}

	list->lenght++;
	return list->lenght;
}

void changeDataInList(data_list_t* list, data_t* dat, index_t index){
	if(isDataListEmpty(list)){
		printf("Error: Empty List\n");
		return;
	}

	if(list->lenght == 0){
		printf("Error: Empty List\n");
		return;
	}

	if(index >= list->lenght){
		printf("Error: Index out of List Range\n");
		return;
	}

	list->list[index].type = dat->type;
	list->list[index].data = dat->data;
	return;
}

// Plotable lists
// [1,...,10]
// [1,...,10],[10,...,20]
// [[1,...,10],[10,...,20]]

void PlotXList_Color(display_t* dis, color3_t* clr, data_list_t* xlist){
	if(isDataListEmpty(xlist)){
		printf("Error: Empty List\n");
		return;
	}

	flushColorBuffer(dis,&dis->view_color);
	int firsttime = 1;
	float xmax = 0;
	float xmin = 0;
	float xpad = dis->viewbox.x_pad;
	data_t* xl = malloc(sizeof(data_t) * xlist->lenght);
	index_t indx = 0;
	for(index_t i = 0; i < xlist->lenght; i++){
		if(xlist->list[i].type != DP_TYPE_LST){
			xl[indx] = xlist->list[i];
			indx++;
		}

		switch(xlist->list[i].type){
			case DP_TYPE_DEC:
				if(xmax < xlist->list[i].data.dec || firsttime){
					xmax = xlist->list[i].data.dec;
				}

				if(xmin > xlist->list[i].data.dec || firsttime){
					xmin = xlist->list[i].data.dec;
				}
				firsttime = 0;
			break;

			case DP_TYPE_FRA:
				if(xmax < xlist->list[i].data.frac || firsttime){
					xmax = xlist->list[i].data.frac;
				}

				if(xmin > xlist->list[i].data.frac || firsttime){
					xmin = xlist->list[i].data.frac;
				}
				firsttime = 0;
			break;

			case DP_TYPE_LLD:
				if(xmax < xlist->list[i].data.lld || firsttime){
					xmax = xlist->list[i].data.lld;
				}

				if(xmin > xlist->list[i].data.lld || firsttime){
					xmin = xlist->list[i].data.lld;
				}
				firsttime = 0;
			break;

			case DP_TYPE_FFA:
				if(xmax < xlist->list[i].data.ff || firsttime){
					xmax = xlist->list[i].data.ff;
				}

				if(xmin > xlist->list[i].data.ff || firsttime){
					xmin = xlist->list[i].data.ff;
				}
				firsttime = 0;
			break;

			default:
			break;
		}
	}

	dis->viewbox.x_start = xmin - xpad;
	dis->viewbox.x_end = xmax + xpad;

	PlotViewBoxLines(dis);

	for(index_t i = 0; i < indx; i++){
		int tx = dis->viewbox.width + 1;
		switch(xl[i].type){
			case DP_TYPE_DEC:
				tx = (int)lerp(xl[i].data.dec,xmin - xpad, xmax + xpad, 0, dis->viewbox.width);
			break;

			case DP_TYPE_FRA:
				tx = (int)lerp(xl[i].data.frac,xmin - xpad, xmax + xpad, 0, dis->viewbox.width);
			break;

			case DP_TYPE_LLD:
				tx = (int)lerp(xl[i].data.lld,xmin - xpad, xmax + xpad, 0, dis->viewbox.width);
			break;

			case DP_TYPE_FFA:
				tx = (int)lerp(xl[i].data.ff,xmin - xpad, xmax + xpad, 0, dis->viewbox.width);
			break;

			default:
			break;
		}

		// Point_Xbound(dis,clr,tx,dis->viewbox.height/2);
		for(int lx = 0; lx < dis->viewbox.line_width; lx++){
			for(int ly = 0; ly < dis->viewbox.line_width; ly++){
				int fx = tx - (dis->viewbox.line_width/2) + lx;
				int fy = dis->viewbox.height/2 - (dis->viewbox.line_width/2) + ly;

				Point_Bound(dis,clr,fx,fy);
			}
		}
	}
	free(xl);
}

void PlotXList(display_t* dis, data_list_t* xlist){
	color3_t clr = (color3_t){0,0,0};
	PlotXList_Color(dis,&clr,xlist);
}

void PlotYList_Color(display_t* dis, color3_t* clr, data_list_t* ylist){
	if(isDataListEmpty(ylist)){
		printf("Error: Empty List\n");
		return;
	}

	flushColorBuffer(dis,&dis->view_color);
	int firsttime = 1;
	float ymax = 0;
	float ymin = 0;
	float ypad = dis->viewbox.y_pad;
	data_t* yl = malloc(sizeof(data_t) * ylist->lenght);
	int indy = 0;
	for(index_t i = 0; i < ylist->lenght; i++){
		if(ylist->list[i].type != DP_TYPE_LST){
			yl[indy] = ylist->list[i];
			indy++;
		}

		switch(ylist->list[i].type){
			case DP_TYPE_DEC:
				if(ymax < ylist->list[i].data.dec || firsttime){
					ymax = ylist->list[i].data.dec;
				}

				if(ymin > ylist->list[i].data.dec || firsttime){
					ymin = ylist->list[i].data.dec;
				}
				firsttime = 0;
			break;

			case DP_TYPE_FRA:
				if(ymax < ylist->list[i].data.frac || firsttime){
					ymax = ylist->list[i].data.frac;
				}

				if(ymin > ylist->list[i].data.frac || firsttime){
					ymin = ylist->list[i].data.frac;
				}
				firsttime = 0;
			break;

			case DP_TYPE_LLD:
				if(ymax < ylist->list[i].data.lld || firsttime){
					ymax = ylist->list[i].data.lld;
				}

				if(ymin > ylist->list[i].data.lld || firsttime){
					ymin = ylist->list[i].data.lld;
				}
				firsttime = 0;
			break;

			case DP_TYPE_FFA:
				if(ymax < ylist->list[i].data.ff || firsttime){
					ymax = ylist->list[i].data.ff;
				}

				if(ymin > ylist->list[i].data.ff || firsttime){
					ymin = ylist->list[i].data.ff;
				}
				firsttime = 0;
			break;

			default:
			break;
		}
	}

	dis->viewbox.y_start = ymax + ypad;
	dis->viewbox.y_end = ymin - ypad;

	PlotViewBoxLines(dis);

	for(index_t i = 0; i < indy; i++){
		int ty = dis->viewbox.width + 1;
		switch(yl[i].type){
			case DP_TYPE_DEC:
				ty = (int)lerp(yl[i].data.dec,ymin - ypad, ymax + ypad, dis->viewbox.height, 0);
			break;

			case DP_TYPE_FRA:
				ty = (int)lerp(yl[i].data.frac,ymin - ypad, ymax + ypad, dis->viewbox.height, 0);
			break;

			case DP_TYPE_LLD:
				ty = (int)lerp(yl[i].data.lld,ymin - ypad, ymax + ypad, dis->viewbox.height, 0);
			break;

			case DP_TYPE_FFA:
				ty = (int)lerp(yl[i].data.ff,ymin - ypad, ymax + ypad, dis->viewbox.height, 0);
			break;

			default:
			break;
		}

		// Point_Ybound(dis,clr,dis->viewbox.width/2,ty);
		for(int lx = 0; lx < dis->viewbox.line_width; lx++){
			for(int ly = 0; ly < dis->viewbox.line_width; ly++){
				int fx = (dis->viewbox.width/2) - (dis->viewbox.line_width/2) + lx;
				int fy = ty - (dis->viewbox.line_width/2) + ly;

				Point_Bound(dis,clr,fx,fy);
			}
		}
	}
	free(yl);
}

void PlotYList(display_t* dis, data_list_t* ylist){
	color3_t clr = (color3_t){0,0,0};
	PlotYList_Color(dis,&clr,ylist);
}

void PlotXYList_Color(display_t* dis, color3_t* clr, data_list_t* xlist, data_list_t* ylist){
	if(isDataListEmpty(xlist)){
		printf("Error: Empty List\n");
		return;
	}

	if(isDataListEmpty(ylist)){
		printf("Error: Empty List\n");
		return;
	}

	int firsttime = 1;
	float xmax = 0;
	float xmin = 0;
	float xpad = dis->viewbox.x_pad;
	data_t* xl = malloc(sizeof(data_t) * xlist->lenght);
	index_t indx = 0;
	for(index_t i = 0; i < xlist->lenght; i++){
		if(xlist->list[i].type != DP_TYPE_LST){
			xl[indx] = xlist->list[i];
			indx++;
		}

		switch(xlist->list[i].type){
			case DP_TYPE_DEC:
				if(xmax < xlist->list[i].data.dec || firsttime){
					xmax = xlist->list[i].data.dec;
				}

				if(xmin > xlist->list[i].data.dec || firsttime){
					xmin = xlist->list[i].data.dec;
				}
				firsttime = 0;
			break;

			case DP_TYPE_FRA:
				if(xmax < xlist->list[i].data.frac || firsttime){
					xmax = xlist->list[i].data.frac;
				}

				if(xmin > xlist->list[i].data.frac || firsttime){
					xmin = xlist->list[i].data.frac;
				}
				firsttime = 0;
			break;

			case DP_TYPE_LLD:
				if(xmax < xlist->list[i].data.lld || firsttime){
					xmax = xlist->list[i].data.lld;
				}

				if(xmin > xlist->list[i].data.lld || firsttime){
					xmin = xlist->list[i].data.lld;
				}
				firsttime = 0;
			break;

			case DP_TYPE_FFA:
				if(xmax < xlist->list[i].data.ff || firsttime){
					xmax = xlist->list[i].data.ff;
				}

				if(xmin > xlist->list[i].data.ff || firsttime){
					xmin = xlist->list[i].data.ff;
				}
				firsttime = 0;
			break;

			default:
			break;
		}
	}

	dis->viewbox.x_start = xmin - xpad;
	dis->viewbox.x_end = xmax + xpad;

	firsttime = 1;
	float ymax = 0;
	float ymin = 0;
	float ypad = dis->viewbox.y_pad;
	data_t* yl = malloc(sizeof(data_t) * ylist->lenght);
	int indy = 0;
	for(index_t i = 0; i < ylist->lenght; i++){
		if(ylist->list[i].type != DP_TYPE_LST){
			yl[indy] = ylist->list[i];
			indy++;
		}

		switch(ylist->list[i].type){
			case DP_TYPE_DEC:
				if(ymax < ylist->list[i].data.dec || firsttime){
					ymax = ylist->list[i].data.dec;
				}

				if(ymin > ylist->list[i].data.dec || firsttime){
					ymin = ylist->list[i].data.dec;
				}
				firsttime = 0;
			break;

			case DP_TYPE_FRA:
				if(ymax < ylist->list[i].data.frac || firsttime){
					ymax = ylist->list[i].data.frac;
				}

				if(ymin > ylist->list[i].data.frac || firsttime){
					ymin = ylist->list[i].data.frac;
				}
				firsttime = 0;
			break;

			case DP_TYPE_LLD:
				if(ymax < ylist->list[i].data.lld || firsttime){
					ymax = ylist->list[i].data.lld;
				}

				if(ymin > ylist->list[i].data.lld || firsttime){
					ymin = ylist->list[i].data.lld;
				}
				firsttime = 0;
			break;

			case DP_TYPE_FFA:
				if(ymax < ylist->list[i].data.ff || firsttime){
					ymax = ylist->list[i].data.ff;
				}

				if(ymin > ylist->list[i].data.ff || firsttime){
					ymin = ylist->list[i].data.ff;
				}
				firsttime = 0;
			break;

			default:
			break;
		}
	}

	dis->viewbox.y_start = ymax + ypad;
	dis->viewbox.y_end = ymin - ypad;

	PlotViewBoxLines(dis);

	index_t smlt = (indy > indx)?(indx):(indy);
	for(index_t i = 0; i < smlt; i++){
		int ty = dis->viewbox.width + 1;
		switch(yl[i].type){
			case DP_TYPE_DEC:
				ty = (int)lerp(yl[i].data.dec,ymin - ypad, ymax + ypad, dis->viewbox.height, 0);
			break;

			case DP_TYPE_FRA:
				ty = (int)lerp(yl[i].data.frac,ymin - ypad, ymax + ypad, dis->viewbox.height, 0);
			break;

			case DP_TYPE_LLD:
				ty = (int)lerp(yl[i].data.lld,ymin - ypad, ymax + ypad, dis->viewbox.height, 0);
			break;

			case DP_TYPE_FFA:
				ty = (int)lerp(yl[i].data.ff,ymin - ypad, ymax + ypad, dis->viewbox.height, 0);
			break;

			default:
			break;
		}

		int tx = dis->viewbox.width + 1;
		switch(xl[i].type){
			case DP_TYPE_DEC:
				tx = (int)lerp(xl[i].data.dec,xmin - xpad, xmax + xpad, 0, dis->viewbox.width);
			break;

			case DP_TYPE_FRA:
				tx = (int)lerp(xl[i].data.frac,xmin - xpad, xmax + xpad, 0, dis->viewbox.width);
			break;

			case DP_TYPE_LLD:
				tx = (int)lerp(xl[i].data.lld,xmin - xpad, xmax + xpad, 0, dis->viewbox.width);
			break;

			case DP_TYPE_FFA:
				tx = (int)lerp(xl[i].data.ff,xmin - xpad, xmax + xpad, 0, dis->viewbox.width);
			break;

			default:
			break;
		}

		// Point_Bound(dis,clr,tx,ty);
		for(int lx = 0; lx < dis->viewbox.line_width; lx++){
			for(int ly = 0; ly < dis->viewbox.line_width; ly++){
				int fx = tx - (dis->viewbox.line_width/2) + lx;
				int fy = ty - (dis->viewbox.line_width/2) + ly;

				Point_Bound(dis,clr,fx,fy);
			}
		}
	}
	free(xl);
	free(yl);
}

void PlotXYList(display_t* dis, data_list_t* xlist, data_list_t* ylist){
	color3_t clr = (color3_t){0,0,0};
	PlotXYList_Color(dis,&clr,xlist,ylist);
}

void PlotList_Combined_Color(display_t* dis, color3_t* clr, data_list_t* list){
	if(isDataListEmpty(list)){
		printf("Error: Empty List\n");
		return;
	}

	data_list_t xlist = {0,NULL};
	data_list_t ylist = {0,NULL};

	for(index_t i = 0; i < list->lenght; i++){
		if(!isDataListEmpty(&xlist) && isDataListEmpty(&ylist)){
			if(list->list[i].type == DP_TYPE_LST){
				ylist = list->list[i].data.points;
			}
		}

		if(isDataListEmpty(&xlist)){
			if(list->list[i].type == DP_TYPE_LST){
				xlist = list->list[i].data.points;
			}
		}
	}

	if(!isDataListEmpty(&xlist)){
		if(isDataListEmpty(&ylist)){
			PlotXList_Color(dis,clr,&xlist);
		}else{
			PlotXYList_Color(dis,clr,&xlist,&ylist);
		}
	}else{
		printf("Error: Empty Xlist\n");
	}
}

void PlotList_Combined(display_t* dis, data_list_t* list){
	color3_t clr = (color3_t){0,0,0};
	PlotList_Combined_Color(dis,&clr,list);
}

void RePlotXList_Color(display_t* dis, color3_t* clr, data_list_t* xlist){
	if(isDataListEmpty(xlist)){
		printf("Error: Empty List\n");
		return;
	}

	data_t* xl = malloc(sizeof(data_t) * xlist->lenght);
	index_t indx = 0;
	for(index_t i = 0; i < xlist->lenght; i++){
		if(xlist->list[i].type != DP_TYPE_LST){
			xl[indx] = xlist->list[i];
			indx++;
		}
	}

	for(index_t i = 0; i < indx; i++){
		int tx = dis->viewbox.width + 1;
		switch(xl[i].type){
			case DP_TYPE_DEC:
				tx = (int)lerp(xl[i].data.dec, dis->viewbox.x_start, dis->viewbox.x_end, 0, dis->viewbox.width);
			break;

			case DP_TYPE_FRA:
				tx = (int)lerp(xl[i].data.frac, dis->viewbox.x_start, dis->viewbox.x_end, 0, dis->viewbox.width);
			break;

			case DP_TYPE_LLD:
				tx = (int)lerp(xl[i].data.lld, dis->viewbox.x_start, dis->viewbox.x_end, 0, dis->viewbox.width);
			break;

			case DP_TYPE_FFA:
				tx = (int)lerp(xl[i].data.ff, dis->viewbox.x_start, dis->viewbox.x_end, 0, dis->viewbox.width);
			break;

			default:
			break;
		}

		int ty = (int)lerp(0,dis->viewbox.y_end,dis->viewbox.y_start,dis->viewbox.height,0);
		// Point_Bound(dis,clr,tx,ty);
		for(int lx = 0; lx < dis->viewbox.line_width; lx++){
			for(int ly = 0; ly < dis->viewbox.line_width; ly++){
				int fx = tx - (dis->viewbox.line_width/2) + lx;
				int fy = ty - (dis->viewbox.line_width/2) + ly;

				Point_Bound(dis,clr,fx,fy);
			}
		}
	}
	free(xl);
}

void RePlotXList(display_t* dis, data_list_t* xlist){
	color3_t clr = (color3_t){0,0,0};
	RePlotXList_Color(dis,&clr,xlist);
}

void RePlotYList_Color(display_t* dis, color3_t* clr, data_list_t* ylist){
	if(isDataListEmpty(ylist)){
		printf("Error: Empty List\n");
		return;
	}

	data_t* yl = malloc(sizeof(data_t) * ylist->lenght);
	int indy = 0;
	for(index_t i = 0; i < ylist->lenght; i++){
		if(ylist->list[i].type != DP_TYPE_LST){
			yl[indy] = ylist->list[i];
			indy++;
		}
	}

	for(index_t i = 0; i < indy; i++){
		int ty = dis->viewbox.width + 1;
		switch(yl[i].type){
			case DP_TYPE_DEC:
				ty = (int)lerp(yl[i].data.dec, dis->viewbox.y_end, dis->viewbox.y_start, dis->viewbox.height, 0);
			break;

			case DP_TYPE_FRA:
				ty = (int)lerp(yl[i].data.frac, dis->viewbox.y_end, dis->viewbox.y_start, dis->viewbox.height, 0);
			break;

			case DP_TYPE_LLD:
				ty = (int)lerp(yl[i].data.lld, dis->viewbox.y_end, dis->viewbox.y_start, dis->viewbox.height, 0);
			break;

			case DP_TYPE_FFA:
				ty = (int)lerp(yl[i].data.ff, dis->viewbox.y_end, dis->viewbox.y_start, dis->viewbox.height, 0);
			break;

			default:
			break;
		}

		int tx = (int)lerp(0,dis->viewbox.x_start,dis->viewbox.x_end,0,dis->viewbox.width);
		// Point_Bound(dis,clr,tx,ty);
		for(int lx = 0; lx < dis->viewbox.line_width; lx++){
			for(int ly = 0; ly < dis->viewbox.line_width; ly++){
				int fx = tx - (dis->viewbox.line_width/2) + lx;
				int fy = ty - (dis->viewbox.line_width/2) + ly;

				Point_Bound(dis,clr,fx,fy);
			}
		}
	}
	free(yl);
}

void RePlotYList(display_t* dis, data_list_t* ylist){
	color3_t clr = (color3_t){0,0,0};
	RePlotYList_Color(dis,&clr,ylist);
}

void RePlotXYList_Color(display_t* dis, color3_t* clr, data_list_t* xlist, data_list_t* ylist){
	if(isDataListEmpty(xlist)){
		printf("Error: Empty List\n");
		return;
	}

	if(isDataListEmpty(ylist)){
		printf("Error: Empty List\n");
		return;
	}

	data_t* xl = malloc(sizeof(data_t) * xlist->lenght);
	index_t indx = 0;
	for(index_t i = 0; i < xlist->lenght; i++){
		if(xlist->list[i].type != DP_TYPE_LST){
			xl[indx] = xlist->list[i];
			indx++;
		}
	}

	data_t* yl = malloc(sizeof(data_t) * ylist->lenght);
	int indy = 0;
	for(index_t i = 0; i < ylist->lenght; i++){
		if(ylist->list[i].type != DP_TYPE_LST){
			yl[indy] = ylist->list[i];
			indy++;
		}
	}

	index_t smlt = (indy > indx)?(indx):(indy);
	for(index_t i = 0; i < smlt; i++){
		int ty = dis->viewbox.width + 1;
		switch(yl[i].type){
			case DP_TYPE_DEC:
				ty = (int)lerp(yl[i].data.dec, dis->viewbox.y_end, dis->viewbox.y_start, dis->viewbox.height, 0);
			break;

			case DP_TYPE_FRA:
				ty = (int)lerp(yl[i].data.frac, dis->viewbox.y_end, dis->viewbox.y_start, dis->viewbox.height, 0);
			break;

			case DP_TYPE_LLD:
				ty = (int)lerp(yl[i].data.lld, dis->viewbox.y_end, dis->viewbox.y_start, dis->viewbox.height, 0);
			break;

			case DP_TYPE_FFA:
				ty = (int)lerp(yl[i].data.ff, dis->viewbox.y_end, dis->viewbox.y_start, dis->viewbox.height, 0);
			break;

			default:
			break;
		}

		int tx = dis->viewbox.width + 1;
		switch(xl[i].type){
			case DP_TYPE_DEC:
				tx = (int)lerp(xl[i].data.dec, dis->viewbox.x_start, dis->viewbox.x_end, 0, dis->viewbox.width);
			break;

			case DP_TYPE_FRA:
				tx = (int)lerp(xl[i].data.frac, dis->viewbox.x_start, dis->viewbox.x_end, 0, dis->viewbox.width);
			break;

			case DP_TYPE_LLD:
				tx = (int)lerp(xl[i].data.lld, dis->viewbox.x_start, dis->viewbox.x_end, 0, dis->viewbox.width);
			break;

			case DP_TYPE_FFA:
				tx = (int)lerp(xl[i].data.ff, dis->viewbox.x_start, dis->viewbox.x_end, 0, dis->viewbox.width);
			break;

			default:
			break;
		}

		// Point_Bound(dis,clr,tx,ty);
		for(int lx = 0; lx < dis->viewbox.line_width; lx++){
			for(int ly = 0; ly < dis->viewbox.line_width; ly++){
				int fx = tx - (dis->viewbox.line_width/2) + lx;
				int fy = ty - (dis->viewbox.line_width/2) + ly;

				Point_Bound(dis,clr,fx,fy);
			}
		}
	}
	free(xl);
	free(yl);
}

void RePlotXYList(display_t* dis, data_list_t* xlist, data_list_t* ylist){
	color3_t clr = (color3_t){0,0,0};
	RePlotXYList_Color(dis,&clr,xlist,ylist);
}

void RePlotList_Combined_Color(display_t* dis, color3_t* clr, data_list_t* list){
	if(isDataListEmpty(list)){
		printf("Error: Empty List\n");
		return;
	}

	data_list_t xlist = {0,NULL};
	data_list_t ylist = {0,NULL};

	for(index_t i = 0; i < list->lenght; i++){
		if(!isDataListEmpty(&xlist) && isDataListEmpty(&ylist)){
			if(list->list[i].type == DP_TYPE_LST){
				ylist = list->list[i].data.points;
			}
		}

		if(isDataListEmpty(&xlist)){
			if(list->list[i].type == DP_TYPE_LST){
				xlist = list->list[i].data.points;
			}
		}
	}

	if(!isDataListEmpty(&xlist)){
		if(isDataListEmpty(&ylist)){
			RePlotXList_Color(dis,clr,&xlist);
		}else{
			RePlotXYList_Color(dis,clr,&xlist,&ylist);
		}
	}else{
		printf("Error: Empty Xlist\n");
	}
}

void RePlotList_Combined(display_t* dis, data_list_t* list){
	color3_t clr = (color3_t){0,0,0};
	RePlotList_Combined_Color(dis,&clr,list);
}

#endif
