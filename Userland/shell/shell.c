#include <shell.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <command.h>


char shell_buffer[128/*SHELL_BUFFER_SIZE*/];
int curr_pos =0;

int cmd_count = 10; /****Must update with each cmd inser/delete****/

cmd_entry cmd_table[10];

void init_shell()
{

	clean_buffer();
	initialize_cmd_table(); 
	prnt_welcome_msg();
	print_shell_text();
	print_commands();


}

void print_shell_text()
{
	char fmt[] = "%s";
	char shell_text[] = "Shell> ";
	printf(fmt, shell_text);
}

void print_shell_error()
{
	char fmt[] = "%s";
	char shell_text[] = "We are sorry, command does not exist, select one of available commands:";
	printf(fmt, shell_text);
}

void update_shell()
{
	char key;
	key = getc(); 
	if(key == 0)
	{
		return;
	}
	if(key == '\n')
	{
		putc('\n');
		excecute_command(shell_buffer);
		print_shell_text();
		clean_buffer();
	}
	if(curr_pos >= 128/*SHELL_BUFFER_SIZE*/-2)
	{
		//sound beep
		return;
	}


	else if (key == '\b')
	{
		if(curr_pos > 0){
			putc('\b');
			putc(' ');
			putc('\b');
			curr_pos--;
			shell_buffer[curr_pos] = '\0';
		}
	}
	else 
	{
		putc(key);
		shell_buffer[curr_pos] = key;
		curr_pos++;
	}
}

void excecute_command(char* buffer)
{

	int cmd_no = parse_command(buffer);
	if( cmd_no == -1)
	{
		print_shell_error();
		print_commands();
		return;
	}
	int argc, cmd_len;
	cmd_len = strlen(cmd_table[cmd_no].name);
	char** args = get_arguments(buffer+cmd_len, &argc);
	cmd_table[cmd_no].func(args, argc);
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
	char next = buffer[i];
	if(next == ' ' || next == '\0'){
		return cmd_no;
	}
	return -1;
}



char** get_arguments(char* buffer, int* argc)
{
	char* argv[25/*MAX_ARG_DIM*/];
	int i = 0, arg = 0;
	while(buffer[i] != '\0' && arg < 25/*MAX_ARG_DIM*/) {
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
	while(i < 128/*SHELL_BUFFER_SIZE*/ && i < curr_pos)
	{
		shell_buffer[i] = '\0';
		i++;
	}
	curr_pos = 0;
}


void prnt_welcome_msg()
 {
 	char fmt_s[] = "%s";
 	char welcome[] = "\n\n***Welcome to Barely Compiles OS***\n\n";
	printf(fmt_s, welcome);
}

//Returns the index of the command in the command table, if such command does not exist, returns -1
int get_cmd_index(char * cmd_name) 
{
	int i;
	for( i=0; i < cmd_count; i++) {
		if (strcmp(cmd_name, cmd_table[i].name) == 0) {
			return i;
		}
	}
	return -1;
}


cmd_entry* get_command_table()
{
	return cmd_table;
}



void print_commands()
{
	int i;
	char fmt[] = "%s\n";
	for( i=0; i < cmd_count; i++)
	{
		printf(fmt, cmd_table[i].name);
	}

}

int get_cmd_count()
{
	return cmd_count;
}

void initialize_cmd_table()
{

	char name0[] = "echo";
	char name1[] = "clear";
	char name2[] = "date";
	char name3[] = "time";
	char name4[] = "setdate";
	char name5[] = "settime";
	char name6[] = "getchar";
	char name7[] = "printf";
	char name8[] = "scanf";
	char name9[] = "help";

	cmd_table[0].name = name0;
	cmd_table[1].name = name1;
	cmd_table[2].name = name2;
	cmd_table[3].name = name3;
	cmd_table[4].name = name4;
	cmd_table[5].name = name5;
	cmd_table[6].name = name6;
	cmd_table[7].name = name7;
	cmd_table[8].name = name8;
	cmd_table[9].name = name9;

	char help0[] =	"Echo repeats the input string following echo statement \n example: \"echo Hello I am using echo\"";
	char help1[] =	"Clears the screen, uses no arguments, therefore will ignore any ones received\n";
	char help2[] =	"Prints current system date on screen\n";
	char help3[] =	"Prints current system time on screen\n";
	char help4[] =	"Sets system date, format must be dd/mm/yyyy.\nExample: \"setdate 05/05/2015\"\n";
	char help5[] =	"Sets system time, format must be ss:mm:hh.\n Example: \" settime 23:23:23\"\n";
	char help6[] =	"Test command for directive board to test getchar() functionality.\n";
	char help7[] =	"Test command for supreme leaders to test printf() functionality \n";
	char help8[] =	"Test command for the High Command to test scanf() functionality\n";
	char help9[] =	"Displays information about following command, syntaxt: \"help \"command_name\"\"\n";

	cmd_table[0].help = help0; 
	cmd_table[1].help = help1; 
	cmd_table[2].help = help2; 
	cmd_table[3].help = help3; 
	cmd_table[4].help = help4; 
	cmd_table[5].help = help5; 
	cmd_table[6].help = help6; 
	cmd_table[7].help = help7; 
	cmd_table[8].help = help8; 
	cmd_table[9].help = help9; 

	
	cmd_table[0].func = &echo;
	cmd_table[1].func = &clear;
	cmd_table[2].func = &date;
	cmd_table[3].func = &time;
	cmd_table[4].func = &set_date;
	cmd_table[5].func = &set_time;
	cmd_table[6].func = &getchar_cmd;
	cmd_table[7].func = &printf_cmd;
	cmd_table[8].func = &scanf_cmd;
	cmd_table[9].func = &help;
}
