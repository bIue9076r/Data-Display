#ifndef COMMANDS_H
#define COMMANDS_H
#include "gdeclare.h"
#include "strlib.h"

#define CMD_VER1	0
#define CMD_VER2	1
#define CMD_HELP1	2
#define CMD_HELP2	3
#define CMD_EXIT	4
#define CMD_PLOT	5
#define CMD_SHOW	6

#define CMD(C) str_tequ(command,&commands[C])

void commandHelp(int i);
void cmd_help(str_t* command, str_t* params);
void cmd_exit(str_t* command, str_t* params);
void cmd_plot(str_t* command, str_t* params);
void cmd_show(str_t* command, str_t* params);

int runCommand(str_t* command, str_t* params);

#endif
