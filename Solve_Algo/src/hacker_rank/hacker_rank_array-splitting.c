
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
#define MAX_DIM				20001

static signed int input[MAX_DIM];
static signed int N;
static signed int max_part, total_sum;


/* Actual algo funciton */
static signed int core_fn(int pos, int end, int rem_total)
{
	int i, j;
	signed int part, max, val, sum, rem_sum, flag_part;

	/* Base case : no more partitions possible */
	if((end - pos) == 1)
	{
		return 0;
	}

	sum = 0;
	rem_sum = rem_total;
	max = 0;
	flag_part = 0;
	part = 0;
	for(i = pos; i < end; i++)
	{
		val = input[i];
		sum += val;
		rem_sum -= val;
		if(sum == rem_sum)
		{
			flag_part = 1;

			//left partition
			part = 1;
			part += core_fn(pos, i+1, rem_sum);
			if(part > max)
			{
				max = part;
			}

			//right partition
			part = 1;
			part += core_fn(i+1, end, rem_sum);
			if(part > max)
			{
				max = part;
			}

			break;
		}
	}

	//partition not possible
	if(flag_part == 0)
	{
		return 0;
	}

	return max;
}

static void test_wrapper()
{
#if 1//def WINDOWS_TEST
	int test_cases, T;
	char str[10];
	signed int correct_ans;
#endif
	signed int i, val;
	
#if 1//def WINDOWS_TEST
	/* Read number of test cases */
	scanf("%d", &T);
	for(test_cases = 1; test_cases <= T; test_cases++)
#endif
	{
		/* Read Inputs */
		scanf("%d", &N);

		total_sum = 0;
		for(i = 0; i < N; i++)
		{
			scanf("%d", &val);
			input[i] = val;
			total_sum += val;
		}

		max_part = core_fn(0, N, total_sum);
		
#ifdef WINDOWS_TEST
		/* Print output */
		printf("#%d %d\n", test_cases, max_part);

		/* Test the answer with reference output kept in input file */
		scanf("%s", str);
		scanf("%d", &correct_ans);
		if(max_part == correct_ans)
		{
			printf(" Success: Output is matching with Reference output\n");
		}
		else
		{
			printf(" !!FAILURE: Output is NOT matching with Reference output\n");
		}
#else
		printf("%d\n", max_part);
#endif
	}
}

int main()
{
#ifdef WINDOWS_TEST
	printf("\n\n ++++++++ Hacker rank - array-splitting ++++++++\n\n");

	freopen("../test/hacker_rank/hacker_rank_array-splitting.txt", "r", stdin);
#endif

	/* test wrapper function */
	test_wrapper();

	return 0;
}