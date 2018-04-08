
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
#define MAX_DIM				100002

static signed long long left[MAX_DIM], right[MAX_DIM];
static signed long long N;
static signed long long left_sum, right_sum, cur_scr, max_id;

signed long long abs(signed long long val)
{
	if(val < 0)
		return -val;
	else
		return val;
}

/* Actual algo funciton */
static signed long long core_fn()
{
	signed long long scr, lsum, rsum, i, j, val1, val2;

	signed long long max;

	max = cur_scr;
	max_id = 0;
	for(i = 1; i <= N; i++)
	{
		val1 = left[i];
		val2 = right[i];

		lsum = left_sum - val1 + val2;
		rsum = right_sum - val2 + val1;
		scr = abs(lsum - rsum);
		if(scr > max)
		{
			max = scr;
			max_id = i;
		}
	}

	return max_id;
}

static void test_wrapper()
{
#ifdef WINDOWS_TEST
	int test_cases, T;
	char str[10];
	signed long long correct_ans;
#endif
	signed long long i, val1, val2;
	
#ifdef WINDOWS_TEST
	/* Read number of test cases */
	scanf("%d", &T);
	for(test_cases = 1; test_cases <= T; test_cases++)
#endif
	{
		/* Read Inputs */
		scanf("%I64d", &N);

		left_sum = 0;
		right_sum = 0;
		for(i = 1; i <= N; i++)
		{
			scanf("%I64d %I64d", &val1, &val2);
			left[i] = val1;
			right[i] = val2;
			left_sum += val1;
			right_sum += val2;
		}
		cur_scr = abs(left_sum - right_sum);

		/* algo function call */
		core_fn();

		
#ifdef WINDOWS_TEST
		/* Print output */
		printf("#%d %I64d\n", test_cases, max_id);

		/* Test the answer with reference output kept in input file */
		scanf("%s", str);
		scanf("%I64d", &correct_ans);
		if(max_id == correct_ans)
		{
			printf(" Success: Output is matching with Reference output\n");
		}
		else
		{
			printf(" !!FAILURE: Output is NOT matching with Reference output\n");
		}
#else
		printf("%I64d\n", max_id);
#endif
	}
}

int main()
{
#ifdef WINDOWS_TEST
	printf("\n\n ++++++++ Code forces - 733b ++++++++\n\n");

	freopen("../test/code_forces/code_forces_733b.txt", "r", stdin);
#endif

	/* test wrapper function */
	test_wrapper();

	return 0;
}