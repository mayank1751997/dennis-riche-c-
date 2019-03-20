5.1 => As written, getint treats a + or - not followed by a digit as a valid representation of zero. Fix it to push such a character back on the input
								
								
		#include<stdio.h>
		#include<ctype.h>
		
		#define BUFSIZE 100
		#define SIZE 1000

		int getch(void);
		void ungetch(int);
		char buf[BUFSIZE];
		int bufp = 0;
		int main(void)

		{
			int n,s,array[SIZE],getint(int *);

			for(n=0;n<SIZE && getint(&array[n]) !=EOF; n++)
			{
			   /* For debug purposes */
			   printf("storing in n = %d, getint %d\n", n, array[n]);
			}
			
			printf("storing in n = %d, getint %d\n", n, array[n]);

			for(s=0;s<=n; s++)
				printf("%d",array[s]);

			return 0;
		}

		int getint(int *pn)
		{
			int c,sign;

			while(isspace(c=getch()))
			;
			
			if(!isdigit(c) && c !=EOF && c!='+' && c!='-')
			{
				ungetch(c); /* it's not a number */
				return 0;
			}
			
			sign = (c == '-') ? -1 : 1;

			if(c=='+' || c=='-')
				c = getch();
			
			for(*pn = 0; isdigit(c);c=getch())
				*pn = 10 * *pn + (c-'0');
			
			*pn *= sign;
				
			if(c!=EOF)
				ungetch(c);

			return c;
		}

		int getch(void)
		{
			return (bufp > 0)? buf[--bufp] : getchar();
		}

		void ungetch(int c)
		{
			if(bufp >= BUFSIZE)
				printf("ungetch: too many characters\n");
			else
				buf[bufp++]=c;
		}