5.3 => Write a pointer version of the function strcat that we showed in Chapter 2: strcat (s ,t) copies the string t to the end of s.

		#include <stdio.h>
		void strcat1 (char *s, char *t);

		int main(int argc, const char * argv[])
		{
			char s[100];
			char t[50];

			printf("\nEnter string 1:");
			scanf("%s", s);
			printf("Enter string 2:");
			scanf("%s", t);
			strcat1(s, t);
			
			printf("\nThe string after concatenation is:%s", s);			
			return 0;
		}

		void strcat1(char *s, char *t)
		{
			while(*s)   // till it doesn't point to NULL-till string is not empty
			{
				s++;    // points next letter of the string
			}
			while(*t)   // points until second string is not empty
			{
				*s = *t;
				s++;
				t++;
			}
			*s = '\0';
		}