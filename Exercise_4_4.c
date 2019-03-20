4.4 =>	Add commands to print the top element of the stack without popping, to duplicate it, and to swap the top two elements. Add a command to
		clear the stack.
		
		
		#include <stdio.h>

		int Maxsize = 5;       
		int Stack[5];     
		int Top = -1;            

		int x, y, *a, *b, temp;

		int isempty() //check the stack is empty or not
		{		

		   if(Top == -1)
			  return 1;
		   else
			  return 0;
		}
		   
		int isfull() //check the stack is full or not
		{		

		   if(Top == Maxsize)
			  return 1;
		   else
			  return 0;
		}

		int peek()	//take the top value
		{		
		   return Stack[Top];
		}


		int push(int Data) //push from stack
		{		

		   if(!isfull()) 
		   {
			  Top = Top + 1;   
			  Stack[Top] = Data;
		   } 
		   else
		   {
			  printf("Could not insert data, Stack is full.\n");
		   }
		}

		int main()	// push items on to the stack 
		{
		   push(3);
		   push(5);
		   push(9);
		   push(1);
		   push(12);
		 

			//print data
			for(int i = 0;i<5;i++)
			{
				printf("before swapping stack[%d] = %d\n",i,Stack[i]);

			}

			 printf("Element at top of the stack: %d\n" ,peek());
		   

			//swapping
			 a = &Stack[3];
			 b = &Stack[4];
			 
			int Temp = *b;
			*b = *a;
			*a = Temp;


			printf("After swapping stack[3] =  %d\n",Stack[3]);

			printf("After swapping stack[4]  = %d\n",Stack[4]);

			//clear stack

			for(int i = 0;i<5;i++)
			{   
				Stack[i]=0;
			}

			//print element

			for(int i = 0;i<5;i++)
			{

				printf("After clear stack[%d] = %d\n",i,Stack[i]);

			}

		   return 0;
		}