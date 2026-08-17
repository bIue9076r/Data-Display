#include <stdio.h>
#include <stdlib.h>

#include "genlib.c"
#include "letters.c"
#include "drawing.c"
#include "data.c"
#include "display.c"

#include "strlib.c"

#define VERSION "0.0"

display_t gDisplay;
int gRunning = 1;
int gWitdh = 600;
int gHeight = 400;

// Options
// -h --help
// -v --version
// -i [input]

void help(void){
	printf("datDis Evaluator - Options\n");
	printf("-h\t\t\t|\tHelp\n");
	printf("-v\t\t\t|\tVersion\n");
	printf("--help\t\t\t|\tHelp\n");
	printf("--Version\t\t|\tVersion\n");
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

str_t arg_strings[] = {
	(str_t){.len=2,.str="-h"},
	(str_t){.len=6,.str="--help"},
	(str_t){.len=9,.str="--version"},
	(str_t){.len=2,.str="-v"},
	(str_t){.len=2,.str="-i"},
	(str_t){.len=7,.str="--input"},
};

// Commands
// v / version
// h / help

void commandHelp(int i){
	printf("Commands\n");
	printf("h / help\t\t|\tHelp\n");
	printf("v / version\t\t|\tVersion\n");
}

str_t commands[] = {
	(str_t){.len=7,.str="version"},
	(str_t){.len=1,.str="v"},
	(str_t){.len=4,.str="help"},
	(str_t){.len=1,.str="h"},
	(str_t){.len=4,.str="exit"},
	(str_t){.len=4,.str="plot"},
};

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

	if(str_tequ(&command,&commands[0]) || str_tequ(&command,&commands[1])){
		version();
	}

	if(str_tequ(&command,&commands[2]) || str_tequ(&command,&commands[3])){
		if(params.len > 0){
			commandHelp(str_ttoi(&params));
		}else{
			commandHelp(0);
		}
	}

	if(str_tequ(&command,&commands[4])){
		gRunning = 0;
	}

	if(str_tequ(&command,&commands[5])){
		if(params.len > 0){
			str_t trail = {.len = 0, .str = NULL};
			str_tsplit(&params,&trail);

			char str[params.len + 1];
			for(int i = 0; i < params.len; i++){
				str[i] = params.str[i];
			}
			str[params.len] = 0;
			
			ShowColorBuffer(&gDisplay,str);

			printf("Ploted display to \"");
			str_tprint(&params);
			printf("\"\n");

			if(trail.len > 0){
				printf("Warning: Trailing parameters\n");
				printf("-> ");
				str_tprintln(&trail);
			}
		}else{
			printf("Missing parameters for plot\n");
		}
	}

	return 0;
}

int main(int argc, char** argv){
	newDisplay(&gDisplay,gHeight,gWitdh);
	// Parse Input args
	if(argc > 1){
		int bad = 0;
		for(int i = 1; i < argc; i++){
			str_t a; str_tnew(&a,argv[i]);
			if(str_tequ(&a,&arg_strings[0]) || str_tequ(&a,&arg_strings[1])){
				help();
				goto quikexit;
			}

			if(str_tequ(&a,&arg_strings[2]) || str_tequ(&a,&arg_strings[3])){
				version();
				goto quikexit;
			}

			if(str_tequ(&a,&arg_strings[4]) || str_tequ(&a,&arg_strings[5])){
				for(int j = i + 1; j < argc; j++){
					str_t line;
					str_tnew(&line,argv[j]);
					eval(&line);
				}
				goto quikexit;
			}

			// default
			badArg(&a,bad);
			bad = 1;
		}
	}

	while(gRunning){
		// Read Input
		char* str = readInput();
		str_t input;
		str_tnew(&input,str);

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
