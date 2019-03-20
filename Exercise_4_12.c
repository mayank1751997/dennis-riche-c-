4.12 => Adapt the ideas of printd to write a recursive version of itoa; that is, convert an integer into a string by calling a recursive routine


		#include<stdio.h>
		#include<string.h>
		#include<limits.h>
		#include<math.h>
		
		void itoa(int n, char s[]);
		void reverse(char s[]);

		int main()
		{
			char c[20];
			int j;
			printf("Enter a Number:");
			scanf("%d",&j);
			itoa(j,c);
			printf("String :%s\n",c);
			return 0;
		}

		void itoa(int n, char s[])
		{
			static int i=0;
			if((n / 10))
				itoa(n /10, s);			 
			else
			{			  
			  if(n < 0)
			   s[i++] = '-';
			}
			  s[i++] = abs(n % 10) + '0';
			  s[i] = '\0';
		}
		