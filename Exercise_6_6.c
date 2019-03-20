6.6	=>	Implement a simple version of the #define processor (i.e., no arguments) 
		suitable for use with C programs, based on the routines of this section.
		You may also find getch and ungetch helpful.
		
		#include <stdio.h>
		#include <ctype.h>
		#define BUFSIZE 100

		int getch(void);
		void ungetch(int c);
		#define PI 3.14

		void main()
		{
			int c;
			static float r;
		 
			c = getch();
			while( isdigit( c ) )
			{
			  r = r*10 + c - '0';
			  c = getch();
			}
			ungetch( c );
			printf( "Enter Radius = %f\n", r);

			float Result = PI*r*r;		
			printf( "Area Of Circle = %f\n",Result);
		}

		char buf[BUFSIZE];  
		int bufp = 0;       
		int getch(void) 
		{
			return (bufp > 0) ? buf[--bufp] : getchar();
		}

		void ungetch(int c) 
		{  
			if(bufp >= BUFSIZE)
				printf("ungetch: too many characters\n");
			else
				buf[bufp++] = c;
			return;
		}