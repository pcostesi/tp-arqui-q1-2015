#include <shell.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <command.h>


char shell_buffer[128/*SHELL_BUFFER_SIZE*/];
int curr_pos =0;

cmd_entry cmd_table[11];
int cmd_count = (sizeof(cmd_table) / sizeof(cmd_entry));

void init_shell()
{

	clean_buffer();
	initialize_cmd_table(); 
	prnt_welcome_msg();
	print_shell_text();


}

void print_shell_text()
{
	char fmt[] = "%s";
	char shell_text[] = "Shell> ";
	printf(fmt, shell_text);
}

void print_shell_error()
{
	printf("We are sorry, command does not exist, select one of available commands:\n");
}

void update_shell()
{
	char key;
	key = getc();

	if(key == 0) {
		return;
	}

	if(key == '\n') {
		putc('\n');
		shell_buffer[curr_pos] = 0;
		excecute_command(shell_buffer);
		print_shell_text();
		clean_buffer();

	} else if (key == '\b') {
		if(curr_pos > 0){
			putc('\b');
			putc(' ');
			putc('\b');
			curr_pos--;
			shell_buffer[curr_pos] = '\0';
		}

	} else if(curr_pos >= 128/*SHELL_BUFFER_SIZE*/-2) {
		//sound beep
		return;

	} else {
		putc(key);
		shell_buffer[curr_pos] = key;
		curr_pos++;
	}
}

void excecute_command(char* buffer)
{
	int argc,
		cmd_len;
	char * args[64];

	int cmd_no = parse_command(buffer);
	if( cmd_no == -1)
	{
		print_shell_error();
		print_commands();
		return;
	}

	cmd_len = strlen(cmd_table[cmd_no].name);
	argc = get_arguments(buffer + cmd_len, args);
	cmd_table[cmd_no].func(args, argc);
}

int parse_command(char* buffer)
{
	int i = 0,
		cmd_no = -1;

	if(buffer[0] == '\0') {
		return -1;
	}

	while (cmd_no == -1 && i < cmd_count) {
		if (substr(cmd_table[i].name, buffer)) {
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



unsigned int get_arguments(char* buffer, char ** args)
{
	int arg = 0,	// current argument
		i = 0;		// current buffer index

	char * ptr = NULL;

	while (buffer[i] != '\0' && buffer[i] == ' ') {
		i++;
	}

	while (buffer[i] != '\0' && arg < 64) {
		// guard condition
		if (buffer[i] == ' ') {
			ptr = NULL;
			buffer[i] = '\0';
			i++;
			continue;
		}

		if (ptr == NULL) {
			ptr = buffer + i;
			args[arg] = ptr;
			arg++;
		}

		i++;
	}
	return arg;
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
	for( i=0; i < cmd_count; i++)
	{
		printf("command: \t%s\n", cmd_table[i].name);
	}

}

int get_cmd_count()
{
	return cmd_count;
}

void initialize_cmd_table()
{
	cmd_table[0].name = "echo";
	cmd_table[1].name = "clear";
	cmd_table[2].name = "date";
	cmd_table[3].name = "time";
	cmd_table[4].name = "setdate";
	cmd_table[5].name = "settime";
	cmd_table[6].name = "getchar";
	cmd_table[7].name = "printf";
	cmd_table[8].name = "scanf";
	cmd_table[9].name = "help";
	cmd_table[10].name = "halt";
	
	
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
	cmd_table[10].func = &halt_system;


	cmd_table[0].help = "Echo repeats the input string following echo statement \n example: \"echo Hello I am using echo\"";
	cmd_table[1].help = "Clears the screen, uses no arguments, therefore will ignore any ones received\n";
	cmd_table[2].help = "Prints current system date on screen\n";
	cmd_table[3].help = "Prints current system time on screen\n";
	cmd_table[4].help = "Sets system date, format must be dd/mm/yyyy.\nExample: \"setdate 05/05/2015\"\n";
	cmd_table[5].help = "Sets system time, format must be ss:mm:hh.\n Example: \" settime 23:23:23\"\n";
	cmd_table[6].help = "Test command for directive board to test getchar() functionality.\n";
	cmd_table[7].help = "Test command for supreme leaders to test printf() functionality \n";
	cmd_table[8].help = "Test command for the High Command to test scanf() functionality\n";
	cmd_table[9].help = "Displays information about following command, syntaxt: \"help \"command_name\"\"\n";
	cmd_table[10].help = "Halts the system.\n";

}
