7.1	=>	Write a program that converts upper case to lower or lower case
		to upper, depending on the name it is invoked with, as found in argv [0 ].
		
		
		#include<stdio.h>
		#include<ctype.h>
		#include<string.h>

		int main(int argc,char *argv[])
		{
			int c;

			while ((c = getchar()) != EOF)
				putchar(toupper(c));
			return 0;
			
			while ((c = getchar()) != EOF)
				putchar(tolower(c));
			
			return 0;
		}