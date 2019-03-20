5.20 =>	Expand dcl to handle declarations with function argument types, qualifiers like const, and so on.

		#include <stdio.h>
		#include <string.h>
		#include <ctype.h>
		#include <stdlib.h>
		#define MAXTOKEN 100
		#define BUFSIZE 100

		enum {NAME, PARENS, BRACKETS};
		enum {NO, YES};

		void dcl(void);         //parse a declarator
		void dirdcl(void);      //parse a direct declarator
		void errmesg(char *);  
		int gettoken(void);

		int Tokentype;              //type of last token
		char Token[MAXTOKEN];       //last token string
		char Name[MAXTOKEN];        //identifier name
		char Datatype[MAXTOKEN];    //data type = char, int, etc.
		char Out[1000];
		int Errtoken = NO;
		int Errbrack = NO;

		/* convert declaration to words */
		int main()
		{
			while(gettoken() != EOF)        //1st token on line
			{
				strcpy(Datatype, Token);    //is the datatype
				Out[0] = '\0';
				dcl();      //parse rest of line
				if(Tokentype != '\n')
					printf("syntax error\n");
				printf("%s: %s %s\n", Name, Out, Datatype);
			}
			return 0;
		}

		/* dcl: parse a declarator */
		void dcl(void)
		{
			int Ns;	
			for(Ns = 0; gettoken() == '*';) //count stars
				Ns++;
			dirdcl();
			while(Ns-- > 0)
				strcat(Out, " pointer to");
		}

		/* dirdcl: parse a direct declarator */
		void dirdcl(void)
		{
			int Type;
			void paramdcl(void);    //declarator analysis with parameters 
			
			if(Tokentype == '(') //(dcl)
			{
				dcl();
				if(Tokentype != ')')
					errmesg("error: missing )\n");
			}
			else if(Tokentype == NAME) //variable name
			{
				if(Name[0] == '\0')
					strcpy(Name, Token);
			}
			else
				Errtoken = YES;
			while((Type = gettoken()) == PARENS || Type == BRACKETS || 
													Type == '(')
				if(Type == PARENS)
					strcat(Out, " function returning");
				else if(Type == '(')
				{
					strcat(Out, " function taking");
					paramdcl();
					strcat(Out, " and returning");
				}
				else
				{
					strcat(Out, " array");
					strcat(Out, Token);
					strcat(Out, " of");
				}
		}

		/* errmesg: error message */
		void errmesg(char *msg)
		{
			printf("%s", msg);
			Errtoken = YES;
		}

		void declspec(void);    //specification declaration
		int typespec(void);     //type specifier
		int typedesc(void);     //descriptor type

		/* paramdcl: declarator analysis with parameters */
		void paramdcl(void)
		{
			do
			{
				declspec(); //specification declaration
			} while(Tokentype == ',');
			if(Tokentype != ')')
				errmesg("missing ) in declarator of parameters\n");
		}

		/* specification declaration */
		void declspec(void)
		{
			char temp[MAXTOKEN];
			
			temp[0] = '\0';
			gettoken();
			do
			{
				if(Tokentype != NAME)
				{
					Errtoken = YES;
					dcl();
				}
				else if(typespec() == YES) // type specifier
				{
					strcat(temp, " ");
					strcat(temp, Token);
					gettoken();
				}
				else if(typedesc() == YES) //descriptor type
				{
					strcat(temp, " ");
					strcat(temp, Token);
					gettoken();
				}
				else
					errmesg("error: unknown type in the parameter list\n");
			} while(Tokentype != ',' && Tokentype != ')');
			strcat(Out, temp);
			if(Tokentype == ',')
				strcat(Out, ",");
		}

		/* type specifier */
		int typespec(void)
		{
			static char *Types[] = {"char", "int", "void"};
			char *ptypes = Token;
			int Result, i;
		   
			Result = NO;
			for(i = 0; i < 3; i++)
				if(strcmp(ptypes, *(Types + i)) == 0)
					return Result = YES;
				else
					Result = NO;
			return Result;
				
		}

		/*  descriptor type */
		int typedesc(void)
		{
			static char *Typed[] = {"const", "volatile"};
			char *ptd = Token;
			int Result, i;
			
			Result = NO;
			for(i = 0; i < 2; i++)
				if(strcmp(ptd, *(Typed + i)))
					return Result = YES;
				else
					Result = NO;
			return Result;
		}

		int getch(void);        //get a (possibly pushed-back) character
		void ungetch(int);    //push character back on input

		int gettoken(void)
		{
			int c;
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
							p++;
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

		char Buf[BUFSIZE];          
		int Bufp = 0;               

		int getch(void) // get a character  
		{
		   return (Bufp > 0) ? Buf[--Bufp] : getchar();
		}

		void ungetch(int c) // push character back on input
		{
			if(Bufp >= BUFSIZE)
				printf("ungetch: too many characnters\n");
			else
				Buf[Bufp++] = c;
		}

