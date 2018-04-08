
#include <stdio.h>
#include <string.h>

#define INT_MAX				 99999999
#define INT_MIN				-99999999
#define SUCCESS				0
#define MAX_DIM				101

static signed char input[MAX_DIM][MAX_DIM];
static signed long long N, M, K;
static signed long long g_max_scr, g_min_swaps;


/* Actual algo funciton */
static void core_fn()
{
	signed long long i, j, cnt;
	signed long long first_id, max_id;
	signed long long sum, max_sum, trail_1s, max_trail_1s;

	g_max_scr = 0;
	g_min_swaps = 0;
	for(j = 0; j < M; j++)
	{
		//find first 1
		for(i = 0; i < N; i++)
		{
			if(input[i][j] == 1)
			{
				break;
			}
		}

		//find max scr
		first_id = i;
		trail_1s = 0;
		max_sum = 0;
		max_trail_1s = 0;
		for(; i < N; i++)
		{
			//sum
			sum = 0;
			for(cnt = i; cnt < (i + K) && cnt < N; cnt++)
			{
				if(input[cnt][j] == 1)
				{
					sum += 1;
				}
			}
			//max
			if(sum > max_sum)
			{
				max_sum = sum;
				max_trail_1s = trail_1s;
				max_id = i;
			}
			//update trail
			if(i == first_id)
			{
				trail_1s = 1;
			}
			else
			{
				if(input[i][j] == 1)
				{
					trail_1s += 1;
				}
			}
		}

		//final result
		g_max_scr += max_sum;
		g_min_swaps += max_trail_1s;
	}
}

void main()
{
	signed long long i, j;
	
#ifdef WINDOWS_TEST
	while(1) 
	{
#endif
	/* Read Inputs */
	scanf("%I64d %I64d %I64d", &N, &M, &K);
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < M; j++)
		{
			scanf("%d ", &input[i][j]);
		}
	}

	/* algo function call */
	core_fn();

	printf("%I64d %I64d\n", g_max_scr, g_min_swaps);
#ifdef WINDOWS_TEST
	}
#endif
}