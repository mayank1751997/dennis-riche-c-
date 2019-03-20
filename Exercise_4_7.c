4.7	=>	Write a routine ungets (s) that will push back an entire string onto the input. Should ungets know about buf and bufp, or should it just
		use ungetch?
		
		
		#include <stdio.h>
		#include <string.h>
		#define BUFSIZE 100

		char Buf[BUFSIZE]; 
		int Bufp = 0; 

		int getch(void)			//get from buffer
		{
		  return (Bufp > 0) ? Buf[--Bufp] : getchar();
		}
		 
		void ungetch(int c)		//add in to buffer
		{
		  if(Bufp >= BUFSIZE)
			printf("ungetch: too many characters\n");
		  else  
			Buf[Bufp++] = c;  
		}
		 
		void ungets(const char *s)	//get all characters from buffer
		{    
		  size_t i = strlen(s);

		  while (i > 0)
			ungetch(s[--i]);
		}
		 
		int main(void)
		{
		  char *s = "Write If you want to add in Buffer: ";
		  int c;

		  ungets(s);
		  while ((c = getch()) != EOF)
			putchar(c);               
		  return 0;
		}
		