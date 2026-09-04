#ifndef GDECLARE_H
#define GDECLARE_H
#include "display.h"
#include "strlib.h"
#include "lvars.h"

#define VERSION "0.0"

extern display_t gDisplay;
extern int gRunning;
extern int gWitdh;
extern int gHeight;
extern localVars_t gVars;
extern str_t gFunct;

extern str_t arg_strings[];
extern str_t commands[];

void help(void);
void version(void);
int eval(str_t* input);

#endif
