4.1 => Write the function strrindex (s, t), which returns the position of the rightmost occurrence of t in s, or - 1 if there is none.
	   
	   
	   #include<stdio.h>
	   #include<conio.h>

		int strindex(char source[],char searchfor[]); //create function with argument

		int main(void)
		{
			char Line[] = "abcdefghijklefghhh";	
			char Pattern[] = "efg";

			int find;

			find = strindex(Line, Pattern); 

			printf("find the right index: %d\n", find);

		}

		int strindex(char s[],char t[])		//result of match index
		{
			int i,j,k, Result;

			Result = -1;		//pattern is not match

			for(i=0;s[i]!='\0';i++)
			{
				for(j=i,k=0;t[k]!='\0' && s[j]==t[k];j++,k++)
					;
				if(k>0 && t[k] == '\0')		
					Result = i;
			}
			return Result;
		}
		