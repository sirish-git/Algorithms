
/*
Problem Source:
http://codeforces.com/problemset/problem/213/C

http://www.spoj.com/problems/TOURIST/ - Similar problem with high complexity

Editorial/Logic/Ideas Sources: 
	1) Code from submission number: 21850203 
	2) https://www.quora.com/How-would-we-solve-the-TOURIST-problem-on-SPOJ-How-do-we-solve-such-DP-in-general

Notes:
	1) In the return trip the tourist can only move left or up in the grid. 
		This is equivalent to moving right or down in the first trip. 
		So basically there is no difference between the two trips.
	2) Since both trips are basically same we only need to think of first trip. 
		We can send 2 tourists at the same time starting from (0,0)(0,0) cell. 
		So our state will consist of (x1,y1,x2,y2)(x1,y1,x2,y2) 
		where (x1,y1)(x1,y1) is position of first tourist and (x2,y2)(x2,y2) is position of second tourist in grid.
	3) If both tourists are on the same cell (x1==x2 and y1==y2) then we can add only 1 to result if that cell is special.
	4) This algorithm has time complexity of O(n4)O(n4) which won't probably run in time. 
		We can reduce the complexity to O(n3)O(n3). 
		If we know the position of first tourist is (x1,y1)(x1,y1) the xx coordinate of 
		second tourist is x2x2 then we must have x1+y1=x2+y2x1+y1=x2+y2 
		since they both cover same distance in same amount of time. 
		So y2=x1+y1−x2y2=x1+y1−x2 and our state depends only on (x1,y1,x2)(x1,y1,x2).

	5) It is further simplified, Note, that after each move our cells will be located on the same diagonal.
	6) We will solve the problem with DP f(d,i1,i2), d — diagonal number, i1 — 1st coordinate 1st path, i2 — 1st coordinate 2nd path. 
	7) It is clear that we can calculate 2nd coordinate when we know number of the diagonal and 1st coordinate.
*/

/*
My Notes:
	1) Basically we are computing all possible paths from a given cell till dest (bottom-right) cell, finding the max.
	2) So it is stored as dp result for a given cell.
*/

/*
Problem Description:



*/

#include <stdio.h>
#include <string.h>


#define MAX_DIM				305
#define INT_MIN				-99999999


static signed long long input[MAX_DIM][MAX_DIM];
static signed long long W, H;
static signed long long max_scr;

static int dp[2*MAX_DIM][MAX_DIM][MAX_DIM];

int find_max(int a, int b)
{
	if(a > b)
		return a;
	else
		return b;
}
/* Actual algo funciton */
static int core_fn_rec_dp(int d, int x1, int x2)
{
    int y1, y2;
    int max;

	y1 = d-x1;
	y2 = d-x2;

	/* Base case: check bounds */
    if(x1<1 || x1 > H || x2<1 || x2 > H)
	{
		return INT_MIN;
	}
    if(y1<1 || y1 > W || y2<1 || y2 > W)
	{
		return INT_MIN;
	}

	/* Return dp result */
    if(dp[d][x1][x2] != INT_MIN)
	{
		return dp[d][x1][x2];
	}

	max = INT_MIN;
	if(input[x1][y1] >= 0 && input[x2][y2] >= 0)
	{
		max = find_max(max, core_fn_rec_dp(d+1, x1,   x2));
		max = find_max(max, core_fn_rec_dp(d+1, x1+1, x2));
		max = find_max(max, core_fn_rec_dp(d+1, x1,   x2+1));
		max = find_max(max, core_fn_rec_dp(d+1, x1+1, x2+1));

		if(x1 == x2)
		{
			max += input[x1][d-x1];
		}
		else
		{
			max += input[x1][d-x1];   
			max += input[x2][d-x2];
		}
	}

	/* Store dp result */
    dp[d][x1][x2] = max;

    return max;
}

static void test_wrapper()
{
	int test_cases, T;
	char str[10], inp[MAX_DIM], ch;
	signed long long ans, correct_ans;
	signed long long i, j, k, val, max;
	
#if 1//def WINDOWS_TEST
	/* Read number of test cases */
	scanf("%d", &T);
	for(test_cases = 1; test_cases <= T; test_cases++)
#endif
	{
		/* Read Inputs */
		scanf("%d %d", &W, &H);
		for(i = 1; i <= H; i++)
		{
			scanf("%s", &inp[1]);
			for(j = 1; j <= W; j++)
			{
				ch = inp[j];
				switch(ch)
				{
				case '.':
					input[i][j] = 0;
					break;
					
				case '*':
					input[i][j] = 1;
					break;

				case '#':
					input[i][j] = INT_MIN;
					break;
				}
			}
		}

		//reset dp buffer
		max = (W > H) ? W : H; //fill till max index
		for(i = 1; i <= (W+H); i++) 
		{
			for(j = 1; j <= max; j++) 
			{
				for(k = 1; k <= max; k++) 
				{
					dp[i][j][k] = INT_MIN;
				}
			}
		}
		dp[W+H][H][H] = input[H][W];

		/* algo function call */
		max_scr = core_fn_rec_dp(2, 1, 1);
		if(max_scr < 0)
		{
			//if dest can't be reached
			max_scr = 0;
		}

		
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
		printf("%d\n", max_scr);
#endif
	}
}

int main()
{
#ifdef WINDOWS_TEST
	printf("\n\n ++++++++ Spoj - Touris ++++++++\n\n");

	freopen("../test/spoj/spoj_tourist.txt", "r", stdin);
#endif

	/* test wrapper function */
	test_wrapper();

	return 0;
}