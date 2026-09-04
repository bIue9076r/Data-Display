#ifndef STRLIB_H
#define STRLIB_H
#include <stdio.h>

typedef struct str_s {
	char* str;
	int len;
} str_t;

int valChar(char c);
void str_tnew(str_t* a, char* str);
void str_tcopy(str_t* a, str_t* b);
int str_tequ(str_t* a, str_t* b);
int str_ttoi(str_t* a);
long long int str_ttoll(str_t* a);
float str_ttof(str_t* a);
double str_ttod(str_t* a);
void str_tprint(str_t* a);
void str_tprintln(str_t* a);
int str_tsplitde(str_t* src, str_t* des, char del);
int str_tsplit(str_t* src, str_t* des);
int str_tsubin(str_t* src, str_t* des, int included, char open, char close);
int str_tsub(str_t* src, str_t* des, char open, char close);

#define STRLIB_MATH
#ifdef STRLIB_MATH
#include <math.h>

#define FUNC_OP_ADD	0
#define FUNC_OP_SUB	1
#define FUNC_OP_MUL	2
#define FUNC_OP_DIV	3
#define FUNC_OP_EXP	4
#define FUNC_OP_FUNC	5
// (x^ln5 + 3x)/2
// log()
// ln()
// sin()
// cos()
// tan()
// arctan()
// arcsin()
// arccos()
// floor()
// ceil()
// abs()
// sqrt()

// value reading until (
// if no value then sub loop until next )
// if value is a func then find ) and evaluate sub loop
// if not then implict multiplication and sub loop
// after all this if operation
// break of after and evaluate
typedef union floatFunc_u {
	float f;
	float (*func)(float x);
} floatFunc_t;

float fn_log(float x);
float fn_ln(float x);
float fn_sin(float x);
float fn_cos(float x);
float fn_tan(float x);
float fn_arctan(float x);
float fn_arcsin(float x);
float fn_arccos(float x);
float fn_floor(float x);
float fn_ceil(float x);
float fn_abs(float x);
float fn_sqrt(float x);

float funcOperation(int type, float a, floatFunc_t b);
int isOperation(char c);
float thingf(str_t* func);
float str_tfunc(str_t* func);
int str_tfunc_i(str_t* func);
#endif
#endif
