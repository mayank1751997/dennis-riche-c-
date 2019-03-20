5.4 => Write the function strend (s ,t ), which returns 1 if the string t occurs at the end of the string s, and zero otherwise

		#include<stdio.h>
		#include<string.h>

		int strend (char *s, char *t);

		int main()
		{
			char c1[20]="ABCDTEST", c2[10]="TEAT";
			int j;
			j=strend(c1,c2);
			printf("%d\n", j);
			return 0;
		}

		int strend(char *s, char *t)
		{

			while (*s++)
			{
				if (*t == *s) 
					return 1;           
				else
					return 0;
			}
		}
		