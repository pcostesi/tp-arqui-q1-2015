#include <command.h>
#include <string.h>
#include <shell.h>
#include <stdio.h>
#include <libc.h>

/*****Commands functions*****/


void help(char *argv[], int argc) 
{
	int cmd_index;
	cmd_entry* table = get_command_table();
	if (argc == 1) {
		cmd_index = get_cmd_index(argv[0]);
		if (cmd_index != -1) {
			printf("%s", table[cmd_index].help);
		} else {
			help_error_print(table);
		}
	} else if (argc == 0) {
		help_error_print(table);
	}
}


void echo(char** args, int argc)
{
	int i;
	for(i = 0; i < argc; i++)
	{
		printf("%s ", args[i]);
	}
	putc('\n');
}

void clear(char** args, int argc)
{
    ioctl(STDOUT, IOCTL_CLR,    (void *) 0);
    ioctl(STDOUT, IOCTL_MOVE,   (void *) 0);
}

void commands(char** args, int argc)
{
	printf("Available commands are: \n");
	print_commands();
}


void date(char** args, int argc)
{
	struct rtc_time time_struct;
	gettime(&time_struct);
	printf("%d/%d/%d\n",
		time_struct.day,
		time_struct.mon,
		time_struct.year
	);
}

void time(char** args, int argc)
{
	struct rtc_time time_struct;
	gettime(&time_struct);
	printf("%d:%d:%d\n",
		time_struct.hour,
		time_struct.min,
		time_struct.sec
	);
}

void set_date(char** args, int argc)
{
	struct rtc_time time_struct;
	int days, months, years;

	gettime(&time_struct);
	if(argc <1){
		printf(INVALID_DATE);
		return;
	}
	if(!parse_date(args[0], &days, &months, &years)){
		printf(INVALID_DATE);
		return;

	}
	time_struct.year = years;
	time_struct.mon = months;
	time_struct.day = days;

	settime(&time_struct);
}

void set_time(char** args, int argc)
{
	struct rtc_time time_struct;
	int seconds, minutes, hours;

	gettime(&time_struct);
	if(argc < 1){
		printf(INVALID_TIME);
		return;
	}	
	if(!parse_time(args[0], &seconds, &minutes, &hours)){
		printf(INVALID_TIME);
		return;
	}


	time_struct.sec = seconds;
	time_struct.min = minutes;
	time_struct.hour = hours;

	settime(&time_struct);

}
 
void halt_system(void)
{
	halt();
}

void print_ascii_table(char** args, int argc)
{
	int i;

	for (i = 0; i < 128; i++){
		printf("%x: %c", i, i < 32 ? ' ' : i);

		if (i % 8) {
			printf(" \t| ");
		} else {
    		putc('\n');
    	}
	}

    putc('\n');
}






/*****Auxiliary functions for commands*****/






//Receives input string, parses it for a date, returns 1 if valid, 0 if not
int parse_date(char* date_string, int* days, int*months, int*years)
{
	int len =0;
	len = strlen(date_string);
	if(len !=8)
	{
		return 0;
	}
	if(date_string[2]!= '/' || date_string[5] != '/')
	{
		return 0;	
	}
	//days
	if( !is_num(date_string[0]) || !is_num(date_string[1]))
	{
		return 0;
	}
	//months
	if( !is_num(date_string[3]) || !is_num(date_string[4]) )
	{
		return 0;
	}
	//years
	if( !is_num(date_string[6]) || !is_num(date_string[7]) )
	{	
		return 0;
	}
	*days = ((int)date_string[0]-'0' )*10+(int)(date_string[1]-'0'); 
	*months = ((int)date_string[3]-'0' )*10+(int)(date_string[4]-'0');
	*years = ((int)date_string[6]-'0' )*10+(int)(date_string[7]-'0'); 	
	return valid_date(*days, *months, *years);

}

int parse_time(char* time_string, int* seconds, int*minutes, int*hours)
{	
	int len =0;
	len = strlen(time_string);
	if(len !=8)
	{
		return 0;
	}
	if(time_string[2]!= ':' || time_string[5] != ':')
	{
		return 0;	
	}
	//seconds
	if( !is_num(time_string[0]) || !is_num(time_string[1]))
	{
		return 0;
	}
	//minutes
	if( !is_num(time_string[3]) || !is_num(time_string[4]))
	{
		return 0;
	}
	//hours
	if( !is_num(time_string[6]) || !is_num(time_string[7]))
	{
		return 0;
	}
	*seconds = (time_string[0]-'0')*10 + (time_string[1]-'0');
	*minutes = (time_string[3]-'0')*10 + (time_string[4]-'0');
	*hours = (time_string[6]-'0')*10 + (time_string[7]-'0');
	return valid_time(*seconds, *minutes, *hours);
}


int is_num(char c)
{
	if( (c >= '0') && (c<+ '9'))
	{
		return 1;
	}
	return 0;
}

int valid_time(int sec, int min, int hrs)
{

	if( sec >60 || sec < 0	||
		min >60 || min < 0	||
		hrs >24 || sec < 0)
	{
		return 0;
	}
	return 1;

}

int valid_date(int day, int month, int year)
{
	unsigned short monthlen[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if (month < 1 || day < 1 || month > 12){
		return 0;
	}
	if (is_leap_year(year) && month == 2) {
		monthlen[1]++;
	}
	if (day>monthlen[month-1] || day < 1) {
		return 0;
	}
	return 1;
}

int is_leap_year(int year)
{
	return ((!(year%4) && (year%100)) || !(year%400));
}	


void getchar_cmd(char *argv[], int argc) 
{
	printf("Please type in a character\n");
	char c = getc();
	printf("You pressed: %c\n", c);
}

void printf_cmd(char *argv[], int argc) 
{
	printf("Testing printf...\n\n");
	printf("Printing an integer: %d\n", 99);
	printf("Printing a string: %s\n", "This is a real cool string!");
	printf("Printing in uppercase hexadecimal notation: %x\n", 0x55fa);
	printf("Printing a single char: %c\n", 'z');
}

void scanf_cmd(char *argv[], int argc) 
{
	int n;
	char vec[SCANF_MAX_STR_BUFFER];
	printf("Welcome to scanf user test:\n ");
	printf("And so, the trial begins...\n");
	printf("Please type in a number: \n");
	scanf("%d", &n);
	printf("You typed in: %d\n\n", n);
	reset_vect(vec);
	
	printf("Trial number 2...type in a short text: ");
	scanf("%s", vec);
	printf("You typed in: %s\n\n", vec);
	reset_vect(vec);

	printf("Trial number 3...Please type in a single character: ");
	scanf("%c", vec);
	printf("\nYou typed: %c\n\n", vec[0]);
	reset_vect(vec);

	printf("And so, the final trial begins:\n");
	printf("Are you ready? Type in Y or N\n");
	scanf("%s", vec);
	reset_vect(vec);
	printf(" Actually your response was irrelevant, proceeding with last trial...\n ");
	printf("Type in string format, your credit card number followed by verification code\n" );
	scanf("%s", vec);
	printf("\nYour fake card data was: %s\n\n", vec);
	reset_vect(vec);
}

void reset_vect(char vec[])
{
	int i;
	for(i=0; i<50; i++ )
	{
		vec[i] = 0;
	}
}

/*TODO EPIC ASCII STAR*/
//TODO EVIL MUSIC 


void help_error_print()
{
	printf("\nInvoke help as follows: \"help \"command_name\"\".\nTo see list of available commands type \"commands\"");	
}


