
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

#define RESET				999999
#define INT_MAX				99999999
#define INT_MIN				-99999999
#define DP_EMPTY			-1
#define DP_INIT				-9999
#define SUCCESS				0
#define MAX_DIM				200001

static signed int input[MAX_DIM];
static signed int N;
static signed int max_cont_sum;


/* Actual algo funciton */
static signed int core_fn()
{
	int i, j;
	signed int max, val, sum;

	sum = 0;
	max = 0;
	for(i = 0; i < N; i++)
	{
		val = input[i];
		sum += val;
		if(sum < 0)
		{
			sum = 0;
		}
		if(sum > max)
		{
			max = sum;
		}
	}

	max_cont_sum = max;

	return max;
}

static void test_wrapper()
{
#if 1//def WINDOWS_TEST
	int test_cases, T;
	char str[10];
	signed int correct_ans, correct_ans2;
#endif
	signed int i, val, max_non_cont_sum, max;
	
#if 1//def WINDOWS_TEST
	/* Read number of test cases */
	scanf("%d", &T);
	for(test_cases = 1; test_cases <= T; test_cases++)
#endif
	{
		/* Read Inputs */
		scanf("%d", &N);

		max = INT_MIN;
		max_non_cont_sum = 0;
		for(i = 0; i < N; i++)
		{
			scanf("%d", &val);
			input[i] = val;
			if(val >= 0)
			{
				max_non_cont_sum += val;
			}
			if(val > max)
			{
				max = val;
			}
		}
		//if all input values are negative
		if(max < 0)
		{
			max_cont_sum = max;
			max_non_cont_sum = max;
		}
		else
		{
			/* algo function call */
			core_fn();
		}
		
#ifdef WINDOWS_TEST
		/* Print output */
		printf("#%d %d %d\n", test_cases, max_cont_sum, max_non_cont_sum);

		/* Test the answer with reference output kept in input file */
		scanf("%s", str);
		scanf("%d %d", &correct_ans, &correct_ans2);
		if(max_cont_sum == correct_ans && max_non_cont_sum == correct_ans2)
		{
			printf(" Success: Output is matching with Reference output\n");
		}
		else
		{
			printf(" !!FAILURE: Output is NOT matching with Reference output\n");
		}
#else
		printf("%d %d\n", max_cont_sum, max_non_cont_sum);
#endif
	}
}

int main()
{
#ifdef WINDOWS_TEST
	printf("\n\n ++++++++ Hacker rank - maxsubarray ++++++++\n\n");

	freopen("../test/hacker_rank/hacker_rank_maxsubarray.txt", "r", stdin);
#endif

	/* test wrapper function */
	test_wrapper();

	return 0;
}