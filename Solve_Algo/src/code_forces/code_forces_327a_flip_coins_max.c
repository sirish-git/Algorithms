
/*
Problem Source:
http://codeforces.com/problemset/problem/327/A

Solution: 
http://codeforces.com/blog/entry/13713
https://discuss.codechef.com/questions/80238/kadanes-algorithm-codeforces
1) Use Kadance algorithm to find max subarray
*/

/*
A. Flipping Game

Iahub got bored, so he invented a game to be played on paper.

He writes n integers a1, a2, ..., an. Each of those integers can be either 0 or 1. He's allowed to do exactly one move: he chooses two indices i and j (1 ≤ i ≤ j ≤ n) and flips all values ak for which their positions are in range [i, j] (that is i ≤ k ≤ j). Flip the value of x means to apply operation x = 1 - x.

The goal of the game is that after exactly one move to obtain the maximum number of ones. Write a program to solve the little game of Iahub.

Input
The first line of the input contains an integer n (1 ≤ n ≤ 100). In the second line of the input there are n integers: a1, a2, ..., an. It is guaranteed that each of those n values is either 0 or 1.

Output
Print an integer — the maximal number of 1s that can be obtained after exactly one move.

Examples
input
5
1 0 0 1 0
output
4
input
4
1 0 0 1
output
4
*/

#include <stdio.h>

#define RESET				999999
#define INT_MAX				99999999
#define INT_MIN				-99999999
#define SUCCESS				-1
#define MAX_DIM				100

static int N, input[MAX_DIM];
static int num_ones;


/* Actual algo funciton */
static int flip_max()
{
	int i, j;
	int total_ones;
	int max_so_far, max_val;

	//count the max 1's in original array and flip
	total_ones = 0;
	for(i = 0; i < N; i++)
	{
		if(input[i] == 1)
		{
			total_ones++;
			input[i] = -1;
		}
		else
		{
			input[i] = 1;
		}
	}

	/* Kadance algorithm to find max subarry sum */
	max_so_far = -1;
	max_val = 0;
	for(i = 0; i < N; i++)
	{
		max_val = max_val + input[i];
		if(max_val > max_so_far)
		{
			max_so_far = max_val;
		}
		if(max_val < 0)
		{
			max_val = 0;
		}
	}

	if(N == 1)
	{
		num_ones = total_ones ^ 1;
	}
	else
	{
		num_ones = total_ones + max_so_far;
	}

	return num_ones;
}

void test_flip()
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
		/* Read */
		scanf("%d", &N);
		for(i = 0; i < N; i++)
		{
			scanf("%d", &input[i]);
			//clear dp buffer
			dp[i] = 0;
		}

		/* algo function call */
		flip_max();

		
#ifdef WINDOWS_TEST
		/* Print output */
		printf("#%d %d\n", test_cases, num_ones);

		/* Test the answer with reference output kept in input file */
		scanf("%s", str);
		scanf("%d", &correct_ans);
		ans = num_ones;
		if(correct_ans == ans)
		{
			printf(" Success: Output is matching with Reference output\n");
		}
		else
		{
			printf(" !!FAILURE: Output is NOT matching with Reference output\n");
		}
#else
		printf("%d\n", num_ones);
#endif
	}
}

void main()
{
#ifdef WINDOWS_TEST
	printf("\n\n ++++++++ Code forces - 327a ++++++++\n\n");

	freopen("../test/code_forces/code_forces_327a.txt", "r", stdin);
#endif

	/* test wrapper function */
	test_flip();
}