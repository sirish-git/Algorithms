
/*
Problem Source:
http://codeforces.com/contest/732/problem/B

Editorial/Logic/Ideas Sources: 
1) 
*/


/*
Problem Description: B. Cormen — The Best Friend Of a Man

Recently a dog was bought for Polycarp. The dog's name is Cormen. Now Polycarp has a lot of troubles. For example, Cormen likes going for a walk.

Empirically Polycarp learned that the dog needs at least k walks for any two consecutive days in order to feel good. For example, if k = 5 and yesterday Polycarp went for a walk with Cormen 2 times, today he has to go for a walk at least 3 times.

Polycarp analysed all his affairs over the next n days and made a sequence of n integers a1, a2, ..., an, where ai is the number of times Polycarp will walk with the dog on the i-th day while doing all his affairs (for example, he has to go to a shop, throw out the trash, etc.).

Help Polycarp determine the minimum number of walks he needs to do additionaly in the next n days so that Cormen will feel good during all the n days. You can assume that on the day before the first day and on the day after the n-th day Polycarp will go for a walk with Cormen exactly k times.

Write a program that will find the minumum number of additional walks and the appropriate schedule — the sequence of integers b1, b2, ..., bn (bi ≥ ai), where bi means the total number of walks with the dog on the i-th day.

Input
The first line contains two integers n and k (1 ≤ n, k ≤ 500) — the number of days and the minimum number of walks with Cormen for any two consecutive days.

The second line contains integers a1, a2, ..., an (0 ≤ ai ≤ 500) — the number of walks with Cormen on the i-th day which Polycarp has already planned.

Output
In the first line print the smallest number of additional walks that Polycarp should do during the next n days so that Cormen will feel good during all days.

In the second line print n integers b1, b2, ..., bn, where bi — the total number of walks on the i-th day according to the found solutions (ai ≤ bi for all i from 1 to n). If there are multiple solutions, print any of them.

Examples
input
3 5
2 0 1
output
4
2 3 2
input
3 1
0 0 0
output
1
0 1 0
input
4 6
2 4 3 5
output
0
2 4 3 5


*/

#include <stdio.h>
#include <string.h>

#define RESET				999999
#define INT_MAX				99999999
#define INT_MIN				-99999999
#define DP_INIT				-9999
#define SUCCESS				0
#define MAX_DIM				505

static signed long long input[MAX_DIM];
static signed long long n, k;
static signed long long min_scr;


/* Actual algo funciton */
static void core_fn()
{
	int i, left, cur, right, diff;

	min_scr = 0;
	left = input[0];
	cur = input[1];
	for(i = 2; i <= (n + 1); i++)
	{
		right = input[i];
		if((left + cur) < k)
		{
			diff = k - (left + cur);
			min_scr += diff;
			cur += diff;
			input[i - 1] = cur;
		}

		//swap
		left = cur;
		cur = right;
	}
}

void test_wrap()
{
	int test_cases, T;
	char str[10];
	int ans, correct_ans;
	int i;
	
#ifdef WINDOWS_TEST
	/* Read number of test cases */
	scanf("%d", &T);
	for(test_cases = 1; test_cases <= T; test_cases++)
#endif
	{
		/* Read Inputs */
		scanf("%d %d", &n, &k);
		for(i = 1; i <= n; i++)
		{
			scanf("%d", &input[i]);
		}
		input[0] = input[n+1] = k;

		/* algo function call */
		core_fn();

		
#ifdef WINDOWS_TEST
		/* Print output */
		printf("#%d %d\n", test_cases, min_scr);

		/* Test the answer with reference output kept in input file */
		scanf("%s", str);
		scanf("%d", &correct_ans);
		ans = min_scr;
		if(correct_ans == ans)
		{
			printf(" Success: Output is matching with Reference output\n");
		}
		else
		{
			printf(" !!FAILURE: Output is NOT matching with Reference output\n");
		}

		for( i = 1; i <= n; i++)
		{
			scanf("%d", &correct_ans);
			if(correct_ans == input[i])
			{
				printf(" Success: Output is matching with Reference output\n");
			}
			else
			{
				printf(" !!FAILURE: Output is NOT matching with Reference output\n");
			}
		}
#else
		printf("%d\n", min_scr);
		for( i = 1; i <= n; i++)
		{
			printf("%d ", input[i]);
		}
#endif
	}
}

void main()
{
#ifdef WINDOWS_TEST
	printf("\n\n ++++++++ Code forces - 732b ++++++++\n\n");

	freopen("../test/code_forces/code_forces_732b.txt", "r", stdin);
#endif

	/* test wrapper function */
	test_wrap();
}