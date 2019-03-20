4.13 => Write a recursive version of the function reverse (s), which reverses the string s in place.

			 
		#include <stdio.h>
		#include <string.h>
		 
		void reverse_String(char [], int, int);		//reverse the given string
		 
		int main()
		{
			char Str[100], Temp;
			int i, j, Len;
		 
			printf("\n Enter any String :  ");
			scanf("%s",Str);

			Len = strlen(Str);
			reverse_String(Str, 0, Len -1);
		 
			printf("\n String after Reversing = %s\n", Str);
			
			return 0;
		}
		 
		void reverse_String(char Str[], int i, int Len)
		{
			char temp;
			temp = Str[i];
			Str[i] = Str[Len - i];
			Str[Len - i] = temp;
			
			if (i == Len/2)				//because of middle will ne at same position after reverse
			{
				return;
			}
			reverse_String(Str, i + 1, Len);
		}