4.11 =>	Modify getop so that it doesn't need to use ungetch. Hint: use an internal static variable

		#include <stdio.h>
		#include <stdlib.h>
		#include <ctype.h>

		#define MAXOP 100	/* max size of operand or operator */
		#define MAXVAL 100	/* max size of value*/
		#define NUMBER '0'	/* a number was found */


		/* getop:  get next operator or numeric operand */
		int getop(char s[]) 
		{
			int i, c;	
			static int Buffer = 0;
			if (Buffer != 0)
			{
				c = Buffer;
				Buffer = 0;
			}
			else
				c = getchar();
			
			for (; c == ' ' || c == '\t'; c = getchar());
			s[0] = c;
			s[1] = '\0';
			if (!isdigit(c) && c != '.')
				return c;
			i = 0;
			if (isdigit(c)) 
			{
				while (isdigit(c = getchar())) 
				{
					s[++i] = c;
				}
				s[++i] = c;
			}
			if (c == '.') 		/* collect fraction part */
			{
				while (isdigit(c = getchar())) 
				{
					s[++i] = c;
				}
			}
			s[i] = '\0';		/* terminate string */
			if (c != EOF)
				Buffer = c;
			return NUMBER;
		}

		int p = 0;		/* next free stack position */
		double Value[MAXVAL];	/* value stack */

		void push(double f) 	/* push:  push f onto stack */
		{
			if (p < MAXVAL)
				Value[p++] = f;
			else
				printf("error: stack full, can't push %g\n", f);
		}
		/* pop:  pop and return top value from stack */
		double pop(void) 
		{
			if (p > 0)
				return Value[--p];
			else 
			{
				printf("error: stack empty\n");
				return 0.0;
			}
		}

		int getop(char []);
		void push(double);
		double pop(void);

		int main() 			/* reverse Polish calculator */
		{
			int Type;
			double Op2;
			char S[MAXOP];
			
			while ((Type = getop(S)) != EOF)
			{
				switch (Type) 
				{
					case NUMBER:
						push(atof(S));
						break;
					case '+':
						push(pop() + pop());
						break;
					case '*':
						push(pop() * pop());
						break;
					case '-':
						Op2 = pop();
						push(pop() - Op2);
						break;
					case '/':
						Op2 = pop();
						if (Op2 != 0.0)
							push(pop() / Op2);
						else
							printf("error: zero divisor\n");
						break;
					case '\n':
						printf("\t%.8g\n", pop());
						break;
					default:
						printf("error: unknown command %s\n", S);
						break;
				}
			}
			return 0;
		}
		