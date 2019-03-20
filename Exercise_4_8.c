4.8	=>	Suppose that there will never be more than one character of pushback. Modify getch and ungetch accordingly.


		#include <stdio.h>

		char pushed = 0;

		int getch(void) 			/*getch() function which reads a single byte character from input*/
		{
			char A;
			if (pushed != 0) 
			{
				A = pushed;
				pushed = 0;
				return (unsigned char) A;
			}
			return getchar();
		}

		void ungetch(char C)			/*ungetch() function pushes the single-byte character ch onto the head of the input queue*/
		{
			pushed = C;
		}

		int main () 				
		{
			
			ungetch('x');
			ungetch('a');		       /* x was lost */
			putchar(getch());
			return 0;	
		}