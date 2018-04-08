
/*
Problem Source:
http://codeforces.com/contest/349/problem/B

Editorial/Logic/Ideas Sources: 
1) 
*/


/*
Problem Description:

B. Color the Fence
time limit per test2 seconds
memory limit per test256 megabytes
inputstandard input
outputstandard output
Igor has fallen in love with Tanya. Now Igor wants to show his feelings and write a number on the fence opposite to Tanya's house. Igor thinks that the larger the number is, the more chance to win Tanya's heart he has.

Unfortunately, Igor could only get v liters of paint. He did the math and concluded that digit d requires ad liters of paint. Besides, Igor heard that Tanya doesn't like zeroes. That's why Igor won't use them in his number.

Help Igor find the maximum number he can write on the fence.

Input
The first line contains a positive integer v (0 ≤ v ≤ 106). The second line contains nine positive integers a1, a2, ..., a9 (1 ≤ ai ≤ 105).

Output
Print the maximum number Igor can write on the fence. If he has too little paint for any digit (so, he cannot write anything), print -1.

Examples
input
5
5 4 3 2 1 2 3 4 5
output
55555
input
2
9 11 1 12 5 8 9 10 6
output
33
input
0
1 1 1 1 1 1 1 1 1
output
-1


*/

#include <stdio.h>
#include <string.h>

#define RESET				999999
#define INT_MAX				99999999
#define INT_MIN				-99999999
#define DP_EMPTY			-1
#define DP_INIT				-9999
#define SUCCESS				0
#define MAX_DIM				2000000

static signed long long input[10];
static signed long long N;
static signed long long max_scr;
static signed char max_scr_out[MAX_DIM];
static signed long long scr_cnt, nz_flag;


/* Actual algo funciton */
static int core_fn()
{
	int i, j;
	int id, id_cnt, max, rem, quot, flag, cnt;

	nz_flag = 0;
	scr_cnt = MAX_DIM-1;
	max_scr = 0;
	rem = N;
	while(1)
	{
		flag = 0;
		max = 0;
		id = 1;
		for(j = 1; j <= 9; j++)
		{
			quot = rem / input[j];
			if(quot != 0 && quot >= max)
			{
				flag = 1;
				max = quot;
				id = j;
			}
		}

		if(flag == 0)
		{
			break;
		}
		//update value
		for(i = 0; i < max; i++)
		{
			nz_flag = 1;
			max_scr_out[scr_cnt] = id;
			scr_cnt--;
		}
		//substract max val
		rem = rem - input[id] * max;
		if(rem <= 0)
		{
			break;
		}
	}

	return max_scr;
}

static void test_wrapper()
{
	int test_cases, T;
	char str[10];
	signed long long ans, correct_ans;
	signed long long i, val;
	
#ifdef WINDOWS_TEST
	/* Read number of test cases */
	scanf("%d", &T);
	for(test_cases = 1; test_cases <= T; test_cases++)
#endif
	{
		/* Read Inputs */
		scanf("%I64d", &N);
		for(i = 1; i <= 9; i++)
		{
			scanf("%I64d", &val);
			input[i] = val;
		}

		/* algo function call */
		core_fn();

		
#ifdef WINDOWS_TEST
		/* Print output */
		if(nz_flag == 0)
		{
			printf("#%d -1\n", test_cases);
		}
		else
		{
			printf("#%d\n", test_cases);
			for(i = MAX_DIM-1; i > scr_cnt; i--)
			{
				printf("%d", max_scr_out[i]);
			}
			printf("\n");
		}

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
		if(nz_flag == 0)
		{
			printf("-1\n");
		}
		else
		{
			for(i = MAX_DIM-1; i > scr_cnt; i--)
			{
				printf("%d", max_scr_out[i]);
			}
			printf("\n");
		}
#endif
	}
}

void main()
{
#ifdef WINDOWS_TEST
	printf("\n\n ++++++++ Code forces - 349b ++++++++\n\n");

	freopen("../test/code_forces/code_forces_349b.txt", "r", stdin);
#endif

	/* test wrapper function */
	test_wrapper();
}