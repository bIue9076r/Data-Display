#include <stdio.h>
#include <stdlib.h>

#include "gdeclare.h"

#include "genlib.c"
#include "letters.c"
#include "drawing.c"
#include "data.c"
#include "display.c"

#include "strlib.c"
#include "commands.c"

#define VERSION "0.0"

display_t gDisplay;
int gRunning = 1;
int gWitdh = 600;
int gHeight = 400;

void help(void){
	printf("datDis Evaluator - Options\n");
	printf("-h\t\t\t|\tHelp\n");
	printf("-help\t\t\t|\n");
	printf("-v\t\t\t|\tVersion\n");
	printf("-version\t\t|\n");
	printf("-dh\t\t\t|\tDisplay Height\n");
	printf("-height\t\t\t|\n");
	printf("-dw\t\t\t|\tDisplay Witdh\n");
	printf("-witdh\t\t\t|\n");
	printf("-b\t\t\t|\tBorder\n");
	printf("-border\t\t\t|\t\n");
	printf("-bl\t\t\t|\tBorder Left\n");
	printf("-border-left\t\t|\t\n");
	printf("-br\t\t\t|\tBorder Right\n");
	printf("-border-right\t\t|\t\n");
	printf("-bu\t\t\t|\tBorder Up\n");
	printf("-border-up\t\t|\t\n");
	printf("-bd\t\t\t|\tBorder Down\n");
	printf("-border-down\t\t|\t\n");
	printf("-bc\t\t\t|\tBorder Color\n");
	printf("-border-color\t\t|\t\n");
	printf("-lc\t\t\t|\tLine Color\n");
	printf("-line-color\t\t|\t\n");
	printf("-ac\t\t\t|\tAxis Color\n");
	printf("-axis-color\t\t|\t\n");
	printf("-cc\t\t\t|\tChar Color\n");
	printf("-char-color\t\t|\t\n");
	printf("-vc\t\t\t|\tView Color\n");
	printf("-view-color\t\t|\t\n");
	printf("-xs\t\t\t|\tX Start\n");
	printf("-x-start\t\t|\t\n");
	printf("-ys\t\t\t|\tY Start\n");
	printf("-y-start\t\t|\t\n");
	printf("-xe\t\t\t|\tX End\n");
	printf("-x-end\t\t\t|\t\n");
	printf("-ye\t\t\t|\tY End\n");
	printf("-y-end\t\t\t|\t\n");
	printf("-xr\t\t\t|\tX Range\n");
	printf("-x-range\t\t|\t\n");
	printf("-yr\t\t\t|\tY Range\n");
	printf("-y-range\t\t|\t\n");
	printf("-xp\t\t\t|\tX Padding\n");
	printf("-x-padding\t\t|\t\n");
	printf("-yp\t\t\t|\tY Padding\n");
	printf("-y-padding\t\t|\t\n");
	printf("-xl\t\t\t|\tX Lines\n");
	printf("-x-lines\t\t|\t\n");
	printf("-yl\t\t\t|\tY Lines\n");
	printf("-y-lines\t\t|\t\n");
	printf("-xlsy\t\t\t|\tX Lines Square Y\n");
	printf("-x-lines-sy\t\t|\t\n");
	printf("-ylsx\t\t\t|\tY Lines Square X\n");
	printf("-y-lines-sx\t\t|\t\n");
	printf("-cs\t\t\t|\tChar size\n");
	printf("-char-size\t\t|\t\n");
	printf("-lw\t\t\t|\tLine Width\n");
	printf("-line-width\t\t|\t\n");
	printf("-alw\t\t\t|\tAxis Line Width\n");
	printf("-axis-line-width\t|\t\n");
	printf("-xff\t\t\t|\tX Figure Format\n");
	printf("-x-figure-format\t|\t\n");
	printf("-yff\t\t\t|\tY Figure Format\n");
	printf("-y-figure-format\t|\t\n");
	printf("-ff\t\t\t|\tFigure Format\n");
	printf("-figure-format\t\t|\t\n");
	printf("-sxl\t\t\t|\tShow X Lines\n");
	printf("-show-x-lines\t\t|\t\n");
	printf("-syl\t\t\t|\tShow Y Lines\n");
	printf("-show-y-lines\t\t|\t\n");
	printf("-sl\t\t\t|\tShow Lines\n");
	printf("-show-lines\t\t|\t\n");
	printf("-dl\t\t\t|\tDashed Lines\n");
	printf("-dashed-line\t\t|\t\n");
	printf("-sxa\t\t\t|\tShow X Axis\n");
	printf("-show-x-axis\t\t|\t\n");
	printf("-sya\t\t\t|\tShow Y Axis\n");
	printf("-show-y-axis\t\t|\t\n");
	printf("-sa\t\t\t|\tShow Axis\n");
	printf("-show-axis\t\t|\t\n");
	printf("-sxf\t\t\t|\tShow X Figures\n");
	printf("-show-x-figures\t\t|\t\n");
	printf("-syf\t\t\t|\tShow Y Figures\n");
	printf("-show-y-figures\t\t|\t\n");
	printf("-sf\t\t\t|\tShow Figures\n");
	printf("-show-figures\t\t|\t\n");
}

void badArg(str_t* s,int b){
	if(!s){
		printf("bad argument\n");
		if(!b){
			help();
		}
	}

	printf("bad argument [%s]\n",s->str);
	if(!b){
		help();
	}
}

void version(void){
	printf("datDis Evaluator - Version %s\n",VERSION);
}

void err(int e){
	gRunning = 0;
	switch(e){
		case 0:
			gRunning = 1;
		break;

		default:
			printf("Error\n");
		break;
	}
}

#include "args.c"
#include "commands.c"

char* readInput(void){
	printf("\n> ");
	char* str = malloc(sizeof(char));
	str[0] = 0;
	int str_len = 0;
	char c = 0;
	while(c != '\n'){
		scanf("%c",&c);
		if(valChar(c)){
			char* tmp = malloc(sizeof(char) * (str_len + 2));
			for(int i = 0; i < str_len; i++){
				tmp[i] = str[i];
			}
			tmp[str_len++] = c;
			tmp[str_len] = 0;
			free(str);
			str = tmp;
		}
	}

	return str;
}

int eval(str_t* input){
	str_t command = {
		.len = input->len,
		.str = input->str,
	};

	str_t params = {
		.len = 0,
		.str = NULL,
	};

	int i = 0;
	while(i < input->len){
		if(input->str[i] == ' ' || input->str[i] == '\t'){
			command.len = i;
			if(i + 1 < input->len){
				params = (str_t){
					.len = (input->len - i - 1),
					.str = (input->str + i + 1),
				};
			}
			break;
		}

		i++;
	}

	// str_tprintln(&command);
	// str_tprintln(&params);
	return runCommand(&command, &params);;
}

int main(int argc, char** argv){
	gDisplay.colorBuffer = NULL;
	newDisplay(&gDisplay,gHeight,gWitdh);
	// Parse Input args
	if(readArgs(argc,argv)){
		goto quikexit;
	}

	while(gRunning){
		// Read Input
		char* str = readInput();
		str_t input;
		str_tnew(&input,str);

		if(input.len == 0){
			continue;
		}

		// Evaluate
		int e = eval(&input);
		if(e){
			err(e);
		}

		// Cleanup
		free(str);
	}

	// free memory
	quikexit:
	freeColorBuffer(&gDisplay);
	return 0;
}
