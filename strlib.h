#ifndef STRLIB_H
#define STRLIB_H
#include <stdio.h>

typedef struct str_s {
	char* str;
	int len;
} str_t;

int valChar(char c);
void str_tnew(str_t* a, char* str);
int str_tequ(str_t* a, str_t* b);
int str_ttoi(str_t* a);
long long int str_ttoll(str_t* a);
float str_ttof(str_t* a);
double str_ttod(str_t* a);
void str_tprint(str_t* a);

#endif
