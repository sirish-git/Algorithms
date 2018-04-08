
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

#define INT_MAX				 1000000000
#define INT_MIN				-1000000000
#define SUCCESS				0
#define MAX_DIM				100002

int input_dig[MAX_DIM];
char input_bin[MAX_DIM];
int N;

static void test_wrapper()
{
	int test_cases, T;
	int i, j, id, index;
	int l, r;
	int l_max, r_min;
	int a0, a1, a2, a3;
	int b0, b1, b2, b3;
	int a, b;
	int min, max;
	int sum_run;
	
#ifdef WINDOWS_TEST
	/* Read number of test cases */
	scanf("%d", &T);
	for(test_cases = 1; test_cases <= T; test_cases++)
#endif
	{
		/* Read Inputs */
		scanf("%d", &N);
		for (i = 0; i < N; i++)
		{
			scanf("%d", &input_dig[i]);
		}
		scanf("%s", &input_bin[0]);

		l_max = INT_MIN;
		r_min = INT_MAX;
		//parse the input bins and corresponding digits. note l <= r
		b0 = input_bin[0] - '0';
		b1 = input_bin[1] - '0';
		b2 = input_bin[2] - '0';
		b3 = input_bin[3] - '0';
		a0 = input_dig[0];
		a1 = input_dig[1];
		a2 = input_dig[2];
		a3 = input_dig[3];
		sum_run = b0 + b1 + b2 + b3;
		for(i = 4; i < N; i++)
		{
			b = input_bin[i] - '0';
			a = input_dig[i];
			if(sum_run == 4 || sum_run == 0)
			{
				if(b0 == 1 && b1 == 1 && b2 == 1 && b3 == 1)
				{
					if(b == 0)
					{
						min = INT_MAX;
						//find min
						if(a0 < min)
							min = a0;
						if(a1 < min)
							min = a1;
						if(a2 < min)
							min = a2;
						if(a3 < min)
							min = a3;
						if(a < min)
							min = a;
						r = min - 1;
						if(r < r_min)// && r >= l_max)
							r_min = r;
					}
				}
				else
				if(b0 == 0 && b1 == 0 && b2 == 0 && b3 == 0)
				{
					if(b == 1)
					{
						max = INT_MIN;
						//find max
						if(a0 > max)
							max = a0;
						if(a1 > max)
							max = a1;
						if(a2 > max)
							max = a2;
						if(a3 > max)
							max = a3;
						if(a > max)
							max = a;
						l = max + 1;
						if(l > l_max)// && l <= r_min)
							l_max = l;
					}
				}
			}

			//update sum
			sum_run -= b0;
			//swap values
			b0 = b1;
			b1 = b2;
			b2 = b3;
			b3 = b;
			a0 = a1;
			a1 = a2;
			a2 = a3;
			a3 = a;			
			//update sum
			sum_run += b3;
		}
#if 0
		if(l_max == INT_MIN)
		{
			l_max = r_min;
		}
		else
		if(r_min == INT_MAX)
		{
			r_min = l_max;
		}
#endif

		//output
		printf("%d %d\n", l_max, r_min);
	}
}

int main()
{
	/* test wrapper function */
	test_wrapper();

	return 0;
}