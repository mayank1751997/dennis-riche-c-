5.6 => Rewrite appropriate programs from earlier chapters and exercises with pointers instead of array indexing. Good possibilities include getline
	(Chapters 1 and 4), atoi, itoa, and their variants (Chapters 2, 3, and 4), reverse (Chapter 3), and strindex and getop (Chapter 4)
		
		#include <stdio.h>
		#include <ctype.h>

		#define NUMBER '0'		/* a number was found */
		#define BUFSIZE 100		/* max size of value*/

		char Buffer[BUFSIZE];
		int BufferP = 0;

		int getch(void)			/*getch() function which reads a single byte character from input*/
		{
			return (BufferP > 0 ? Buffer[--BufferP] : getchar());
		}

		void ungetch(int c) 		/*ungetch() function pushes the single-byte character ch onto the head of the input queue*/
		{
			if (BufferP >= BUFSIZE)
				printf("ungetch: too many characters\n");
			else
				Buffer[BufferP++] = c;
		}

		int my_getline(char *s, int Limit)	/*Getline function reads the string entered as input*/  
		{
			int c, i;
			i = 0;
			while (--Limit > 0 && (c = getchar()) != EOF && c != '\n')
				*(s + i++) = c;
			if (c == '\n')
				*(s + i++) = c;
			*(s+i) = '\0';
			return i;
		}

		int my_atoi(char *s) 		/* function that coverts string to integer*/
		{
			int Value = 0, Sign;
			for (; isspace((unsigned char) *s); s++);
			Sign = (*s == '-' ? -1 : 1);
			if (*s == '-' || *s == '+')
				s++;
			while (isdigit((unsigned char) *s)) 
			{
				Value = Value * 10 + *s - '0';
				s++;
			}
			return Sign*Value;
		}

		char *my_itoa(int n, char *s) 		/* function that coverts integer to string*/
		{
			char *my_reverse(char *);
			char *p = s;
			int Sign;
			Sign = (n < 0 ? -1 : 1);
			do
			{
				*s++ = ((n % 10) * Sign) + '0';
			} while ((n /= 10));
			if (Sign == -1)
				*s++ = '-';
			*s = '\0';
			my_reverse(p);
			return p;
		}

		char *my_reverse(char *s)		/* function that reverses the string*/
		{
			char *a = s, *b = s, c;
			for (; *b; b++);
			b--;
			while (b > a) 
			{
				c = *a;
				*a = *b;
				*b = c;
				b--;
				a++;
			}
			return s;
		}

		int strindex(char *s, char *t) 		/* function that gives the starting index value to string*/
		{
			int i, j, k;
			
			for (i = 0; *(s+i) != '\0'; i++) 
			{
				for (j = i, k = 0; *(t+k) != '\0' && *(s+j)==*(t+k); j++,  k++);
				if (k > 0 && *(t+k) == '\0')
					return i;
			}
			return -1;
		}

		int getop(char *s)			/* getop:  get next operator or numeric operand */ 
		{
			int getch(void);
			void ungetch(int);
			int i, c;
			while ((*s = c = getch()) == ' ' || c == '\t');
			*(s+1) = '\0';
			if (!isdigit(c) && c != '.')
				return c;
			i = 0;
			if (isdigit(c))
			{
				while (isdigit(c = getch())) 
				{
					*(s + ++i) = c;
				}
				*(s + ++i) = c;
			}
			if (c == '.') 
			{
				while (isdigit(c = getch())) 
				{
					*(s + ++i) = c;
				}
				*(s + ++i) = c;
			}
			*(s+i) = '\0';
			if (c != EOF)
				ungetch(c);
			return NUMBER;
		}

		int main() 
		{
			int Num;
			char b[100];
			char c[]="letap eenimiaj";
			
			printf("\nitoa:%s",my_itoa(456777,b));
			
			printf("\natoi:%d",my_atoi("-64567"));
			
			printf("%s\n", my_reverse(c));
			
			printf("Index of String:%d\n", strindex(c,"patel"));
			return 0;
		}