4.10 =>	An alternate organization uses getline to read an entire input line; this makes getch and ungetch unnecessary. Revise the calculator to use
		this approach.
		
		
		#include<stdio.h>
		#include<string.h>

		int main ()
		{
		  char Name[40];
		  char *a = Name;
		  size_t Bufsize = 40;
		  size_t Character; 

		  printf("Enter your Name: ");
		  Character = getline (&a,&Bufsize,stdin);	//get line function
								
		  printf("Hello, Your Name is : %s", Name); //take whole line from buffer

		  return 0;
		} 