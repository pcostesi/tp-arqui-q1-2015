#include <shell.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <command.h>

/*
char shell_buffer[SHELL_BUFFER_SIZE];
int curr_pos =0;

int cmd_count = 9; /****Must update with each cmd inser/delete****/
/*
cmd_entry cmd_table [] =
{
	{"echo", ECHO_HELP, echo},
	{"clear", CLEAR_HELP, clear},
	{"date", DATE_HELP, date},
	{"time", TIME_HELP, time},
	{"setdate", SETDATE_HELP, set_date},
	{"settime", SETTIME_HELP, set_time},
	{"getchar", GETCHAR_HELP, getchar_cmd},
	{"printf", PRINTF_HELP, printf_cmd},
	{"scanf", SCANF_HELP, scanf_cmd}
};

void init_shell()
{
	clean_buffer();
	prnt_welcome_msg();
	printf(SHELL_TEXT); 
}

void update_shell()
{
	char key;
	key = getc(); 
	if(key == 0)
	{
		return;
	}

	if(curr_pos >= SHELL_BUFFER_SIZE-1)
	{
		//sound beep
		return;
	}

	if(key == '\n')
	{
		printf("\n");
		excecute_command(shell_buffer);
		printf(SHELL_TEXT);
		void cleanBuffer();
	}
	else if (key == '\b')
	{
		if(curr_pos > 0){
			printf("\b");
			curr_pos--;
			shell_buffer[curr_pos] = '\0';
		}
	}
	else 
	{
		printf(key);
		shell_buffer[curr_pos] = key;
		shell_buffer[curr_pos] = '\0';
		curr_pos++;
	}
}

void excecute_command(char* buffer)
{

	int cmd_no = parse_command(buffer);
	if( cmd_no == -1)
	{
		//print error
		return;
	}
	int argc, cmd_len;
	cmd_len = strlen(cmd_table[cmd_no].name);
	char** args = get_arguments(buffer+cmd_len, &argc);
	cmd_table[cmd_no].func(argc, args);
}

int parse_command(char* buffer)
{
	int i = 0, cmd_no = -1;
	if(buffer[0] == '\0')
	{

	}

	while( cmd_no == -1 && i < cmd_count){
		if(substr(cmd_table[i].name, buffer))
		{
			cmd_no = i;
		}
		i++;
	}
	i = strlen(cmd_table[cmd_no].name);
	char next = (buffer+i);
	if(next == ' ' || next == '\0'){
		return cmd_no;
	}
	return -1;
}



char** get_arguments(char* buffer, int* argc)
{
	char* argv[MAX_ARG_DIM];
	int i = 0, arg = 0;
	while(buffer[i] != '\0' && arg < MAX_ARG_DIM) {
		if(buffer[i+1]==' ')
		{
		}
		else if (buffer[i] == ' ') {
			argv[arg++] = buffer + i + 1;
			buffer[i] = '\0';
		}
		i++;
	}
	*argc = arg;
	return argv;
}


void clean_buffer()
 {
	int i = 0;
	while(i < SHELL_BUFFER_SIZE && i < curr_pos)
	{
		shell_buffer[i] = '\0';
	}
	curr_pos = 0;
}


void prnt_welcome_msg()
 {
	printf(WELCOME_MSG);
}
*/