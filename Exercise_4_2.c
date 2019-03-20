4.2 => Extend atof to handle scientific notation of the form 123.45e-6
       where a floating-point number may be followed by e or E and an optionally signed exponent.
	   
		#include<stdio.h>
		#include<ctype.h>
		#include<math.h>
		#define MAXLINE 100

		double FuncAtof(char s[]);
		int Getline(char Line[],int Maxline);

		int main(void)			//main function consist the Getline and FuncAtof functions
		{
			char String[MAXLINE];
			double Number;
			printf("\nEnter your string for scientific notation check:");
			Getline(String,MAXLINE);	//Getline Function is called which is used to parse the entered string

			Number=FuncAtof(String);	//FuncAtof function is called which is used to return the final string 
						//to float value considering scientific notaions
			printf("\n%f",Number);	//eg1: 1 -> 1.00

			return 0;
		}

		double FuncAtof(char s[])		/*myatof: return double from string input.
										Can also account for scientific input
										including negative and/or non-integer 
										exponent, and white space between
										base, e, and exponent.
										e.g. "12.345 e -5.337" = 0.00005681867*/
		{
			double Val,Pow;
			int Sign,i,Esign,Exp;   
			int Power(int Base,int Exp);    
				
			for(i=0;isspace(s[i]);i++)
				;

			Sign=(s[i]=='-')?-1:1;

			if(s[i]=='+' || s[i] == '-')
				i++;

			for(Val=0.0;isdigit(s[i]);i++)
				Val = 10.0 * Val + (s[i] - '0');
			
			if(s[i]=='.')
				i++;

			for(Pow=1.0;isdigit(s[i]);i++)
			{
				Val = 10.0 * Val + (s[i] - '0');
				Pow *= 10.0;
			}

			if(s[i]=='e' || s[i] =='E')
				i++;
			if(s[i]=='+' || s[i] =='-')
			{
				Esign=s[i];
				i++;
			}

			for(Exp=0;isdigit(s[i]);i++)
				Exp=10.0 * Exp + (s[i] - '0');
			
			if( Esign == '-')
				return Sign * (Val / Pow) / Power(10,Exp);
			else
			
				return Sign * (Val / Pow) * Power(10,Exp);
		}

		int Getline(char s[],int Limit)
		{
			int i,c;

			for(i=0;i<Limit-1 && (c=getchar())!=EOF && c!='\n';++i)
						
				s[i] = c;
				
			if(c=='\n')
			
				s[i++]=c;
			
			s[i]='\0';

		}					//Getline function reads the string entered as input
			
		int Power(int Base,int Exp)
		{
			int power;
			power=1;
		   
			while(Exp-- > 0)
				power *=Base;

			return power;			//return the power with base and its exponent
		}