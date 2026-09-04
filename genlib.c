#ifndef GENLIB_C
#define GENLIB_C
#include "genlib.h"

int i_abs(int x){
	return (x < 0)?(-x):(x);
}

int i_sign(int x){
	if(x > 0){
		return 1;
	}

	if(x < 0){
		return -1;
	}

	return 0;
}

float f_abs(float x){
	return (x < 0.0)?(-x):(x);
}

float f_sign(float x){
	if(x > 0.0){
		return 1.0;
	}

	if(x < 0.0){
		return -1.0;
	}

	return 0.0;
}

float f_mod(float x, float d){
	float r = x - ((int)(x/d) * d);
	return r;
}

int i_max(int x, int y){
	return (x > y)?(x):(y);
}

float f_max(float x, float y){
	return (x > y)?(x):(y);
}

int i_min(int x, int y){
	return (x < y)?(x):(y);
}

float f_min(float x, float y){
	return (x < y)?(x):(y);
}

// (r1s,r1e) -> (r2s,r2e)
// (r1s,r2s) (r1e,r2e)

float lerp(float t, float r1s, float r1e, float r2s, float r2e){
	if(f_abs(r1e - r1s) < 0.0001){
		return r1e;
	}

	return ((r2e - r2s)*(t - r1s))/(r1e - r1s) + r2s;
}

#endif