
/*
Problem Source:
http://www.spoj.com/problems/JUMPDORA/

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
#define MAX_DIM				101

static signed long long input[MAX_DIM][MAX_DIM], dp[MAX_DIM][MAX_DIM];
static signed long long M, N;
static signed long long min_scr;


long long find_min(int a, int b)
{
	if(a < b)
		return a;
	else
		return b;
}

/* Actual algo funciton */
static signed long long core_fn_rec_dp(int row, int col)
{
	signed long long i, j, val;
	signed long long min;

	/* Base case: bounds */
	if(row >= M || col >= N)
	{
		return INT_MAX;
	}
	/* current cell has block */
	val = input[row][col];
	if(val == -1)
	{
		return INT_MAX;
	}
	/* Reached destination */
	if(row == (M-1) && col == (N-1))
	{
		return 0;
	}

	/* return dp result: min jums required to reach dest from this position */
	if(dp[row][col] != -1)
	{
		return dp[row][col];
	}

	/* core algo */
	min = INT_MAX;
	//4 jumps possible
	//right
	min = find_min(min, 1 + core_fn_rec_dp(row, col+1));
	//down
	min = find_min(min, 1 + core_fn_rec_dp(row+1, col));
	if(val > 0)
	{
		//right
		min = find_min(min, 1 + core_fn_rec_dp(row, col+1+val));
		//down
		min = find_min(min, 1 + core_fn_rec_dp(row+1+val, col));
	}

	/* store dp result */
	dp[row][col] = min;

	return min;
}

static void test_wrapper()
{
#if 1//def WINDOWS_TEST
	int test_cases, T;
	char str[10], inp[MAX_DIM], ch;
	signed long long correct_ans;
#endif
	signed long long i, j;
	
#if 1//def WINDOWS_TEST
	/* Read number of test cases */
	scanf("%d", &T);
	for(test_cases = 1; test_cases <= T; test_cases++)
#endif
	{
		/* Read Inputs */
		scanf("%lld %lld", &M, &N);
		for(i = 0; i < M; i++)
		{
			scanf("%s", &inp[0]);
			for(j = 0; j < N; j++)
			{
				ch = inp[j];
				if(ch == '#')
					input[i][j] = -1;
				else
					input[i][j] = ch - 48;

				//reset dp
				dp[i][j] = -1;
			}
		}

		/* algo function call */
		min_scr = core_fn_rec_dp(0, 0);
		if(min_scr >= INT_MAX)
		{
			min_scr = -1;
		}

		
#ifdef WINDOWS_TEST
		/* Print output */
		printf("#%d %lld\n", test_cases, min_scr);

		/* Test the answer with reference output kept in input file */
		scanf("%s", str);
		scanf("%lld", &correct_ans);
		if(min_scr == correct_ans)
		{
			printf(" Success: Output is matching with Reference output\n");
		}
		else
		{
			printf(" !!FAILURE: Output is NOT matching with Reference output\n");
		}
#else
		printf("%lld\n", min_scr);
#endif
	}
}

int main()
{
#ifdef WINDOWS_TEST
	printf("\n\n ++++++++ spoj - jumpdora ++++++++\n\n");

	freopen("../test/spoj/spoj_jumpdora.txt", "r", stdin);
#endif

	/* test wrapper function */
	test_wrapper();

	return 0;
}