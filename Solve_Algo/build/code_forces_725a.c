
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
#define DP_INIT				-9999
#define SUCCESS				0
#define MAX_DIM				200001

static char input[MAX_DIM];
static signed long long N;
static signed long long max_scr;


/* Actual algo funciton */
static void core_fn()
{
	int i;
	int left, right;

	left = 0;
	for(i = 0; i < N; i++)
	{
		if(input[i] == '<')
		{
			left++;
		}
		else
		{
			break;
		}
	}


	right = 0;
	for(i = N-1; i >= 0; i--)
	{
		if(input[i] == '>')
		{
			right++;
		}
		else
		{
			break;
		}
	}

	max_scr = left + right;
}

static void test_wrapper()
{
	int test_cases, T;
	char str[10];
	signed long long ans, correct_ans;
	signed long long i;
	char ch;
	
#ifdef WINDOWS_TEST
	/* Read number of test cases */
	scanf("%d", &T);
	for(test_cases = 1; test_cases <= T; test_cases++)
#endif
	{
		/* Read Inputs */
		scanf("%d", &N);
		{
			scanf("%s", &input[0]);
		}

		/* algo function call */
		core_fn();

		
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

void main()
{
#ifdef WINDOWS_TEST
	printf("\n\n ++++++++ Code forces - 725a ++++++++\n\n");

	freopen("../test/code_forces/code_forces_725a.txt", "r", stdin);
#endif

	/* test wrapper function */
	test_wrapper();
}