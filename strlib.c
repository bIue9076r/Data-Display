#ifndef STRLIB_C
#define STRLIB_C
#include "strlib.h"

int valChar(char c){
	return (c == '\t' || (c >= ' ' && c <= '~'));
}

void str_tnew(str_t* a, char* str){
	if(!a){
		return;
	}

	if(!str){
		a->str = 0;
		a->len = 0;
	}

	a->str = str;
	for(int i = 0; str[i] != 0; i++){
		a->len = i + 1;
	}
}

int str_tequ(str_t* a, str_t* b){
	if(a->len != b->len){
		return 0;
	}

	if(!a->str || !b->str){
		return 0;
	}

	for(int i = 0; i < a->len; i++){
		if(a->str[i] != b->str[i]){
			return 0;
		}
	}

	return 1;
}

int str_ttoi(str_t* a){
	if(!a){
		return -1;
	}

	if(a->len == 0){
		return 0;
	}

	int r = 0;
	int sign = 1;
	int ini = 0;
	if(a->str[0] == '-'){
		sign = -1;
		ini = 1;
	}

	for(int i = ini; i < a->len; i++){
		if('0' <= a->str[i] && a->str[i] <= '9'){
			r = r * 10;
			r = r + (int)(a->str[i] - '0');
		}
	}

	return sign * r;
}

long long int str_ttoll(str_t* a){
	if(!a){
		return -1;
	}

	if(a->len == 0){
		return 0;
	}

	long long int r = 0;
	long long int sign = 1;
	int ini = 0;
	if(a->str[0] == '-'){
		sign = -1;
		ini = 1;
	}

	for(int i = ini; i < a->len; i++){
		if('0' <= a->str[i] && a->str[i] <= '9'){
			r = r * 10;
			r = r + (long long int)(a->str[i] - '0');
		}
	}

	return sign * r;
}

float str_ttof(str_t* a){
	if(!a){
		return -1.0;
	}

	if(a->len == 0){
		return 0.0;
	}

	float r = 0;
	float sign = 1;
	int ini = 0;
	if(a->str[0] == '-'){
		sign = -1.0;
		ini = 1;
	}

	int ndp = 1;
	int fac = 1;

	for(int i = ini; i < a->len; i++){
		if(ndp){
			if('0' <= a->str[i] && a->str[i] <= '9'){
				r = r * 10;
				r = r + (a->str[i] - '0');
			}
			if(a->str[i] == '.'){
				ndp = 0;
			}
		}else{
			if('0' <= a->str[i] && a->str[i] <= '9'){
				float t = (float)(a->str[i] - '0');
				for(int i = 0; i < fac; i++){
					t = t / 10;
				}
				fac++;
				r = r + t;
			}
		}
	}

	return sign * r;
}

double str_ttod(str_t* a){
	if(!a){
		return -1.0;
	}

	if(a->len == 0){
		return 0.0;
	}

	double r = 0;
	double sign = 1;
	int ini = 0;
	if(a->str[0] == '-'){
		sign = -1.0;
		ini = 1;
	}

	int ndp = 1;
	int fac = 1;

	for(int i = ini; i < a->len; i++){
		if(ndp){
			if('0' <= a->str[i] && a->str[i] <= '9'){
				r = r * 10;
				r = r + (a->str[i] - '0');
			}
			if(a->str[i] == '.'){
				ndp = 0;
			}
		}else{
			if('0' <= a->str[i] && a->str[i] <= '9'){
				double t = (double)(a->str[i] - '0');
				for(int i = 0; i < fac; i++){
					t = t / 10;
				}
				fac++;
				r = r + t;
			}
		}
	}

	return sign * r;
}

void str_tprint(str_t* a){
	if(!a){
		return;
	}

	if(!a->str){
		return;
	}

	if(a->len == 0){
		return;
	}

	for(int i = 0; i < a->len; i++){
		printf("%c",a->str[i]);
	}
}

void str_tprintln(str_t* a){
	if(!a){
		return;
	}

	if(!a->str){
		return;
	}

	if(a->len == 0){
		return;
	}

	for(int i = 0; i < a->len; i++){
		printf("%c",a->str[i]);
	}
	printf("\n");
}

int str_tsplitde(str_t* src, str_t* des, char del){
	if(!src){
		return 0;
	}

	if(!des){
		return 0;
	}

	int len = src->len;
	int index = 0;
	while(index < len){
		if(src->str[index] == del){
			if(index + 1 < len){
				des->len = (len - index - 1);
				des->str = (src->str + index + 1);
			}else{
				des->len = 0;
				des->str = NULL;
			}
			break;
		}

		index++;
		src->len = index;
	}

	return index;
}

int str_tsplit(str_t* src, str_t* des){
	return str_tsplitde(src,des,' ');
}

#endif
