5.12 => Extend entab and detab to accept the shorthand entab -m +n. to mean tab stops every n columns, starting at column m. Choose convenient
	    (for the user) default behavior.
		
		#include <stdio.h>
		#include <string.h>
		#include <ctype.h>
		#define MAXTOKEN 100
		#define YES 1
		#define NO 0

		enum {NAME, PARENS, BRACKETS};


		void dcl(void);
		void dirdcl(void);

		int Gettoken(void);
		int Tokentype;              //type of last token
		char Token[MAXTOKEN];       //last token string
		char Name[MAXTOKEN];        //identifier name
		char Datatype[MAXTOKEN];    //data type = char, int, etc.
		char x[1000];
		int Errtoken = NO;
		int Errbreak = NO;

		/* convert declaration to words */
		int main()
		{
			while(Gettoken() != EOF)        //1st token on line
			{
				strcpy(Datatype, Token);    //is the datatype
				x[0] = '\0';
				dcl();      //parse rest of line
				if(Tokentype != '\n')
					printf("syntax error\n");
				printf("%s: %s %s\n", Name, x, Datatype);
			}
			return 0;
		}

		/* dcl: parse a declarator */
		void dcl(void)
		{
			int ns;
			
			for(ns = 0; Gettoken() == '*';) //count stars
				ns++;
			dirdcl();
			while(ns-- > 0)
				strcat(x, " pointer to");
		}

		/* dirdcl: parse a direct declarator */
		void dirdcl(void)
		{
			int Type;
			
			if(Tokentype == '(') //(dcl)
			{
				dcl();
				if(Tokentype != ')')
				{
					printf("error: missing )\n");
					Errtoken = YES;
				}
			}
			else if(Tokentype == NAME) //variable name
				strcpy(Name, Token);
			else
			{
				printf("error: expected name or (dcl)\n");
				Errtoken = YES;
			}
			while((Type = Gettoken()) == PARENS || Type == BRACKETS)
				if(Type == PARENS)
					strcat(x, " function returning");
				else
				{
					strcat(x, " array");
					strcat(x, Token);
					strcat(x, " of");
				}
		}

		int getch(void);
		void ungetch(int c);


		int Gettoken(void)
		{
			int c, getch(void);
			void ungetch(int);
			char *p = Token;
			
			if(Errtoken == YES)
			{
				Errtoken = NO;
				return Tokentype;
			}    
			while((c = getch()) == ' ' || c == '\t')
				;
			if(c == '(')
			{
				if((c = getch()) == ')')
				{
					strcpy(Token, "()");
					return Tokentype = PARENS;
				}
				else
				{
					ungetch(c);
					return Tokentype = '(';
				}
			}
			else if(c == '[')
			{
				for(*p++ = c; *p != ']';)
				{
					*p = getch();
					if(*p != ']')
					{
						if(*p == '\n' || *p == ')' || *p == '(')
						{
							printf("error: missing ]\n");
							ungetch(*p);
							*p = ']';
						}
						else
							*p++;
					}
				}
				*++p = '\0';
				return Tokentype = BRACKETS;
			}
			else if(isalpha(c))
			{
				for(*p++ = c; isalnum(c = getch());)
					*p++ = c;
				*p = '\0';
				ungetch(c);
				return Tokentype = NAME;
			}
			else
				return Tokentype = c;
		}

		#define BUFSIZE 100

		char buf[BUFSIZE];  //buffer for ungetch;
		int bufp = 0; //next free position in bud

		int getch(void) // get a (possibly pushed-back) character  
		{
		   return (bufp > 0) ? buf[--bufp] : getchar();
		}

		void ungetch(int c) // push character back on input
		{
			if(bufp >= BUFSIZE)
				printf("ungetch: too many characnters\n");
			else
				buf[bufp++] = c;
		}