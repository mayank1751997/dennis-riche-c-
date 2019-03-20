7.9	=>	Functions like isupper can be implemented to save space or to
		save time. Explore both possibilities.
		
		#include <stdio.h>
		#include <stdlib.h>

		int isupper(int);

		int main(void)
		{
			int c;

			while ((c = getchar()) != 'x')
			{
				if (c == '\n')
					continue;

				if (isupper(c) == 1)
					printf("true\n");
				else
					printf("false\n");
			}
			return EXIT_SUCCESS;
		}

		int myisupper(int c)
		{
			if (c >= 'A' && c <= 'Z')
				return 1;
			else
				return 0;
		}