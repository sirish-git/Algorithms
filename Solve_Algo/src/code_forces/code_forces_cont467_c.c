
/*
Problem Source:


Editorial/Logic/Ideas Sources: 
1) 
*/


/*
Problem Description:

*/

#include <stdio.h>
#include <string.h>

#define INT_MAX				 99999999
#define INT_MIN				-99999999
#define SUCCESS				0
#define MAX_DIM				101

int input[MAX_DIM];
int counts[601];
long long k, d, t;
int max_scr;



static void test_wrapper()
{
	int test_cases, T;
	long long i, j;
	long long time_cnt, cook_time;
	long long td, tk, time;
	
#ifdef WINDOWS_TEST
	/* Read number of test cases */
	scanf("%d", &T);
	for(test_cases = 1; test_cases <= T; test_cases++)
#endif
	{
		/* Read Inputs */
		scanf("%I64d %I64d %I64d", &k, &d, &t);

		if(k == d || t <= k)
		{
			time_cnt = t;
		}
		else
		{
			td = d;
			tk = k;
			cook_time = time_cnt = 0;
			cook_time += (td < tk) ? td : tk;
			time_cnt += (td < tk) ? td : tk;
			while(td == tk)
			{
			}
		}
	
		printf("%I64d\n", time_cnt);
	}
}

int main()
{
	/* test wrapper function */
	test_wrapper();

	return 0;
}