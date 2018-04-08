
/*
Problem Source:
http://codeforces.com/problemset/problem/189/A

Solution: 

1) 
*/

/*
A. Cut Ribbon

Polycarpus has a ribbon, its length is n. He wants to cut the ribbon in a way that fulfils the following two conditions:

After the cutting each ribbon piece should have length a, b or c.
After the cutting the number of ribbon pieces should be maximum.
Help Polycarpus and find the number of ribbon pieces after the required cutting.

Input
The first line contains four space-separated integers n, a, b and c (1 ≤ n, a, b, c ≤ 4000) — the length of the original ribbon and the acceptable lengths of the ribbon pieces after the cutting, correspondingly. The numbers a, b and c can coincide.

Output
Print a single number — the maximum possible number of ribbon pieces. It is guaranteed that at least one correct ribbon cutting exists.

Examples
input
5 5 3 2
output
2
input
7 5 5 2
output
2
Note
In the first example Polycarpus can cut the ribbon in such way: the first piece has length 2, the second piece has length 3.

In the second example Polycarpus can cut the ribbon in such way: the first piece has length 5, the second piece has length 2.
*/

#include <stdio.h>

#define RESET				999999
#define INT_MAX				99999999
#define INT_MIN				-99999999
#define DP_INIT				-9999
#define SUCCESS				0
#define MAX_DIM				4001

static int N, a, b, c;
static int max_ribbon_cnt;
static int dp[MAX_DIM];


/* Actual algo funciton */
static int cut_ribbon_rec_mem(int rem_rib)
{
	int max_rib, rib_cnt;

	/* Base case */
	if(rem_rib == 0)
	{
		return 1;
	}
	if(rem_rib < 0)
	{
		return INT_MIN;
	}

	/* Memoized result for max cuts with remaining ribbons */
	if(dp[rem_rib] != DP_INIT)
	{
		return dp[rem_rib];
	}

	max_rib = INT_MIN;
	/* recursive call with all 3 denominations */
	rib_cnt = cut_ribbon_rec_mem(rem_rib - a);
	if((rem_rib - a) > 0)
	{
		rib_cnt++;
	}
	if(rib_cnt > max_rib)
	{
		max_rib = rib_cnt;
	}
	rib_cnt = cut_ribbon_rec_mem(rem_rib - b);
	if((rem_rib - b) > 0)
	{
		rib_cnt++;
	}
	if(rib_cnt > max_rib)
	{
		max_rib = rib_cnt;
	}
	rib_cnt = cut_ribbon_rec_mem(rem_rib - c);
	if((rem_rib - c) > 0)
	{
		rib_cnt++;
	}
	if(rib_cnt > max_rib)
	{
		max_rib = rib_cnt;
	}

	/* Memoize the result */
	dp[rem_rib] = max_rib;

	if(max_rib > max_ribbon_cnt)
	{
		max_ribbon_cnt = max_rib;
	}

	return max_rib;
}

void test_ribbon()
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
		scanf("%d %d %d %d", &N, &a, &b, &c);
		//fill dp buffer
		for(i = 0; i <= N; i++)
		{
			dp[i] = DP_INIT;
		}

		/* algo function call */
		max_ribbon_cnt = 0;
		cut_ribbon_rec_mem(N);

		
#ifdef WINDOWS_TEST
		/* Print output */
		printf("#%d %d\n", test_cases, max_ribbon_cnt);

		/* Test the answer with reference output kept in input file */
		scanf("%s", str);
		scanf("%d", &correct_ans);
		ans = max_ribbon_cnt;
		if(correct_ans == ans)
		{
			printf(" Success: Output is matching with Reference output\n");
		}
		else
		{
			printf(" !!FAILURE: Output is NOT matching with Reference output\n");
		}
#else
		printf("%d\n", max_ribbon_cnt);
#endif
	}
}

void main()
{
#ifdef WINDOWS_TEST
	printf("\n\n ++++++++ Code forces - 189a ++++++++\n\n");

	freopen("../test/code_forces/code_forces_189a.txt", "r", stdin);
#endif

	/* test wrapper function */
	test_ribbon();
}