
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
#define MAX_DIM				41

static signed long long dp[MAX_DIM][MAX_DIM];
static signed long long N, M, Q;
static signed long long max_scr;



static void test_wrapper()
{
#ifdef WINDOWS_TEST
	int test_cases, T;
	char str[50];
	signed long long correct_ans;
#endif
	signed long long i, j;
	int val;
	
#ifdef WINDOWS_TEST
	/* Read number of test cases */
	scanf("%d", &T);
	for(test_cases = 1; test_cases <= T; test_cases++)
#endif
	{
		/* Read Inputs */
		scanf("%I64d %I64d %I64d", &N, &M, &Q);
		//read inputs
		for(i = 0; i < N; i++)
		{
			for(j = 0; j < M; j++)
			{
				scanf("%d", &val);
				if(val == 0)
				{
					//dp of 1x1 with val 0 is 1
					dp[i][j] = 1;
				}
				else
				{
					dp[i][j] = 0;
				}
			}
		}

		//build dp array for all rectangles with all 0's
		//for first row
		i = 0;
		for(j = 1; j < M; j++)
		{
			dp[i][j] += dp[i][j-1];
		}
		//for first col
		j = 0;
		for(i = 1; i < N; i++)
		{
		}
		//for remaining elements
		for(i = 1; i < N; i++)
		{
			for(j = 1; j < M; j++)
			{
			}
		}

	}
}

int main()
{
#ifdef WINDOWS_TEST
	printf("\n\n ++++++++ Code forces - 376a ++++++++\n\n");

	freopen("../test/code_forces/code_forces_376a.txt", "r", stdin);
#endif

	/* test wrapper function */
	test_wrapper();

	return 0;
}