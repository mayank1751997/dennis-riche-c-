4.6	=> 	Add commands for handling variables. (It's easy to provide twenty-six variables with single-letter names.) Add a variable for the most
		recently printed value. 
		
		#include <stdio.h>
		#include <ctype.h>
		#include <math.h>
		 
		#define MAXOP 100  /* max size of operand or operator */
		#define NUMBER '0'  /* signal that a number was found */
		#define BUFSIZE 100
		#define MAXVAL 100  /* maximum depth of val stack */

		int sp = 0;           /* next free stack position */
		double val[MAXVAL], o;   /* value stack */

		int getop(char []);
		double push(double);
		double pop(void);
		int getch(void);
		void ungetch(int);
		double atof(char s[]);
		
		/* reverse Polish calculator */
		main()
		{
			int type, op1, op4;
			double op2,op3;
			char s[MAXOP];
			double variable[26];

			while ((type = getop(s)) != EOF)
			{
				switch (type) 
				{
					case NUMBER:
						push(atof(s));
						break;
						
					case '+':
						op3= push(pop() + pop());
						break;
						
					case '*':
						op3=push(pop() * pop());
						break;
						
					case '-':
						op2 = pop();
						op3=push(pop() - op2);
						break;
						
					case '/':
						op2 = pop();
						if (op2 != 0.0)
						  op3= push(pop() / op2);
						else
							 printf("error: zero divisor\n");
						break;
						
					case '%':
						 op1 = (int) pop();
						 op3 = push((int)pop() % op1);
						 break;

					case '=':
						pop();
						if(op4>='A' && op4<='Z')
							variable[op4-'A']=pop();
						else
							printf("error: no variable\n");
						break;
						
					case '\n':
						op3=pop();
						printf("\t%.8g\n",op3);
						break;
					
					default:
						if (type>='A' && type<='Z')
							push(variable[type-'A']);
						else if(type==op3)
							push(op3);
						else
							printf("error: unknown command %s\n", s);
						break;
				}
				op4=type;
			}
			return 0;
		}


		/* push: push f onto value stack */
		double push(double f)
		{
			if (sp < MAXVAL)
				 val[sp++] = f;
			else
				 printf("error: stack full, can't push %g\n", f);
			return f;
		}
		
		/* pop: pop and return top value from stack */
		double pop(void)
		{
			if (sp > 0)
				return val[--sp];
			else
			{
				printf("error: stack empty\n");
				return 0.0;
			}
		}


		/* getop: get next character or numeric operand */
		int getop(char s[])
		{
			int i, c;
			while ((s[0] = c = getch()) == ' ' || c == '\t')
				;
			s[1] = '\0';
			if (!isdigit(c) && c != '.')
				return c;      /* not a number */
			i = 0;
			if (isdigit(c))    /* collect integer part */
				while (isdigit(s[++i] = c = getch()))
				   ;
			if (c == '.')      /* collect fraction part */
				while (isdigit(s[++i] = c = getch()))
			  s[i] = '\0';
			  if (c != EOF)
				  ungetch(c);
			  return NUMBER;
		}


		int getch(void) 	/* get a (possibly pushed-back) character */
		{
			char buf[BUFSIZE];     /* buffer for ungetch */
			int bufp = 0;          /* next free position in buf */
			return (bufp > 0) ? buf[--bufp] : getchar();
		}
		
		void ungetch(int c)    /* push character back on input */
		{
			char buf[BUFSIZE];     /* buffer for ungetch */
			int bufp = 0;          /* next free position in buf */
				if (bufp >= BUFSIZE)
					printf("ungetch: too many characters\n");
				else
					buf[bufp++] = c;
		}

		double atof(char s[])
		{
			double val, power;
			int i, sign;
			for (i = 0; isspace(s[i]); i++) /* skip white space */
				;
			sign = (s[i] == '-') ? -1 : 1;
			if (s[i] == '+' || s[i] == '-')
				i++;
			for (val = 0.0; isdigit(s[i]); i++)
				val = 10.0 * val + (s[i] - '0');
			if (s[i] == '.')
				i++;
			for (power = 1.0; isdigit(s[i]); i++) 
			{
				val = 10.0 * val + (s[i] - '0');
				power *= 10;
			}
			return sign * val / power;
		}