
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
#define INT_MAX				9999999999
#define INT_MIN				-99999999
#define DP_EMPTY			-1
#define DP_INIT				-9999
#define SUCCESS				0
#define MAX_DIM				100000001

static signed int input[MAX_DIM], inp1[100001];
static signed int N;
static signed long long max_scr, min_val, max_val, total_sum;


/* Actual algo funciton */
static signed int core_fn()
{
	signed long long i, val, rem_sum;
	signed long long max;
	signed long long S, P;

	max_scr = 0;
	S = 1;
	rem_sum = total_sum;
	for(i = 0; i < N; i++)
	{
		val = input[i];
		P = S * rem_sum;
		if(P >= max_scr)
		{
			max_scr = P;
		}
		else
		{
			//break;
		}

		rem_sum -= val;
		S ++;
	}

	return max_scr;
}

static void test_wrapper()
{
#if 1//def WINDOWS_TEST
	int test_cases, T;
	char str[10];
	signed int correct_ans;
#endif
	signed int i, j;
	signed int val, id, temp;
	
#if 1//def WINDOWS_TEST
	/* Read number of test cases */
	scanf("%d", &T);
	for(test_cases = 1; test_cases <= T; test_cases++)
#endif
	{
		/* Read Inputs */
		scanf("%d", &N);
		//read inputs
		total_sum = 0;
		for(i = 0; i < N; i++)
		{
			scanf("%d", &val);
			inp1[i] = val;
			total_sum += val;
		}
		//sort the input
		for(i = 0; i < N; i++)
		{
			min_val = INT_MAX;
			for(j = i; j < N; j++)
			{
				val = inp1[j];
				if(val < min_val)
				{
					min_val = val;
					id = j;
				}
			}
			//swap
			if(id != i)
			{
				temp = inp1[i];
				inp1[id] = temp;
			}
			input[i] = min_val;
		}

		/* algo function call */
		core_fn();

		
#ifdef WINDOWS_TEST
		/* Print output */
		printf("#%d %d\n", test_cases, max_scr);

		/* Test the answer with reference output kept in input file */
		scanf("%s", str);
		scanf("%d", &correct_ans);
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
	printf("\n\n ++++++++ Hacker rank - mandragora ++++++++\n\n");

	freopen("../test/hacker_rank/hacker_rank_mandragora.txt", "r", stdin);
#endif

	/* test wrapper function */
	test_wrapper();

	return 0;
}