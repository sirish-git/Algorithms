
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
int n;
int max_scr;



static void test_wrapper()
{
	int test_cases, T;
	int i, j;
	int ans;
	int val, nz_cnt;
	
#ifdef WINDOWS_TEST
	/* Read number of test cases */
	scanf("%d", &T);
	for(test_cases = 1; test_cases <= T; test_cases++)
#endif
	{
		/* Read Inputs */
		scanf("%d", &n);
		//clear counts array
		for(i = 0; i <= 600; i++)
		{
			counts[i] = 0;
		}
		//read values
		for(i = 0; i < n; i++)
		{
			scanf("%d", &val);
			if(val > 0)
			{
				counts[val] = 1;
			}
		}
		//read no of non-zero values
		nz_cnt = 0;
		for(i = 0; i <= 600; i++)
		{
			if(counts[i] == 1)
			{
				nz_cnt++;
			}
		}
	
		printf("%d\n", nz_cnt);
	}
}

int main()
{
	/* test wrapper function */
	test_wrapper();

	return 0;
}