5.8	=>	There is no error checking in day_of _year or month_day. Remedy this defect.

		#include <stdio.h>
		void leap(int Year,int Month,int Day);
		#define cyr 365
		#define lyr 366
		static int Daytab1[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
		static int Daytab2[13]={0,31,29,31,30,31,30,31,31,30,31,30,31};
		static int i =0;

		int main()
		{   
			int Year,Month,Day;
			
			printf("Enter a Day: ");
			scanf("%d",&Day);
			printf("Enter a month: ");
			scanf("%d",&Month);
			printf("Enter a year: ");
			scanf("%d",&Year);
			leap(Year,Month,Day);
			return 0;
		}

		void leap(int Year,int Month,int Day)
		{
			int Result;
			if(Year%4 == 0)
			{
				if( Year%100 == 0)
				{
					// year is divisible by 400, hence the year is a leap year
					if ( Year%400 == 0)
					{  
						while(i<Month)
						{
							Daytab2[i] = Daytab2[i] + Daytab2[i+1];
							i++;
						}
						Result=Daytab2[i]+Day;	// Day = lyr - Day;
						printf("%d\n",Result);	
						printf("%d is a leap year.\n", Year);
					}
					else
					{
						while(i<Month)
						{
							Daytab1[i] = Daytab1[i] + Daytab1[i+1];
							i++;
						}
						Result=Daytab1[i]+Day;	//  Day = cyr - Day;
						printf("%d\n",Day);						
					}        
				}
				else	
				{    
					while(i<Month)
					{
						Daytab2[i] = Daytab2[i] + Daytab2[i+1];
						i++;
					}
					Result=Daytab2[i]+Day;

					printf("%d\n",Result);     
					printf("%d is a leap year.\n",Year);
				}
			}
			else
			{
				while(i<Month)
				{
					Daytab1[i] = Daytab1[i] + Daytab1[i+1];
					i++;
				}
				Result=Daytab1[i]+Day;	 // Day = cyr - Day;
				printf("%d\n",Result);										
			}
		}