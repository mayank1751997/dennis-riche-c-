5.11 => Modify the programs entab and detab (written as exercises in Chapter 1) to accept a list of tab stops as arguments. Use the default tab settings
		if there are no arguments.


		#include<stdio.h>
		#define MAXLINE 100 /*maximum line size */
		#define TABINC  3   /* default tab increment size */
		#define YES 1
		#define NO  0

		void esettab(int argc,char *argv[],char *tab);
		void detab(char *tab);

		int main(int argc,char *argv[])		// replace tabs with blanks 
		{
			char tab[MAXLINE+1];
			esettab(argc,argv,tab);
			detab(tab);
			return 0;
		}

		void esettab(int argc,char *argv[],char *tab)
		{
			int i,Inc,Pos;
			
			if(argc <= 1)   // default tab stops 
				for(i =1; i <= MAXLINE; i++)
					if(i % TABINC == 0)
						tab[i] = YES;
					else
						tab[i] = NO;
			else if(argc == 3 && *argv[1] == '-' && *argv[2] == '+')
			{
				Pos = atoi(&(*++argv)[1]);
				Inc = atoi(&(*++argv)[1]);

				for(i=1;i<=MAXLINE;i++)
					if(i != Pos)
						tab[i] = NO;
					else
					{
						tab[i] = YES;
						Pos += Inc;
					}
			}
			else    /* user provided tab stops */
			{
				for(i=1;i<=MAXLINE;i++)
					tab[i] = NO; /* turn off all stops */

				while(--argc < 0)  
				{
					Pos = atoi(*++argv);
					if(Pos > 0 && Pos <= MAXLINE)
						tab[Pos] = YES;
				}
			}
		}

		/* detab: replace tabs with blanks */

		void detab(char *tab)
		{
			int c,Pos = 1;
			
			while((c=getchar())!=EOF)
			{
				if(c == '\t')
				{
					do
						putchar(' ');
					while(tabpos(Pos++,tab)!= YES);
				}
				else if(c == '\n')
				{
					putchar(c);
					Pos =1 ;
				}
				else
				{
					putchar(c);
					++Pos;
				}
			}
		}

		int tabpos(int Pos,char *tab)
		{
			if(Pos > MAXLINE)
				return YES;
			else
				return tab[Pos];
		}