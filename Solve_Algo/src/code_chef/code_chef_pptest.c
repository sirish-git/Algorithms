
/*
Problem Source:
https://www.codechef.com/problems/PPTEST

Editorial/Logic/Ideas Sources: 
1) 
*/


/*
Problem Description:



*/

#include <stdio.h>
#include <string.h>

#define RESET				999999
#define INT_MAX				99999999
#define INT_MIN				-99999999
#define DP_EMPTY			-1
#define DP_INIT				-9999
#define SUCCESS				0
#define MAX_DIM				101

static signed long long count[MAX_DIM], points[MAX_DIM], time[MAX_DIM];
static signed long long N, W;
static signed long long max_scr;
static signed int dp[MAX_DIM][MAX_DIM];


/* Actual algo funciton */
static int core_fn(int pos, int rem_time)
{
	int i, j;
	int scr, max;
	int c, p, t;

	/* Base case: bounds */
	if(pos >= N)
	{
		return 0;
	}
	if(rem_time <= 0)
	{
		return 0;
	}

	/* return dp result */
	if(dp[pos][rem_time] != -1)
	{
		return dp[pos][rem_time];
	}

	/* core algo iterations */
	max = 0;
	for(i = pos; i < N; i++)
	{
		t = time[i];
		if(t <= rem_time)
		{
			c = count[i];
			p = points[i];
			scr = c * p;
			scr += core_fn(i+1, rem_time - t);
			if(scr > max)
			{
				max = scr;
			}
		}
	}

	/* store dp result: max score for position with remaing elements */
	dp[pos][rem_time] = max;

	return max;
}

static void test_wrapper()
{
#if 1//def WINDOWS_TEST
	int test_cases, T;
	char str[10];
	signed long long ans, correct_ans;
#endif
	signed long long i, j;
	
#if 1//def WINDOWS_TEST
	/* Read number of test cases */
	scanf("%d", &T);
	for(test_cases = 1; test_cases <= T; test_cases++)
#endif
	{
		/* Read Inputs */
		scanf("%I64d %I64d", &N, &W);
		for(i = 0; i < N; i++)
		{
			scanf("%I64d %I64d %I64d", &count[i], &points[i], &time[i]);
		}

		/* Reset dp buffer */
		for(i = 0; i < N; i++)
		{
			for(j = 0; j <= W; j++)
			{
				dp[i][j] = -1;
			}
		}

		/* algo function call */
		max_scr = core_fn(0, W);

		
#ifdef WINDOWS_TEST
		/* Print output */
		printf("#%d %I64d\n", test_cases, max_scr);

		/* Test the answer with reference output kept in input file */
		scanf("%s", str);
		scanf("%I64d", &correct_ans);
		ans = max_scr;
		if(correct_ans == ans)
		{
			printf(" Success: Output is matching with Reference output\n");
		}
		else
		{
			printf(" !!FAILURE: Output is NOT matching with Reference output\n");
		}
#else
		printf("%I64d\n", max_scr);
#endif
	}
}

int main()
{
#ifdef WINDOWS_TEST
	printf("\n\n ++++++++ Code Chef - PPTEST ++++++++\n\n");

	freopen("../test/code_chef/code_chef_PPTEST.txt", "r", stdin);
#endif

	/* test wrapper function */
	test_wrapper();

	return 0;
}