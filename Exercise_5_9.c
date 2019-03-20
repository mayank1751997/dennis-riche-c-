5.9	=>	Rewrite the routines day_of_year and month_day with pointers instead of indexing.

		#include <stdio.h>

		char Yeardays[2][13] = 
		{
			{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
			{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
		};

		int day_of_year(int Year, int Month, int Day) 
		{
			int i, Leap;
			Leap = (Year%4 == 0 && Year%100 != 0) || Year%400 == 0;
			for (i = 1; i < Month; i++)
				Day = Day + (*(*(Yeardays+Leap)+i));
			return Day;
		}

		void month_day(int Year, int Daycount, int *Xmonth, int *Xday) 
		{
			int i, Leap;
			Leap = (Year%4 == 0 && Year%100 != 0) || Year%400 == 0;
			for (i = 1; Daycount > Yeardays[Leap][i]; i++)
				Daycount = Daycount -( *(*(Yeardays+Leap)+i));
			*Xmonth = i;
			*Xday = Daycount;
		}

		int main() {
			
			int dd,mm,yyyy;
			printf("\nEnter Year(in format YYYY):");
			scanf("%d",&yyyy);
			printf("\nEnter Month(in format MM):");
			scanf("%d",&mm);
			printf("\nEnter Day(in year DD):");
			scanf("%d",&dd);
			printf("\nDate: [%d.%d.%d]",yyyy,mm,dd);
			printf("\n%d Days.\n", day_of_year(yyyy,mm,dd));
			return 0;
		}