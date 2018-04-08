
/*
Problem Source:
http://www.spoj.com/problems/POWERCAR/

Editorial/Logic/Ideas Sources: 
1) 
*/


/*
Problem Description:

POWERCAR - Car with powers
no tags 
Car with Powers race track

The race track is a straight line with starting point at Track[0] and ending point at Track[n-1]. The car is initially at Track[0].

Track[i]='#' if the track has a wall at Track[i].

The car can move from Track[i] to Track[i+1] if and only if Track[i+1] is not a wall. The time taken to move from Track[i] to Track[i+1] is 1 unit.

If there is a wall at Track[i+1], you can shoot it from Track[i] if you have enough bullets in the car. Once a bullet is fired, the bullets count will decrease by 1. The time required to fire a bullet is 0.

It is also allowed to ride the car off the track. It's allowed to move from Track[i] to offTrack[i], from offTrack[i] to offTrack[i+1] and from offTrack[i] to Track[i] (if Track[i] is not a wall). The time taken for any of these steps is 2 units.


Find the fastest possible time to finish the race. Print "Impossible" if it's impossible to finish the race.


Input:

The first line consists of an integer t, the number of test cases. For each test case, the first line consists of two integers the length of race track n and the number of bullets the car can fire followed by a line with a string representing the Track. 


Output:

For each test case, print the expected result as specified in the problem statement. 


Input Constraints:

1 <= t <= 100

2 <= n <= 1000

0 <= bullets <= 1000

Track[i] ∈ {'S','E', '0', '#'}

Track[0]='S', Track[n-1]='E' 


Sample Input:

10
7 3
S00000E
2 2
SE
4 1
S00E
8 1
S0000##E
8 3
S0#00#0E
7 2
S0#0##E
10 4
S00#0#0##E
5 2
S000E
7 1
S0##00E
9 0
S0000##0E
 

Sample Output:

6
1
3
13
7
12
9
4
12
15

*/

#include <stdio.h>
#include <string.h>

#define WALL				-1
#define ON_TRACK			 0
#define OFF_TRACK			 1
#define INT_MAX				 99999999
#define INT_MIN				-99999999
#define SUCCESS				0
#define MAX_DIM				1005

static signed long long input[MAX_DIM];
//dp[i][j][k]: stores score from position 'i' to reach end with remaining bullets 'j', for track k
static signed long long dp[MAX_DIM][MAX_DIM][2];

static signed long long N, Bullets;
static signed long long min_scr;

static signed long long find_min(long long a, long long b)
{
	if(a < b)
		return a;
	else
		return b;
}
/* Actual algo funciton */
static signed long long core_fn_rec_dp(int pos, int rem_bullets, int track)
{
	signed long long scr, min, nxt_pos;

	/* Base case: reaching end */
	if(pos == N)
	{
		if(track == ON_TRACK)
		{
			return 0;
		}
		else
		{
			return 2;
		}
	}

	/* return dp result */
	if(dp[pos][rem_bullets][track] != INT_MAX)
	{
		return dp[pos][rem_bullets][track];
	}

	/* core algo */
	min = INT_MAX;
	nxt_pos = pos+1;

	//proceed in on track
	if(track == ON_TRACK && input[nxt_pos] == 0)
	{
		min = find_min(min, 1 + core_fn_rec_dp(nxt_pos, rem_bullets, ON_TRACK));
	}

	//shoot here if possible
	if(track == ON_TRACK && rem_bullets > 0)
	{
		min = find_min(min, 1 + core_fn_rec_dp(nxt_pos, rem_bullets-1, ON_TRACK));
	}

	//start new off track and move to next position
	if(track == ON_TRACK)
	{
		min = find_min(min, 4 + core_fn_rec_dp(nxt_pos, rem_bullets, OFF_TRACK));
	}

	//reached here in off track, so continue off track
	if(track == OFF_TRACK)
	{
		min = find_min(min, 2 + core_fn_rec_dp(nxt_pos, rem_bullets, OFF_TRACK));
	}

	//reached here in off track, come off track to on track
	if(track == OFF_TRACK && input[pos] == 0)
	{
		min = find_min(min, 2 + core_fn_rec_dp(pos, rem_bullets, ON_TRACK));
	}

	/* store dp result */
	dp[pos][rem_bullets][track] = min;

	return min;
}

static void test_wrapper()
{
#if 1//def WINDOWS_TEST
	int test_cases, T;
	char str[10], inp[1005], ch;
	signed long long correct_ans;
#endif
	signed long long i, j, k;
	
#if 1//def WINDOWS_TEST
	/* Read number of test cases */
	scanf("%d", &T);
	for(test_cases = 1; test_cases <= T; test_cases++)
#endif
	{
		/* Read Inputs */
		scanf("%d %d", &N, &Bullets);
		scanf("%s", &inp[1]);
		//first and last elements are zero
		input[1] = 0;
		input[N] = 0;
		for(i = 2; i < N; i++)
		{
			ch = inp[i];
			switch(ch)
			{
			case '#':
				input[i] = WALL;
				break;

			default:
				input[i] = 0;
			}
		}
		/* reset dp buffer */
		for(i = 0; i <= N; i++)
		{
			for(j = 0; j <= Bullets; j++)
			{
				for(k = 0; k < 2; k++)
				{
					dp[i][j][k] = INT_MAX;
				}
			}
		}

		/* algo function call */
		min_scr = core_fn_rec_dp(1, Bullets, ON_TRACK);

		
#ifdef WINDOWS_TEST
		/* Print output */
		printf("#%d %I64d\n", test_cases, min_scr);

		/* Test the answer with reference output kept in input file */
		scanf("%s", str);
		scanf("%I64d", &correct_ans);
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
	printf("\n\n ++++++++ spoj - powercar ++++++++\n\n");

	freopen("../test/spoj/spoj_powercar.txt", "r", stdin);
#endif

	/* test wrapper function */
	test_wrapper();

	return 0;
}