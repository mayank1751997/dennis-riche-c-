3.3 =>	Write a function expand (s1, s2) that expands shorthand notations like a- z in the string s1 into the equivalent complete list abc... xyz in
		s2. Allow for letters of either case and digits, and be prepared to handle cases like a-b-c and a-zO-9 and -a-z. Arrange that a leading or trailing - is
		taken literally.
		
		#include<stdio.h>
		#define MAXLINE 100

		int mgetline(char s[],int maxlimit);
		void expand(char s1[],char s2[]);

		int main(void)
		{
			char s1[MAXLINE],s2[MAXLINE];

			mgetline(s1,MAXLINE);	
			expand(s1,s2);	//expand string from s1

			printf("%s",s2);

			return 0;
		}

		int mgetline(char s[],int lim)
		{
			int i,c;

			for(i=0;i<lim-1 && (c=getchar())!=EOF && c!='\n';++i)
				s[i]=c;

			if(c=='\n')
				s[i++]=c;
			
			s[i]='\0';
		}

		void expand(char s1[],char s2[])
		{
			int i,j,c;

			i=j=0;

			while((c=s1[i++]) != '\0')
				if(s1[i]=='-' && s1[i+1] >=c) //check if next character is '-' and [i+1] is greater than c
				{
					i++;
					while(c<s1[i])	//check range for a-z
					s2[j++]=c++;	
				}
				else
					s2[j++]=c;	//increment character in c

			s2[j]='\0';
		}