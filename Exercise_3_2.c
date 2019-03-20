3.2 =>	Write a function escape(s,t) that converts characters like newline and tab into
		visible escape sequences like \n and \t as it copies the string t to s. Use a switch. Write a
		function for the other direction as well, converting escape sequences into the real characters.
		
		#include <stdio.h>
		#include <conio.h>

		void escape(char s[], char t[]);//declare function with argument

		int main()
		{
			char s[50];
			char t[50] = "Hello,   How are   you";
			escape(s,t);
			printf("%s /n" , s);
		}

		void escape(char s[], char t[])// Define Space and tab is capture
		{
			int a,b;
			while(t[a]!='\0')
			{
				switch(t[a])
				{
					case '\t':
						s[b]='\\';	//copy '\\' character and add t
						++b;
						s[b]='\t';
						break;
					
					case '\n':			//copy '\\' character and add n
						s[b]='\\';
						++b;
						s[b]='\n';
						break;
						
					default:
						s[b] = s[a];
						break;
				}        
				++a;
				++b;
			}
			s[b]='\0';	//not null
		}