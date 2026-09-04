#ifndef VSTRFUNC_C
#define VSTRFUNC_C
#include "vstrfunc.h"

float vthingf(str_t* func){
	int len = func->len;
	float r = 0;
	char str[len];
	int str_len = 0;
	for(int i = 0; i < len; i++){ str[i] = 0;}
	int i = 0;
	int number = 1;
	int noNum = 1;
	
	while(i < len){
		char c = func->str[i];
		if(number){
			if(!((c >= '0' && c <= '9') || (c == '.'))){
				str_t s;
				str_tnew(&s,str);
				r = str_ttof(&s);
				for(int i = 0; i < str_len; i++){
					str[i] = 0;
				}
				str_len = 0;
				number = 0;
				break;
			}
			str[str_len++] = c;
			noNum = 0;
		}
		i++;
	}

	if(number){
		str_t s;
		str_tnew(&s,str);
		r = str_ttof(&s);
		return r;
	}else{
		str_t s = {.str=func->str+i,.len=func->len-i};
		Var_t v = localGet(&gVars,&s);
		if(localExists(&gVars,&s)){
			if(noNum){
				r = 1.0;
			}
			r = r * v.type_float;
		}
		return r;
	}
}

float vstr_tfunc(str_t* func){
	// 2x^2 + 4x
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

				sub = vstr_tfunc(&fcopy);

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

					float fs = vthingf(&s);
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

				float fs = vthingf(&s);
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
		float fs = vthingf(&s);
		if(first){
			r = fs;
		}else{
			r = funcOperation(op,r,(floatFunc_t){.f = fs});
		}
	}

	return r;
}

int vstr_tfunc_i(str_t* func){
	return (int)vstr_tfunc(func);
}
#endif
