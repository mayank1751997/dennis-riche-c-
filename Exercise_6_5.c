6.5	=>	Write a function undef that will remove a name and definition
		from the table maintained by lookup and install. 
		
		#include <stdio.h>
		#include <stdlib.h>
		#include <string.h>
		#define HASHSIZE 101
		
		struct nlist
		{		
			struct nlist *next;		
			char *name;			
			char *defn;			
		};
		
		static struct nlist *hashtab[HASHSIZE];	 
		struct nlist *lookup(char *);
		char *strup(char *);		

		unsigned hash(char *s)
		{
			unsigned hashval;
			for (hashval = 0; *s != '\0'; s++)
			hashval = *s + 31 * hashval;
			return hashval % HASHSIZE;
		}


		struct nlist *lookup(char *s)
		{
			struct nlist *np;
			for (np = hashtab[hash(s)]; np != NULL; np = np->next)
			if (strcmp(s, np->name) == 0)
			return np;			
			return NULL;			
		}

			
		struct nlist *install(char *name, char *defn)
		{
			struct nlist *np;
			unsigned hashval;
			if ((np = lookup(name)) == NULL) 
			{	
				np = (struct nlist *) malloc(sizeof(*np));
				if (np == NULL || (np->name = strup(name)) == NULL)
				return NULL;
				hashval = hash(name);
				np->next = hashtab[hashval];
				hashtab[hashval] = np;
			}
			else					
				free((void *) np->defn);		
				if ((np->defn = strup(defn)) == NULL)
				return NULL;
				return np;
		}

		char *strup(char *s)
		{
			char *p;		
			p = (char *) malloc(strlen(s)+1);	
			if (p != NULL)
			strcpy(p, s);
			return p;
		}

		struct nlist *undef(char *name) 
		{
			struct nlist *found;

			found = lookup(name);

			if (found == NULL) 
				return NULL;
			else
			{
				if (found->next != NULL) 
				{
					
					found = found->next;
				} 
				else 
				{
					hashtab[hash(name)] = NULL;
					free((void *) found);
				}
			}
			return found;
		}

		int main(int argc, char *argv[])
		{
			struct nlist *table[4] = 
			{
					(install("abc", "value")),
					(install("def", "value1")),
					(install("hij", "value2")),
					(install("klm", "value3"))
			};

			int i;

			for (i=0; i < 4; i++)
			{
				printf("%s->%s\n", table[i]->name, table[i]->defn);
			}
			undef("def");
			undef("klm");
				
			struct nlist *result;

			char *keys[4] = 
			{
					"abc",
					"def",
					"hij",
					"klm"
			};

			for (i = 0; i < 4; i++) 
			{
				if ((result = lookup(keys[i])) == NULL) 
				{
					printf("not found\n");
				} 
				else 
				{
					printf("%s->%s\n", result->name, result->defn);
				}
			}

			return 0;
		}