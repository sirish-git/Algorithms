
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
#define MAX_DIM				20001

static signed long long input[MAX_DIM];
static signed long long N;
static signed long long max_scr;


/* Actual algo funciton */
//static to get inlined
static signed long long core_fn()
{
	signed long long i, j;
	signed long long max;

	return max;
}

//static to get inlined
static void test_wrapper()
{
#ifdef WINDOWS_TEST
	int test_cases, T;
	char str[50];
	signed long long correct_ans;
#endif
	signed long long i, j;
	
#ifdef WINDOWS_TEST
	/* Read number of test cases */
	scanf("%d", &T);
	for(test_cases = 1; test_cases <= T; test_cases++)
#endif
	{
		/* Read Inputs */
		scanf("%I64d", &N);

		/* algo function call */
		max_scr = core_fn();

		
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
		printf("%I64d\n", max_scr);
#endif
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