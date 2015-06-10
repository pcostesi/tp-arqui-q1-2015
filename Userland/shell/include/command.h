#ifndef __COMMANDS_H_
#define __COMMANDS_H_ 1
#include <shell.h>

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
void getchar_cmd(char**, int);
void printf_cmd(char**, int);
void scanf_cmd(char**, int);
void reset_vect(char vec[]);
void help_error_print();
void help(char**, int); 
void halt_system(void);
#endif