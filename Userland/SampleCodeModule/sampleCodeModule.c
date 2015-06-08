#include <libc.h>

struct rtc_time 
{
	int sec;
	int min;
	int hour;
	int mday;
	int mon;
	int year;
};

extern void gettime(struct rtc_time *);
extern void settime(struct rtc_time *);

void reverse(char s[]);
void itoa(int n, char s[]);
int strlen(char * s);

int main() {
	struct rtc_time timestruct;
	//halt();
	//pause();
	char str[] = "hi \n";
	char ts[5];
	write(1, str, 4);
	write(1, str, 4);
	write(1, str, 4);
	write(1, str, 4);
	gettime(&timestruct);
	itoa(timestruct.hour, ts);
	write(1, ts, 2);
	write(1, ":", 1);
	itoa(timestruct.min, ts);
	write(1, ts, 2);
	write(1, ":", 1);
	itoa(timestruct.sec, ts);
	write(1, ts, 2);
	return 0xDEADBEEF;
}



int strlen(char * s)
{
	int res = 0;
	while (*s++) res++;
	return res;
}

  /* reverse:  reverse string s in place */
 void reverse(char s[])
 {
     int i, j;
     char c;
 
     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
 }

 /* itoa:  convert n to characters in s */
 void itoa(int n, char s[])
 {
     int i, sign;
 
     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
         s[i++] = n % 10 + '0';   /* get next digit */
     } while ((n /= 10) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
 }
