3.6 => Write a version of itoa that accepts three arguments instead of two. The third argument is a minimum field width; the converted number must
		be padded with blanks on the left if necessary to make it wide enough.
		
		
		#include<stdio.h>
		#include<string.h>

		#define MAXLIMIT 100

		void itoa(int n,char s[],int w);
		void reverse(char s[]);

		int main(void) 
		{
			int number,width;
			char str[MAXLIMIT];

			number= -343565;
			width=10;
			
			itoa(number,str,width);

			printf("%s",str);

			return 0;
		}

		void itoa(int n, char s[], int width)
		{
			int i, sign;
			
			if ((sign = n) < 0)	//record sign
				n = -n;		//make n positive
			i = 0;
			do 	//generate digits in reverse order
			{
				s[i++] = n % 10 + '0';	//get next digit
				printf("%d %% %d + '0' = %d\n", n, 10, s[i-1]);
			} 
			while ((n /= 10) > 0);	//delete it
			if (sign < 0)
				s[i++] = '-';
			
			while (i < width )    /*  Only addition to original function  */
				s[i++] = ' ';
			
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