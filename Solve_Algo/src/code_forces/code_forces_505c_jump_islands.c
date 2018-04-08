
/*
Problem Source:

http://codeforces.com/contest/505/problem/C

Editorial/Logic/Ideas Sources: 
1) http://codeforces.com/blog/entry/15889
*/


/*
Problem Description:

C. Mr. Kitayuta, the Treasure Hunter
time limit per test1 second
memory limit per test256 megabytes
inputstandard input
outputstandard output
The Shuseki Islands are an archipelago of 30001 small islands in the Yutampo Sea. The islands are evenly spaced along a line, numbered from 0 to 30000 from the west to the east. These islands are known to contain many treasures. There are n gems in the Shuseki Islands in total, and the i-th gem is located on island pi.

Mr. Kitayuta has just arrived at island 0. With his great jumping ability, he will repeatedly perform jumps between islands to the east according to the following process:

First, he will jump from island 0 to island d.
After that, he will continue jumping according to the following rule. Let l be the length of the previous jump, that is, if his previous jump was from island prev to island cur, let l = cur - prev. He will perform a jump of length l - 1, l or l + 1 to the east. That is, he will jump to island (cur + l - 1), (cur + l) or (cur + l + 1) (if they exist). The length of a jump must be positive, that is, he cannot perform a jump of length 0 when l = 1. If there is no valid destination, he will stop jumping.
Mr. Kitayuta will collect the gems on the islands visited during the process. Find the maximum number of gems that he can collect.

Input
The first line of the input contains two space-separated integers n and d (1 ≤ n, d ≤ 30000), denoting the number of the gems in the Shuseki Islands and the length of the Mr. Kitayuta's first jump, respectively.

The next n lines describe the location of the gems. The i-th of them (1 ≤ i ≤ n) contains a integer pi (d ≤ p1 ≤ p2 ≤ ... ≤ pn ≤ 30000), denoting the number of the island that contains the i-th gem.

Output
Print the maximum number of gems that Mr. Kitayuta can collect.

Examples
input
4 10
10
21
27
27
output
3
input
8 8
9
19
28
36
45
55
66
78
output
6
input
13 7
8
8
9
16
17
17
18
21
23
24
24
26
30
output
4
Note
In the first sample, the optimal route is 0  →  10 (+1 gem)  →  19  →  27 (+2 gems)  → ...

In the second sample, the optimal route is 0  →  8  →  15  →  21 →  28 (+1 gem)  →  36 (+1 gem)  →  45 (+1 gem)  →  55 (+1 gem)  →  66 (+1 gem)  →  78 (+1 gem)  → ...

In the third sample, the optimal route is 0  →  7  →  13  →  18 (+1 gem)  →  24 (+2 gems)  →  30 (+1 gem)  → ...

*/

#include <stdio.h>
#include <string.h>

#define RESET				999999
#define INT_MAX				99999999
#define INT_MIN				-99999999
#define DP_EMPTY			-1
#define DP_INIT				-9999
#define SUCCESS				0
#define MAX_DIM				30010
#define MAX_LEN				30001
#define DP_LEN				4010

static signed short gems[MAX_DIM], rem_gems[MAX_DIM];
static signed int N, D;
static signed int max_scr, iter_cnt;
static signed short dp[MAX_DIM][DP_LEN]; //the max possible jump is ~250


/* Actual algo funciton */
static int core_fn_rec_dp(int pos, int len)
{
	int next_len1, next_len2, next_len3, next_pos;
	int gem_cnt, max_gem_cnt;

	iter_cnt ++;

	//base case
	if(len == 1)
	{
		//rem gems from current position
		return rem_gems[pos];
	}
	//base case: no more gems left
	if(rem_gems[pos] == 0)
	{
		return 0;
	}

	//return dp result
	if(len < DP_LEN)	//use dp only for these positions
	if(dp[pos][len] != -1)
	{
		return dp[pos][len];
	}

	gem_cnt = gems[pos];
	max_gem_cnt = gem_cnt;
	//all 3 possible jumps
	next_len1 = len - 1;
	if(next_len1 > 0)
	{
		next_pos = pos + next_len1;
		if(next_pos <= MAX_LEN)
		{
			gem_cnt += core_fn_rec_dp(next_pos, next_len1);
			if(gem_cnt > max_gem_cnt)
			{
				max_gem_cnt = gem_cnt;
			}
		}
	}
	gem_cnt = gems[pos];
	next_len2 = len;
	if(next_len2 > 0 && next_len1 != 1)
	{
		next_pos = pos + next_len2;
		if(next_pos <= MAX_LEN)
		{
			gem_cnt += core_fn_rec_dp(next_pos, next_len2);
			if(gem_cnt > max_gem_cnt)
			{
				max_gem_cnt = gem_cnt;
			}
		}
	}
	gem_cnt = gems[pos];
	next_len3 = len + 1;
	if(next_len3 > 0 && next_len1 != 1 && next_len2 != 1)
	{
		next_pos = pos + next_len3;
		if(next_pos <= MAX_LEN)
		{
			gem_cnt += core_fn_rec_dp(next_pos, next_len3);
			if(gem_cnt > max_gem_cnt)
			{
				max_gem_cnt = gem_cnt;
			}
		}
	}

	//store result in dp
	if(len < DP_LEN)	//use dp only for these positions
	dp[pos][len] = max_gem_cnt;

	return max_gem_cnt;
}

static void test_wrapper()
{
	int test_cases, T;
	char str[10];
	signed int ans, correct_ans;
	signed int i, j, loc, rem;
	
#ifdef WINDOWS_TEST
	/* Read number of test cases */
	scanf("%d", &T);
	for(test_cases = 1; test_cases <= T; test_cases++)
#endif
	{
		/* Read Inputs */
		scanf("%d %d", &N, &D);
		//clear gems array
		for(i = 0; i <= 30001; i++)
		{
			gems[i] = 0;
		}
		//read gems location
		for(i = 0; i < N; i++)
		{
			scanf("%d", &loc);
			gems[loc]++;
		}
		//fill remain gems from cur position
		rem = N;
		for(i = 0; i <= 30001; i++)
		{
			rem_gems[i] = rem;
			rem = rem - gems[i];
			//reset dp buffer
			for(j = 0; j < DP_LEN; j++)
			{
				dp[i][j] = -1;
			}
		}

		iter_cnt = 0;
		/* algo function call */
		max_scr = gems[0];
		max_scr += core_fn_rec_dp(D, D);

		
#ifdef WINDOWS_TEST
		/* Print output */
		printf("#%d %d, iter_cnt: %d\n", test_cases, max_scr, iter_cnt);

		/* Test the answer with reference output kept in input file */
		scanf("%s", str);
		scanf("%d", &correct_ans);
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
	printf("\n\n ++++++++ Code forces - 505c ++++++++\n\n");

	freopen("../test/code_forces/code_forces_505c.txt", "r", stdin);
#endif

	/* test wrapper function */
	test_wrapper();
}