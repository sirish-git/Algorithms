
/*
Problem Source:


Editorial/Logic/Ideas Sources: 
1) 
*/


/*
Problem Description:

*/

#include <stdio.h>
#include <math.h>
#include <string.h>

#define INT_MAX				 99999999
#define INT_MIN				-99999999
#define SUCCESS				0
#define MAX_DIM				101

int input[MAX_DIM];
int n;
int max_scr;



static void test_wrapper()
{
	int test_cases, T;
	int i, j;
	int y_root, rem;
	int factor_found;
	int ans;
	int p_min;
	
#ifdef WINDOWS_TEST
	/* Read number of test cases */
	scanf("%d", &T);
	for(test_cases = 1; test_cases <= T; test_cases++)
#endif
	{
		/* Read Inputs */
		scanf("%d %d", &p, &y);

		//find sqrt
		y_root = (int)sqrt((float)y) + 1;

		ans = -1;
		if(p == 2)
		{
			if(y != 2)
			{
				rem = y % 2;
				if(rem == 0)
				{
					ans = y - 1;
				}
				else
				{
					ans = y;
				}
			}
		}
		else
		{
			//find min
			p_min = p < y_root ? p : y_root;

			//make odd
			if((y % 2) == 0)
			{
				y = y - 1;
			}
			//subtract by 2 to avoid div by 2
			for(i = y; i > p; i-=2)
			{
				factor_found = 0;
				//start from 3
				for(j = 3; j <= p_min; j++)
				{
					rem = i % j;
					if(rem == 0)
					{
						factor_found = 1;
						break;
					}
				}
				if(factor_found == 0)
				{
					ans = i;
					break;
				}
			}
		}
	
		printf("%d\n", ans);
	}
}

int main()
{
	/* test wrapper function */
	test_wrapper();

	return 0;
}