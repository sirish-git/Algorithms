
/*
Problem Source:
http://www.spoj.com/problems/TWENDS/

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
#define MAX_DIM				1001

static signed long long input[MAX_DIM], dp_res[MAX_DIM][MAX_DIM], dp_greedy[MAX_DIM][MAX_DIM];
static signed long long N;
static signed long long max_scr;


/* Actual algo funciton */
static signed long long core_fn(long long start, long long end, long long *greedy_max)
{
	signed long long max_dp, max_grd, i, j, dp_val, grd_val, val1, val2, tmp;

	/* Base case: bounds */
	if(start < 1 | end > N)
	{
		return INT_MIN;
	}
	/* Return dp result */
	if(dp_res[start][end] != -1)
	{
		*greedy_max = dp_greedy[start][end];
		return dp_res[start][end];
	}

	/* Base case: only two elements left */
	if((end - start) == 1)
	{
		val1 = input[start];
		val2 = input[end];
		if(val1 > val2)
		{
			*greedy_max = val2;
			dp_greedy[start][end] = val2;
			dp_res[start][end] = val1;
			return val1;
		}
		else
		{
			*greedy_max = val1;
			dp_greedy[start][end] = val1;
			dp_res[start][end] = val2;
			return val2;
		}
	}

	/* core algo */
	max_dp = INT_MIN;
	//choose first element
	{
		dp_val = input[start];
		val1 = input[start + 1];
		val2 = input[end];
		if(val1 >= val2)
		{
			dp_val += core_fn(start+2, end, &grd_val);
			if(dp_val > max_dp)
			{
				max_dp = dp_val;
				max_grd = grd_val + val1;
			}
		}
		else
		{
			dp_val += core_fn(start+1, end-1, &grd_val);
			if(dp_val > max_dp)
			{
				max_dp = dp_val;
				max_grd = grd_val + val2;
			}
		}
	}
	//choose last element
	{
		dp_val = input[end];
		val1 = input[start];
		val2 = input[end - 1];
		if(val1 >= val2)
		{
			dp_val += core_fn(start+1, end-1, &grd_val);
			if(dp_val > max_dp)
			{
				max_dp = dp_val;
				max_grd = grd_val + val1;
			}
		}
		else
		{
			dp_val += core_fn(start, end-2, &grd_val);
			if(dp_val > max_dp)
			{
				max_dp = dp_val;
				max_grd = grd_val + val2;
			}
		}
	}

	/* Store dp result */
	dp_greedy[start][end] = max_grd;
	dp_res[start][end] = max_dp;

	*greedy_max = max_grd;
	return max_dp;
}

static void test_wrapper()
{
	int test_cases, T;
	char str[10];
	signed long long correct_ans;
	signed long long i, j, max_greedy;
	
	test_cases = 1;

	/* Read number of test cases */
#ifdef WINDOWS_TEST
	/* Read number of test cases */
	scanf("%d", &T);
	for(test_cases = 1; test_cases <= T; test_cases++)
#else
	scanf("%d", &N);
	while(N != 0)
#endif
	{
#ifdef WINDOWS_TEST
		scanf("%d", &N);
#endif
		/* Read Inputs */
		for(i = 1; i <= N; i++)
		{
			scanf("%d", &input[i]);
		}
		/* Reset dp buffers */
		for(i = 1; i <= N; i++)
		{
			for(j = 1; j <= N; j++)
			{
				dp_res[i][j] = -1;
				dp_greedy[i][j] = -1;
			}
		}

		/* algo function call */
		max_greedy = 0;
		max_scr = core_fn(1, N, &max_greedy);
		max_scr = max_scr - max_greedy;
		
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
		printf("In game %d, the greedy strategy might lose by as many as %d points.\n", test_cases, max_scr);
		
		test_cases++;
		scanf("%d", &N);
#endif
	}
}

int main()
{
#ifdef WINDOWS_TEST
	printf("\n\n ++++++++ Spoj - Twends ++++++++\n\n");

	freopen("../test/spoj/spoj_twends.txt", "r", stdin);
#endif

	/* test wrapper function */
	test_wrapper();

	return 0;
}