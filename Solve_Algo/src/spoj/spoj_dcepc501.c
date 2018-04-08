
/*
Problem Source:
http://www.spoj.com/problems/DCEPC501/

Editorial/Logic/Ideas Sources: 
1) 
*/


/*
Problem Description:



*/

#include <stdio.h>
#include <string.h>

#define INT_MAX				9999999999
#define INT_MIN				-9999999999
#define SUCCESS				0
#define MAX_DIM				100011

static signed long long input[MAX_DIM], dp[MAX_DIM];
static signed long long N;
static signed long long max_scr;


/* Actual algo funciton */
static signed long long core_fn(int pos)
{
	signed long long i, j, max, val;

	/* Base case: bounds */
	if(pos >= N)
	{
		return 0;
	}

	/* return dp result */
	if(dp[pos] != -1)
	{
		return dp[pos];
	}

	/* core algo */
	max = INT_MIN;
	//pick one item
	val = input[pos];
	val += core_fn(pos + 2);
	if(val > max)
	{
		max = val;
	}

	//pick 2 items
	val = input[pos] + input[pos + 1];
	val += core_fn(pos + 4);
	if(val > max)
	{
		max = val;
	}

	//pick 3 items
	val = input[pos] + input[pos + 1] + input[pos + 2];
	val += core_fn(pos + 6);
	if(val > max)
	{
		max = val;
	}

	/* store dp result */
	dp[pos] = max;

	return max;
}

static void test_wrapper()
{
#if 1//def WINDOWS_TEST
	int test_cases, T;
	char str[10];
	signed long long correct_ans;
#endif
	signed long long i;
	
#if 1//def WINDOWS_TEST
	/* Read number of test cases */
	scanf("%d", &T);
	for(test_cases = 1; test_cases <= T; test_cases++)
#endif
	{
		/* Read Inputs */
		scanf("%d", &N);
		for(i = 0; i < N; i++)
		{
			scanf("%d", &input[i]);
			dp[i] = -1;
		}
		for(; i < (N + 6); i++)
		{
			input[i] = 0;
			dp[i] = -1;
		}

		/* algo function call */
		max_scr = core_fn(0);

		
#ifdef WINDOWS_TEST
		/* Print output */
		printf("#%d %I64d\n", test_cases, max_scr);

		/* Test the answer with reference output kept in input file */
		scanf("%s", str);
		scanf("%I64d", &correct_ans);
		if(max_scr == correct_ans)
		{
			printf(" Success: Output is matching with Reference output\n");
		}
		else
		{
			printf(" !!FAILURE: Output is NOT matching with Reference output\n");
		}
#else
		printf("%lld\n", max_scr);
#endif
	}
}

int main()
{
#ifdef WINDOWS_TEST
	printf("\n\n ++++++++ spoj dcepc501 ++++++++\n\n");

	freopen("../test/spoj/spoj_dcepc501.txt", "r", stdin);
#endif

	/* test wrapper function */
	test_wrapper();

	return 0;
}