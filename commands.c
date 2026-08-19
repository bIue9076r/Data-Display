#ifndef COMMANDS_C
#define COMMANDS_C
#include "commands.h"

// Commands
// v / version
// h / help
// exit
// plot

void commandHelp(int i){
	printf("Commands\n");
	printf("h / help\t\t|\tHelp\n");
	printf("v / version\t\t|\tVersion\n");
}

void cmd_help(str_t* command, str_t* params){
	if(params->len > 0){
		commandHelp(str_ttoi(params));
	}else{
		commandHelp(0);
	}
}

void cmd_exit(str_t* command, str_t* params){
	gRunning = 0;
}

void cmd_plot(str_t* command, str_t* params){
	if(params->len > 0){
		str_t trail = {.len = 0, .str = NULL};
		str_tsplit(params,&trail);

		char str[params->len + 1];
		for(int i = 0; i < params->len; i++){
			str[i] = params->str[i];
		}
		str[params->len] = 0;
		
		ShowColorBuffer(&gDisplay,str);

		printf("Ploted display to \"");
		str_tprint(params);
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

void cmd_show(str_t* command, str_t* params){
	if(params->len > 0){
		str_t trail = {.len = 0, .str = NULL};
		str_tsplit(params,&trail);

		char str[params->len + 1];
		for(int i = 0; i < params->len; i++){
			str[i] = params->str[i];
		}
		str[params->len] = 0;
		
		ShowDataInfo(&gDisplay,str);

		printf("Logged info to \"");
		str_tprint(params);
		printf("\"\n");

		if(trail.len > 0){
			printf("Warning: Trailing parameters\n");
			printf("-> ");
			str_tprintln(&trail);
		}
	}else{
		PrintDataInfo(&gDisplay);
	}
}

str_t commands[] = {
	(str_t){.len=7,.str="version"},
	(str_t){.len=1,.str="v"},
	(str_t){.len=4,.str="help"},
	(str_t){.len=1,.str="h"},
	(str_t){.len=4,.str="exit"},
	(str_t){.len=4,.str="plot"},
	(str_t){.len=4,.str="show"},
};

int runCommand(str_t* command, str_t* params){
	if(CMD(CMD_VER1) || CMD(CMD_VER2)){
		version();
		return 0;
	}

	if(CMD(CMD_HELP1) || CMD(CMD_HELP2)){
		cmd_help(command,params);
		return 0;
	}

	if(CMD(CMD_EXIT)){
		cmd_exit(command,params);
		return 0;
	}

	if(CMD(CMD_PLOT)){
		cmd_plot(command,params);
		return 0;
	}

	if(CMD(CMD_SHOW)){
		cmd_show(command,params);
		return 0;
	}

	// Invalid command
	printf("Unknown Command\n");
	printf("-> ");
	str_tprintln(command);
	return 0;
}

#endif
