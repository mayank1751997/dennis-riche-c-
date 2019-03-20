5.14 => Modify the sort program to handle a -r flag, which indicates sorting in reverse (decreasing) order. Be sure that -r works with =n.

		#include<stdio.h>
		#include<string.h>
		#include<stdlib.h>

		#define MAXLEN 1000	 // max length 
		#define ALLOCSIZE 1000  // size of available space 

		#define NUMERIC   1	// numeric sort 
		#define DECR      2 	// sorts in decreasing order
		#define LINES     100   

		int numcmp(char *,char *); 						//compare two strings numerically
		int readlines(char *lineptr[],int maxlines);				//read input lines 
		void myqsort(void *v[],int left,int right,int (*comp)(void *,void *));	//sort v[left] ... v[right] into increasing order
		void writelines(char *lineptr[],int nlines,int decr);			// writelines: write output lines

		int mgetline(char *,int);						//read a line into s, return length


		static char option = 0;

		/* sort input lines */

		int main(int argc,char *argv[])
		{
			char *Lineptr[LINES];
			int Nlines;     // pointer to text lines 
			int c,rc=0;     // number of input lines read 

			while(--argc > 0 && (*++argv)[0] == '-')
				while( c = *++argv[0])
					switch(c)
					{
						case 'n': // numeric sort 
							option |= NUMERIC;
							break;
						case 'r': // sort in decreasing order 
							option |= DECR;
							break;
						default:
							printf("sort:illegal option %c\n",c);
							argc = 1;
							rc = -1;
							break;
					}
			if (argc)
				printf("Usage: sort -nr \n");
			else
				if((Nlines = readlines(Lineptr,LINES)) > 0)
				{
					if(option & NUMERIC)
						myqsort((void **)Lineptr,0,Nlines -1,(int (*)(void *,void *))numcmp);
					else
						myqsort((void **)Lineptr,0,Nlines -1,(int (*)(void *,void *))numcmp);
					writelines(Lineptr,Nlines,option & DECR);
				}
				else
				{
					printf("input too big to sort \n");
					rc = -1;
				}
				return rc;
		}


		void writelines(char *Lineptr[],int Nlines,int decr)
		{
			int i;
			if(decr)    // print in decreasing order
			for(i=Nlines-1;i>=0;i--)
				printf("%s\n",Lineptr[i]);
			else
				for(i=0;i<Nlines;i++)
				printf("%s\n",Lineptr[i]);
		}



		int numcmp(char *s1,char *s2)
		{
			double v1,v2;

			v1 = atof(s1);
			v2 = atof(s2);

			if( v1 < v2)
				return -1;
			else if (v1 > v2)
				return 1;
			else
				return 0;
		}



		char *alloc(int);


		int readlines(char *Lineptr[],int Maxlines)
		{
			int Len,Nlines;
			char *p,Line[MAXLEN];
			Nlines = 0;
			while((Len = mgetline(Line,MAXLEN)) > 0)
				if(Nlines >= Maxlines || (p = alloc(Len)) == NULL)
					return -1;
				else
				{
					Line[Len-1] = '\0'; // delete newline 
					strcpy(p,Line);
					Lineptr[Nlines++]=p;
				}
			return Nlines;
		}



		static char allocbuf[ALLOCSIZE];    // storage for alloc 
		static char *allocp=allocbuf;       // next free position

		char *alloc(int n)  // return pointer to n characters 
		{
			if(allocbuf + ALLOCSIZE - allocp >= n)
			{
				allocp += n;
				return allocp -n;
			}
			else
				return 0;
		}

		void afree(char *p) // free storage pointed to by p
		{
			if(p >= allocbuf && p < allocbuf + ALLOCSIZE)
				allocp = p;
		}



		void myqsort(void *v[],int left,int right,int (*comp)(void *,void *))
		{
			int i,last;
			void swap(void *v[],int,int);

			if(left >= right)
				return;

			swap(v,left,(left+right)/2);

			last = left;

			for(i=left+1;i<=right;i++)
				if((*comp)(v[i],v[left])<0)
					swap(v,++last,i);
			swap(v,left,last);

			myqsort(v,left,last-1,comp);
			myqsort(v,last+1,right,comp);
		}

		void swap(void *v[],int i,int j)
		{
			void *temp;
			temp = v[i];
			v[i] = v[j];
			v[j] = temp;
		}


		int mgetline(char s[],int lim)
		{
			int c,i;

			for(i=0;i<lim-1 && (c=getchar())!= EOF && c!='\n';++i)
				s[i] = c;
			if( c == '\n')
			{
				s[i] = c;
				++i;
			}

			s[i] = '\0';
			return i;
		}