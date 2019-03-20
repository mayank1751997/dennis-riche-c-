3.1 =>  Our binary search makes two tests inside the loop, when one would suffice (at
		the price of more tests outside.) Write a version with only one test inside the loop and measure
		the difference in run-time.
		
		
		#include <stdio.h> // Include the header file
		#include <conio.h>
		
		
		int binsearch(int x,int v[],int n);	//declare function to search

		int main(void)
		{
			int arr[]={2,4,6,7,9,12,15,17,20,25};	//to search arguments in array
			printf("%d",binsearch(9,arr,10));		//x value, array , value

			return 0;
		}

		int binsearch(int x,int v[],int n)		//binsearch use for sorted array
		{
			int low,high,mid;
			
			low=0;
			high=n-1;
							
			while (low <= high)	//if mid element greater than search element search continuos 
			{
				mid = (low+high)/2;
				
				if (x < v[mid])
				high = mid - 1;
				
				else if (x > v[mid])
				low = mid + 1;
				
				else 
				return mid;	//return position of search element
			
			}
			
			return -1;
				
		}