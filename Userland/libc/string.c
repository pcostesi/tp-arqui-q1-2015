#include <libc.h>
#include <string.h>

/* mostly taken from K&R */

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


//Returns 1 if s1 is substring of s2, else it returns 0
int substr(char * s1, char *s2)
 {
    int i = 0, is_substr = 1;
    while(is_substr && s1[i] != '\0') {
        if(s1[i] != s2[i]) {
            is_substr = 0;
        }
        i++;
    }
    return is_substr;
}



int strcmp(char * s1, char * s2)
{
    int ret = 0;
    
    while(ret == 0 && (*s1 != '\0' || *s2 != '\0')) {
        ret = *s1 - *s2;
        s1++;
        s2++;
    }
    
    return ret;
}