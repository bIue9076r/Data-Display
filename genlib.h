#ifndef GENLIB_H
#define GENLIB_H

int i_abs(int x);
int i_sign(int x);
float f_abs(float x);
float f_sign(float x);
float f_mod(float x, float d);
int i_max(int x, int y);
float f_max(float x, float y);
int i_min(int x, int y);
float f_min(float x, float y);
float lerp(float t, float r1s, float r1e, float r2s, float r2e);

#endif