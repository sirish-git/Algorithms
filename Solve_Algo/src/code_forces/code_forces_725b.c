
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
#define MAX_DIM				128

static signed char input[MAX_DIM];
static signed long long N;
static signed long long max_scr;


/* Actual algo funciton */
static void core_fn()
{
	char ch;
	signed long long quot, rem, val, i, strcnt, pos;

	strcnt = 0;
	i = 0;
	while(input[i] != '\0')
	{
		i++;
		strcnt++;
	}

	N = 0;
	pos = 1;
	for(i = strcnt-2; i >= 0; i--)
	{
		ch = input[i] - 48;
		N += ch * pos;
		pos = pos * 10;
	}
	ch = input[strcnt - 1];

	quot = ((N-1) >> 2);
	rem = N - (quot << 2);

	max_scr = quot * 16;

	if(rem > 2)
	{
		rem -= 2;
	}
	if(rem > 1)
	{
		max_scr += 7;
		rem -= 1;
	}
	if(rem == 1)
	{
		switch(ch)
		{
		case 'f':
			val = 1;
			break;
		case 'e':
			val = 2;
			break;
		case 'd':
			val = 3;
			break;
		case 'a':
			val = 4;
			break;
		case 'b':
			val = 5;
			break;
		case 'c':
			val = 6;
			break;
		}
		max_scr += val;
	}
}

static void test_wrapper()
{
	int test_cases, T;
	char str[10];
	signed long long ans, correct_ans;
	signed long long i;
	
#ifdef WINDOWS_TEST
	/* Read number of test cases */
	scanf("%d", &T);
	for(test_cases = 1; test_cases <= T; test_cases++)
#endif
	{
		/* Read Inputs */
		scanf("%s", &input[0]);

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
	printf("\n\n ++++++++ Code forces - 725b ++++++++\n\n");

	freopen("../test/code_forces/code_forces_725b.txt", "r", stdin);
#endif

	/* test wrapper function */
	test_wrapper();
}