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
	a->len = 0;
	for(int i = 0; str[i] != 0; i++){
		a->len = i + 1;
	}
}

void str_tcopy(str_t* a, str_t* b){
	if(!a){
		return;
	}

	if(!b){
		return;
	}

	b->str = a->str;
	b->len = a->len;
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
			if(index + 1 <= len){
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

int str_tsubin(str_t* src, str_t* des, int included, char open, char close){
	if(!src){
		return 0;
	}

	if(!des){
		return 0;
	}

	int Sub = 0;
	if(included){
		Sub = 1;
	}

	int len = src->len;
	int index = 0;
	while(index < len){
		if(src->str[index] == open){
			Sub++;
		}

		if(src->str[index] == close){
			if(Sub == 1){
				if(index + 1 <= len){
					des->len = (len - index - 1);
					des->str = (src->str + index + 1);
				}else{
					des->len = 0;
					des->str = NULL;
				}
				break;
			}else{
				Sub--;
			}
		}

		index++;
		src->len = index;
	}

	return index;
}

int str_tsub(str_t* src, str_t* des, char open, char close){
	return str_tsubin(src,des,1,open,close);
}

#ifdef STRLIB_MATH
// string to fuction

float fn_log(float x){
	if(x <= 0.0){
		return 0.0;
	}
	return log10(x);
}

float fn_ln(float x){
	if(x <= 0.0){
		return 0.0;
	}
	return log(x);
}

float fn_sin(float x){
	return sin(x);
}

float fn_cos(float x){
	return cos(x);
}

float fn_tan(float x){
	return tan(x);
}

float fn_arctan(float x){
	return atan(x);
}

float fn_arcsin(float x){
	if(fabs(x) > 1.0){
		x = copysign(1.0,x)*(x/x);
	}
	return asin(x);
}

float fn_arccos(float x){
	if(fabs(x) > 1.0){
		x = copysign(1.0,x)*(x/x);
	}
	return acos(x);
}

float fn_floor(float x){
	return floor(x);
}

float fn_ceil(float x){
	return ceil(x);
}

float fn_abs(float x){
	return fabs(x);
}

float fn_sqrt(float x){
	if(x <= 0.0){
		return 0.0;
	}

	return sqrt(x);
}

float funcOperation(int type, float a, floatFunc_t b){
	switch(type){
		case FUNC_OP_ADD:
		case '+':
			return a + b.f;
		case FUNC_OP_SUB:
		case '-':
			return a - b.f;
		case FUNC_OP_MUL:
		case '*':
			return a * b.f;
		case FUNC_OP_DIV:
		case '/':
			if(abs(b.f) < 0.001){
				b.f = b.f + signbit(b.f)*0.001;
			}
			return a / b.f;
		case FUNC_OP_EXP:
		case '^':
			return pow(a,b.f);
		case FUNC_OP_FUNC:
			return b.func(a);
	}
}

int isOperation(char c){
	return (c == '+') || (c == '-') || (c == '*') || (c == '/') || (c == '^');
}

float thingf(str_t* func){
	return str_ttof(func);
}

float str_tfunc(str_t* func){
	// 2^2 + 4
	int len = func->len;
	char fstr[len];
	str_t f;
	int ind = 0;
	for(int i = 0; i < len; i++){
		if(!(func->str[i] == ' ' || func->str[i] == '\t')){
			fstr[ind++] = func->str[i];
			char c = func->str[i];
			if(c >= 'A' && c <= 'Z'){
				fstr[ind - 1] = c + 32;
			}
		}
	}
	f.len = ind;
	f.str = fstr;
	len = ind;

	// [Number](variable){operation}[Number](variable)  {operation or end}
	// [thing]{op}[thing]
	// 2x^2+4x
	// [2x]^[2]+[4x]

	char str[len];
	int str_len = 0;
	for(int i = 0; i < len; i++){ str[i] = 0;}
	
	int i = 0;
	float r = 0.0;
	float sub = 0.0;
	int op = 0;
	int first = 1;

	while(i < len){
		char c = f.str[i];
		if(!isOperation(c)){
			str[str_len++] = c;
			if(c == '('){
				str[--str_len] = 0;
				str_t fcopy = {.len=f.len-i-1,.str=f.str+i+1};
				str_t substr = {.len=0,.str=NULL};
				int index = str_tsub(&fcopy,&substr,'(',')');

				sub = str_tfunc(&fcopy);

				// do something if str before is a func or a var
				if(str_len){
					// func or var
					str_t s = {.len=str_len,.str=str};
					if(str_tequ(&s,&(str_t){.str="log",.len=3})){
						sub = funcOperation(FUNC_OP_FUNC,sub,(floatFunc_t){.func=&fn_log});
						goto fn_skip;
					}
					if(str_tequ(&s,&(str_t){.str="ln",.len=2})){
						sub = funcOperation(FUNC_OP_FUNC,sub,(floatFunc_t){.func=&fn_ln});
						goto fn_skip;
					}
					if(str_tequ(&s,&(str_t){.str="sin",.len=3})){
						sub = funcOperation(FUNC_OP_FUNC,sub,(floatFunc_t){.func=&fn_sin});
						goto fn_skip;
					}
					if(str_tequ(&s,&(str_t){.str="cos",.len=3})){
						sub = funcOperation(FUNC_OP_FUNC,sub,(floatFunc_t){.func=&fn_cos});
						goto fn_skip;
					}
					if(str_tequ(&s,&(str_t){.str="tan",.len=3})){
						sub = funcOperation(FUNC_OP_FUNC,sub,(floatFunc_t){.func=&fn_tan});
						goto fn_skip;
					}
					if(str_tequ(&s,&(str_t){.str="arctan",.len=6})){
						sub = funcOperation(FUNC_OP_FUNC,sub,(floatFunc_t){.func=&fn_arctan});
						goto fn_skip;
					}
					if(str_tequ(&s,&(str_t){.str="arcsin",.len=6})){
						sub = funcOperation(FUNC_OP_FUNC,sub,(floatFunc_t){.func=&fn_arcsin});
						goto fn_skip;
					}
					if(str_tequ(&s,&(str_t){.str="arccos",.len=6})){
						sub = funcOperation(FUNC_OP_FUNC,sub,(floatFunc_t){.func=&fn_arccos});
						goto fn_skip;
					}
					if(str_tequ(&s,&(str_t){.str="floor",.len=5})){
						sub = funcOperation(FUNC_OP_FUNC,sub,(floatFunc_t){.func=&fn_floor});
						goto fn_skip;
					}
					if(str_tequ(&s,&(str_t){.str="ceil",.len=4})){
						sub = funcOperation(FUNC_OP_FUNC,sub,(floatFunc_t){.func=&fn_ceil});
						goto fn_skip;
					}
					if(str_tequ(&s,&(str_t){.str="abs",.len=3})){
						sub = funcOperation(FUNC_OP_FUNC,sub,(floatFunc_t){.func=&fn_abs});
						goto fn_skip;
					}
					if(str_tequ(&s,&(str_t){.str="sqrt",.len=4})){
						sub = funcOperation(FUNC_OP_FUNC,sub,(floatFunc_t){.func=&fn_sqrt});
						goto fn_skip;
					}

					float fs = thingf(&s);
					sub = funcOperation('*',sub,(floatFunc_t){.f = fs});

					fn_skip:
					if(first){
						r = sub;
					}else{
						r = funcOperation(op,r,(floatFunc_t){.f = sub});
					}
					for(int j = 0; j < str_len; j++){ str[j] = 0;}
					str_len = 0;
				}else{
					if(first){
						r = sub;
					}else{
						r = funcOperation(op,r,(floatFunc_t){.f = sub});
					}
				}
				first = 0;
				i = i + index;
			}

			if(c == ')'){
				str[--str_len] = 0;
			}
		}else{
			if(str_len){
				str_t s = {.len=str_len,.str=str};

				float fs = thingf(&s);
				if(first){
					r = fs;
				}else{
					r = funcOperation(op,r,(floatFunc_t){.f = fs});
				}

				for(int j = 0; j < str_len; j++){ str[j] = 0;}
				str_len = 0;
			}
			first = 0;
			op = c;
		}
		i++;
	}

	if(str_len){
		str_t s = {.len=str_len,.str=str};
		float fs = thingf(&s);
		if(first){
			r = fs;
		}else{
			r = funcOperation(op,r,(floatFunc_t){.f = fs});
		}
	}

	return r;
}

int str_tfunc_i(str_t* func){
	return (int)str_tfunc(func);
}

#endif
#endif
