5.13 => 	Write the program tail, which prints the last n lines of its input. By default, n is 10, let us say, but it can be changed by an optional 
		argument, so that 	{tail -n}.
		prints the last n lines. The program should behave rationally no matter how unreasonable the input or the value of n. Write the program so it makes the
		best use of available storage; lines should be stored as in the sorting program of Section 5.6, not in a two-dimensional array of fixed size
		
		
		#include <stdio.h>
		#include <stdlib.h>
		#include <string.h>
		#include <ctype.h>

		#define ALLOCSIZE 10000 /* size of available space */
		#define MAXLINES 10 /* max #lines to be sorted */
		#define PRINTLINES 5 /* max #lines to be sorted */
		#define MAXLEN 10 /* max length of any input line */

		int strcompare(char *s1, char *s2);
		int isdirectory(char *s);

		char *lineptr[MAXLINES]; /* pointers to text lines */

		int ignorecase = 0; /* 1 if case insensitive */
		int directory = 0; /* 1 if sorting in directory order */

		static char allocbuf[ALLOCSIZE]; /* storage for alloc */
		static char *allocp = allocbuf; /* next free position */

		char *alloc(int);
		void afree(char *p);

		int numcmp(char *, char *);
		int strcmpignore(char *, char *);

		int _getline(char *, int);
		int readlines(char *lineptr[], int nlines);
		void writelines(char *lineptr[], int nlines);

		void qsort(void *lineptr[], int left, int right, int (*comp)(void *, void *), int order);

		int main(int argc, char **argv)
		{
			int nlines; /* number of input lines read */
			int numeric = 0; /* 1 if numeric sort */
			int order = 1; /* 1 if sorting in increasing order*/

			int c, i;
			char *t;

			while (--argc > 0 && *(*++argv) == '-') 
			{
				while ((c = *++(*argv)) != '\0') 
				{
					switch (c)
					{
						case 'n':
							numeric = 1;
							break;
						case 'r':
							order = 0;
							break;
						case 'f':
							ignorecase = 1;
							break;
						case 'd':
							directory = 1;
							break;
						default:
							break;
					}
				}
			}

			if ((nlines = readlines(lineptr, MAXLINES)) >= 0) 
			{
				writelines(lineptr, nlines);
				return 0;
			} 
			else 
			{
				printf("error: input too big to sort=%d\n",nlines);
				return 1;
			}
		}

		int strcompare(char *s1, char *s2)
		{
			if (directory) 
			{
				while(*s1 != '\0' && !isdirectory(s1))
					s1++;
				while(*s2 != '\0' && !isdirectory(s2))
					s2++;
				if (ignorecase) 
				{
					while (tolower(*s1) == tolower(*s2))
					{
						if (*s1 == '\0')
							return 0;
						s1++;
						s2++;
						while(*s1 != '\0' && !isdirectory(s1))
							s1++;
						while(*s2 != '\0' && !isdirectory(s2))
							s2++;
					}
					return tolower(*s1) - tolower(*s2);
				} 
				else
				{
					while (*s1 == *s2)
					{
						if (*s1 == '\0')
							return 0;
						s1++;
						s2++;
						while(*s1 != '\0' && !isdirectory(s1))
							s1++;
						while(*s2 != '\0' && !isdirectory(s2))
							s2++;
					}
					return *s1 - *s2;
				}
			} 
			else
			{
				if (ignorecase) 
				{
					return strcmpignore(s1, s2);
				} 
				else 
				{
					return strcmp(s1, s2);
				}
			}
		}

		int isdirectory(char *s)
		{
			return isdigit(*s) || isalpha(*s) || isspace(*s);
		}

		char *alloc(int n) /* return pointer to n characters */
		{
			if (allocbuf + ALLOCSIZE - allocp >= n) 
			{ 
				allocp += n;
				return allocp - n; /* old p */
			} 
			else
				return 0;
		}

		void afree(char *p) /* free storage pointed to by p */
		{
			if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
				allocp = p;
		}

		/* numcmp: compare s1 and s2 numerically */
		int numcmp(char *s1, char *s2)
		{
			double v1, v2;

			v1 = atof(s1);
			v2 = atof(s2);
			if (v1 < v2)
				return -1;
			else if (v1 > v2)
				return 1;
			else
				return 0;
		}

		int strcmpignore(char *s1, char *s2)
		{
			for (; tolower(*s1) == tolower(*s2); ++s1, ++s2)
				if (*s1 == '\0')
					return 0;
			return tolower(*s1) - tolower(*s2);
		}

		/* readlines: read input lines */
		int readlines(char *lineptr[], int maxlines)
		{
			int len, nlines;
			char *p, line[MAXLEN];

			nlines = 0;
			while ((len = _getline(line, MAXLEN)) > 0)
				if (nlines >= maxlines || (p = alloc(len)) == NULL)
					return nlines;
				else 
				{
					line[len-1] = '\0'; /* delete newline */
					strcpy(p, line);
					lineptr[nlines++] = p;
				}
			return nlines;
		}

		/* qsort: sort v[left]...v[right] into increasing/decreasing order */
		void qsort(void *v[], int left, int right, int (*comp)(void *, void *), int order)
		{
			int i, last;
			void swap(void *v[], int, int);

			if (left >= right) /* do nothing if array contains */
				return; /* fewer than two elements */
			swap(v, left, (left + right)/2);
			last = left;
			for (i = left+1; i <= right; i++)
				if (order && (*comp)(v[i], v[left]) < 0)
					swap(v, ++last, i);
				else if (!order && (*comp)(v[i], v[left]) > 0)
					swap(v, ++last, i);
			swap(v, left, last);
			qsort(v, left, last-1, comp, order);
			qsort(v, last+1, right, comp, order);
		}

		/* swap: interchange v[i] and v[j] */
		void swap(void *v[], int i, int j)
		{
			void *temp;
			temp = v[i];
			v[i] = v[j];
			v[j] = temp;
		}

		/* writelines: write output lines */
		void writelines(char *lineptr[], int nlines)
		{
			int i, printlines=0;
			if(nlines>PRINTLINES)
				printlines= PRINTLINES;
			else 
				printlines= 0;
			for (i = nlines-1; i>=printlines; --i)
				printf("%s\n", lineptr[i]);
		}

		int _getline(char s[], int max)
		{
			int c, i, l;

			for (i = 0, l = 0; (c = getchar()) != EOF && c != '\n'; ++i)
				if (i < max - 1)
					s[l++] = c;
			if (c == '\n' && l < max - 1)
				s[l++] = c;
			s[l] = '\0';

			return l;
		}