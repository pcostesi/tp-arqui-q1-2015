#ifndef __SHELL_H_
#define __SHELL_H_ 1
#include <command.h>

#define SHELL_TEXT "Shell> "
#define SHELL_BUFFER_SIZE 512
#define WELCOME_MSG "Welcome to Barely Compiles OS \n"
#define MAX_ARG_DIM 32

typedef struct cmd_entry {
	char* name;
	char* help;
	int (*func)(int argc, char *argv[]);
} cmd_entry;

void init_shell(void);
void update_shell(void);
void excecute_command(char*);
int parse_command(char*);
void clean_buffer(void);
void prnt_welcome_msg();
char** get_arguments(char*, int*);
void clean_buffer(void);
void prnt_welcome_msg(void);


#endif