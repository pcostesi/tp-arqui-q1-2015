#ifndef __COMMANDS_H_
#define __COMMANDS_H_ 1



//Help messages
#define ECHO_HELP "Echo repeats the input string following echo statement \n example: \"echo Hello I am using echo\""
#define CLEAR_HELP "Clears the screen, uses no arguments, therefore will ignore any ones received"
#define DATE_HELP "Prints current system date on screen"
#define TIME_HELP "Prints current system time on screen"
#define SETDATE_HELP "Sets system date, format must be dd/mm/yyyy.\nExample: \"setdate 05/05/2015\" \n "
#define SETTIME_HELP "Sets system time, format must be ss:mm:hh.\n Example: \" settime 23:23:23\"\n "
#define GETCHAR_HELP "Test command for directive board to test getchar() functionality.\n"
#define PRINTF_HELP "Test command for supreme leaders to test printf() functionality \n"
#define SCANF_HELP "Test command for the High Command to test scanf() functionality\n"

//Error messages
#define SETDATE_ERROR_INVALID_FORMAT "Invalid date inserted, please respect dd/mm/yyyy format & insert a valid date.\n"
#define SETDATE_ERROR_NO_ARGUMENTS "No arguments were sent to command setdate format musut be dd/mm/yyyy \n"
#define SET_TIME_NO_ARGUMENT "No arguments were sent to command settime format musut be ss:mm:hh \n"
#define SETTIME_FORMAT_ERROR "Invalid date inserted, please respect ss:mm:hh format & insert a valid date.\n" 


void echo(char**, int);
void clear(char**, int);
void date(char**, int);
void time(char**, int);
void set_date(char**, int);
void set_time(char**, int);
int parse_date(char*, int*, int*, int*);
int parse_time(char*, int*, int*, int*);
int is_num(char);
int valid_time(int, int, int);
int valid_date(int, int, int);
int is_leap_year(int);
int getchar_cmd(int, char *argv[]);
int printf_cmd(int, char *argv[]);
int scanf_cmd(int argc, char *argv[]);
void reset_vect(char vec[]);





#endif