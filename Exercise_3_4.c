3.4 => 	In a two's complement number representation, our version of itoa does not handle the largest negative number, that is, the value of n equal
		to _(2wordsize-l). Explain why not. Modify it to print that value correctly, regardless of the machine on which it runs.
		
		#include <stdlib.h>
		#include <stdio.h>
		#include <limits.h>

		void itoa(int n, char s[]);
		void reverse(char s[]);

		int main(void) 
		{
			char buffer[20];
			
			printf("INT_MIN: %d\n", INT_MIN);
			itoa(INT_MIN, buffer);
			printf("Buffer : %s\n", buffer);
			
			return 0;
		}

		void itoa(int n, char s[])
		{
			int i, sign;
			sign = n;
			
			i = 0;
			do //generate digits in reverse order
			{									//get next digit
				s[i++] = abs(n % 10) + '0';	//get unsigned number for doing abs value and get character to add 0
			}
			while ( n /= 10 );	//delete it
			if (sign < 0)		//check sign less then 0 then add to string
				s[i++] = '-';
			
			s[i] = '\0';
			reverse(s);
		}

		void reverse(char s[]) 
		{
			int c, i, j;
			for ( i = 0, j = strlen(s)-1; i < j; i++, j--) 
			{
				c = s[i];
				s[i] = s[j];
				s[j] = c;
			}
		}