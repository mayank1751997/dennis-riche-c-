5.7 => 	Rewrite readlines to store lines in an array supplied by main, rather than calling alloc to maintain storage. How much faster is the program?

		
		#include <stdio.h>
		#include <string.h>

		#define MAXLINES 10 /* max #lines to be sorted */
		#define MAXLEN 1000 /* max length of any input line */
		#define ALLOCSIZE 10000 /* size of available space */

		char *lineptr[MAXLINES]; /* pointers to text lines */
		int readlines(char *lineptr[], int nlines);
		void writelines(char *lineptr[], int nlines);
		void qsort(char *lineptr[], int left, int right);
		
		char *alloc(int);
		void swap(char *v[], int i, int j);
		static char allocbuf[ALLOCSIZE]; /* storage for alloc */
		static char *allocp = allocbuf; /* next free position */

		int main(int argc, char *argv[])	/* sort input lines */
		{
			int nlines; /* number of input lines read */
    
			printf("argc=%d\n",argc);
			
			qsort(argv, 0, argc-1);
			writelines(argv, argc);
			return 0;
			
		}

		
		/* writelines: write output lines */
		void writelines(char *lineptr[], int nlines)
		{
			int i;
			for (i = 1; i < nlines; i++)
				printf("%s\n", lineptr[i]);
		}


		void qsort(char *v[], int left, int right)
		{
			int i, last;

			if (left >= right) /* do nothing if array contains */
				return; /* fewer than two elements */

			swap(v, left, (left + right)/2);
			last = left;

			for (i = left+1; i <= right; i++)
				if (strcmp(v[i], v[left]) < 0)
					swap(v, ++last, i);
			
			swap(v, left, last);
			qsort(v, left, last-1);
			qsort(v, last+1, right);
		}

		/* swap: interchange v[i] and v[j] */
		void swap(char *v[], int i, int j)
		{
			char *temp;
			temp = v[i];
			v[i] = v[j];
			v[j] = temp;
		}