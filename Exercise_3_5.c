3.5 => Write the function itob (n, s ,b) that converts the integer n into a base b character representation in the string s. In particular,
	   itob (n, s, 16) formats n as a hexadecimal integer in s.
	   
	    #include<stdio.h>
		#include<string.h>

		#define MAXLINE 100

		void itob(int n,char s[],int b);	//create function with argument
		void reverse(char s[]);

		int main(void)
		{
			int number,base;
			char str[MAXLINE];
			
			number=12345;
			base=4;

			itob(number,str,base);

			printf("%s",str);

			return 0;
		}

		void itob(int n,char s[],int b)
		{
			int i,j,sign;

			if((sign=n)<0)	// record sign 
				n = -n;		//make n positive

			i = 0;

			do
			{
				j = n % b;	//get reminder of the number

				s[i++] = (j <= 9)?j+'0':j+'a'-10;//if number less than 10 return string representation ,otherwise substract 10,
												//add a to hexadecimal  representat 10 to 15 like(a,b,c,d)
			}
			while((n/=b)>0);

			if(sign < 0)
				s[i++]='-';
			
			s[i]='\0';
			
			reverse(s);
		}

		void reverse(char s[])
		{
			int i,j,c;

			for ( i = 0, j = strlen(s)-1; i < j; i++, j--) 
			{
				c = s[i];
				s[i] = s[j];
				s[j] = c;
			}
		}