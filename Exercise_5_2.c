5.2 => Write getfloat, the floating-point analog of getint. What type does getfloat return as its function value?


		#include <stdio.h>
		#include <ctype.h>
		#include <math.h>

		#define BUFSIZE 100

		int getfloat(float *);
		int getch(void);
		void ungetch(int);

		int Buf[BUFSIZE];
		int Bufp = 0;

		int main(void)
		{
			float f;
			printf("enter number :");
			getfloat(&f);

			printf("f: %f\n", f);

			return 0;
		}

		int getfloat(float *fp)				//get float value
		{
			int c, Sign;
			float Dec = 0;

			while(isspace(c = getch()))			//for space checking
				;
			
			if (!isdigit(c) && c != EOF && c != '-')
			{			//for digit, end of file & sign checking
				return 0;
			}

			if (c == '-')
			{
				Sign = -1;
				c = getch();
			}
			else 
			{
				Sign = 1;
			}

			for (*fp = 0; isdigit(c); c = getch())
			{
				*fp = 10 * *fp + (c - '0');
			}

			if (c == '.') 
			{
				c = getch();

				for (int i = 1; isdigit(c); c = getch(), i++)
				{
					Dec = Dec + (c - '0');        	
					printf("c: %c\tf: %f\tres: %f\n", c, (c - '0'));		 
				}
			}

			*fp *= Sign;

			if (c != EOF) 
			{
				ungetch(c);
			}
			return c;
		}

		int getch(void)						//get value from buffer
		{
			return (Bufp > 0) ? Buf[--Bufp] : getchar();
		}

		void ungetch(int c)					//add value in buffer
		{
			if (Bufp >= BUFSIZE)
				printf("error: buffer filled\n");
			else
				Buf[Bufp++] = c;
		}