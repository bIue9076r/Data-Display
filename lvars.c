#ifndef LVARS_C
#define LVARS_C
#include "lvars.h"

void updateVar(localVar_t* var, int type, void* v){
	switch(type){
		case VAR_TYPE_INT:
			if(v){
				var->v.type_int = *((int*)v);
			}
		break;

		case VAR_TYPE_FLOAT:
			if(v){
				var->v.type_float = *((float*)v);
			}
		break;

		case VAR_TYPE_FUNCT:
			if(v){
				str_tcopy((str_t*)v,&var->v.type_func);
			}
		break;

		case VAR_TYPE_LIST:
			if(v){
				var->v.type_list = v;
			}
		break;

		case VAR_TYPE_FLEX:
		default:
			var->type = VAR_TYPE_FLEX;
			if(v){
				var->v.type_int = *((int*)v);
			}
		break;
	}
}

void newVarsList(localVars_t* list){
	list->len = 0;
	list->vars = malloc(sizeof(localVar_t));
}

int localExists(localVars_t* list, str_t* n){
	for(int i = 0; i < list->len; i++){
		if(str_tequ(n,&list->vars[i].name)){
			return 1;
		}
	}
	return 0;
}

void localNew(localVars_t* list, str_t* n, int type, void* v){
	if(!list){
		return;
	}

	if(!n){
		return;
	}

	localVar_t V;
	str_tcopy(n,&V.name);
	V.type = type;
	V.v.type_int = 0;
	updateVar(&V,type,v);

	localVar_t* tl = malloc(sizeof(localVar_t) * (list->len + 1));
	for(int i = 0; i < list->len; i++){
		str_tcopy(&list->vars[i].name,&tl[i].name);
		tl[i].type = list->vars[i].type;
		switch(tl[i].type){
			case VAR_TYPE_FLOAT:
				tl[i].v.type_float = list->vars[i].v.type_float;
			break;

			case VAR_TYPE_FUNCT:
				tl[i].v.type_func = list->vars[i].v.type_func;
			break;

			case VAR_TYPE_LIST:
				tl[i].v.type_list = list->vars[i].v.type_list;
			break;

			case VAR_TYPE_INT:
			case VAR_TYPE_FLEX:
			default:
				tl[i].v.type_int = list->vars[i].v.type_int;
			break;
		}
	}

	str_tcopy(&V.name,&tl[list->len].name);
	tl[list->len].type = V.type;
	switch(V.type){
		case VAR_TYPE_FLOAT:
			tl[list->len].v.type_float = V.v.type_float;
		break;

		case VAR_TYPE_FUNCT:
			tl[list->len].v.type_func = V.v.type_func;
		break;

		case VAR_TYPE_LIST:
			tl[list->len].v.type_list = V.v.type_list;
		break;

		case VAR_TYPE_INT:
		case VAR_TYPE_FLEX:
		default:
			tl[list->len].v.type_int = V.v.type_int;
		break;
	}
	list->len = list->len + 1;

	free(list->vars);
	list->vars = tl;
}

void localUpdate(localVars_t* list, str_t* n, int type, void* v){
	if(!list){
		return;
	}

	if(!n){
		return;
	}

	for(int i = 0; i < list->len; i++){
		if(str_tequ(n,&list->vars[i].name)){
			if(type != list->vars[i].type){
				list->vars[i].type = type;
			}
			updateVar(&list->vars[i],type,v);
		}
	}
}

void localSet(localVars_t* list, str_t* n, int type, void* v){
	if(localExists(list,n)){
		localUpdate(list,n,type,v);
	}else{
		localNew(list,n,type,v);
	}
}

Var_t localGet(localVars_t* list, str_t* n){
	if(localExists(list,n)){
		for(int i = 0; i < list->len; i++){
			if(str_tequ(n,&list->vars[i].name)){
				return list->vars[i].v;
			}
		}
	}else{
		return (Var_t){.type_int = 0};
	}
}

Tvar_t localGetType(localVars_t* list, str_t* n){
	if(localExists(list,n)){
		for(int i = 0; i < list->len; i++){
			if(str_tequ(n,&list->vars[i].name)){
				return (Tvar_t){.v = list->vars[i].v, .type = list->vars[i].type};
			}
		}
	}else{
		return (Tvar_t){.v = {.type_int = 0}, .type = VAR_TYPE_INT};
	}
}

void appendStrPool(str_pool_t* parent, char* str){
	while(parent != NULL){
		parent = parent->next;
	}

	if(parent != NULL){
		parent->next = malloc(sizeof(str_pool_t));
		parent->next->next = NULL;
		parent->next->str_home = str;
	}else{
		parent = malloc(sizeof(str_pool_t));
		parent->next = NULL;
		parent->str_home = str;
	}
}

void freeStrPool(str_pool_t* p){
	while(p != NULL){
		if(p->str_home != NULL){
			free(p->str_home);
		}
		str_pool_t* t = p->next;
		free(p);
		p = t;
	}
}

#endif
