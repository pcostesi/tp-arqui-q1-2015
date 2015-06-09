#include <command.h>
#include <string.h>

/*
void echo(char** args, int argc)
{
	int i;
	for(i=0; i < argc ; i++)
	{
		printf("%s \n", args[argc]);
	}

}

void clear(char** args, int argc)
{
	int i = 0;
	for(i=0; i<20;i++){
		printf("\n");
	}
}


void date(char** args, int argc)
{
	//TODO int date params;
	//TODO get_date(); //implementation pending
	printf("Implement date");
}

void time(char** args, int argc)
{
	//TODO int time params;
	//TODO get_time(); //implementation pending
	printf("print params");
}

void set_date(char** args, int argc)
{
	int days, months, years;
	if(argc <1){
		printf("%s \n", SETDATE_ERROR_NO_ARGUMENTS);
		return;
	}
	if(!parse_date(args[0], &days, &months, &years)){
		printf("%s \n", SETDATE_ERROR_INVALID_FORMAT);
		return;

	}
	//TODO   set system date
}

void set_time(char** args, int argc)
{
	int seconds, minutes, hours;
	if(argc < 1)
	{
		printf(SET_TIME_NO_ARGUMENT);
		return;
	}	
	if(!parse_time(args[0], &seconds, &minutes, &hours))
	{
		printf(SETTIME_FORMAT_ERROR);
		return;
	}
	//TODO SET SYSTEM TIME

}

//Receives input string, parses it for a date, returns 1 if valid, 0 if not
int parse_date(char* date_string, int* days, int*months, int*years)
{
	int valid = 1, i=0;
	int len =0;
	len = strlen(date_string);
	if(len !=10)
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
	if( !is_num(date_string[6]) || !is_num(date_string[7] || date_string[8]) || !is_num(date_string[9]))
	{
		return 0;
	}
	*days = ((int)date_string[0]-'0' )*10+(int)(date_string[1]-'0'); 
	*months = ((int)date_string[3]-'0' )*10+(int)(date_string[4]-'0');
	*years = ((int)date_string[6]-'0' )*1000+(int)(date_string[7]-'0')*100 +
			((int)date_string[8]-'0' )*10+(int)(date_string[9]-'0'); 
	return valid_date(*days, *months, *years);

}

int parse_time(char* time_string, int* seconds, int*minutes, int*hours)
{
	int valid = 1, i=0;
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
	//days
	if( !is_num(time_string[3]) || !is_num(time_string[4]))
	{
		return 0;
	}
	//months
	if( !is_num(time_string[6]) || !is_num(time_string[7]))
	{
		return 0;
	}
	*seconds = (time_string[0]-'0')*10 + (time_string[1]-'0');
	*minutes = (time_string[3]-'0')*10 + (time_string[4]-'0');
	*hours = (time_string[6]-'0')*10 + (time_string[7]-'0');
	if(!valid_time(seconds, minutes, hours))
	{
		printf(SETTIME_FORMAT_ERROR);
		return;
	}
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

int valid_date(int year, int month, int day)
{
	unsigned short monthlen[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if (year < 0 || month < 1 || year < 0 || month > 12){
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


int getchar_cmd(int argc, char *argv[]) 
{
	printf("Please type in a character\n");
	char c = getchar();
	printf("You pressed: %c\n", c);
}

int printf_cmd(int argc, char *argv[]) 
{
	printf("Testing printf...\n\n");
	printf("Printing a double: %f\n", 123.456789);
	printf("Printing an integer: %d\n", 99);
	printf("Printing an unsigned integer: %u\n", 312312);
	printf("Printing a string %s\n", "This is a real cool string!");
	printf("Printing in lowercase hexadecimal notation: %x\n", 0x55fa);
	printf("Printing a single char: %c\n", 'c');
}

int scanf_cmd(int argc, char *argv[]) 
{
	int n;
	char vec[50];
	float f;
	printf("Welcome to scanf user test:\n ");
	printf("And so, the trial begins...\n");
	printf("Please type in a number: ");
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
	printf("Type in double format, your credit card number followed by verification code\n" );
	scanf("%f", &f);
	printf("\nYour fake card data was: %f\n\n", f);
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

