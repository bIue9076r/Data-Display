#ifndef LVARS_H
#define LVARS_H
#include <stdlib.h>
#include "strlib.h"

#define VAR_TYPE_FLEX	0
#define VAR_TYPE_INT	1
#define VAR_TYPE_FLOAT	2
#define VAR_TYPE_LIST	3
#define VAR_TYPE_FUNCT	4

typedef union Var_u {
	int	type_int;
	float type_float;
	void* type_list;
	str_t type_func;
} Var_t;

typedef struct localVar_s {
	str_t name;
	int type;
	Var_t v;	
} localVar_t;

typedef struct localVars_s {
	int len;
	localVar_t* vars;
} localVars_t;

void updateVar(localVar_t* var, int type, void* v);
void newVarsList(localVars_t* list);
int localExists(localVars_t* list, str_t* n);
void localNew(localVars_t* list, str_t* n, int type, void* v);
void localUpdate(localVars_t* list, str_t* n, int type, void* v);
void localSet(localVars_t* list, str_t* n, int type, void* v);
Var_t localGet(localVars_t* list, str_t* n);

#endif
