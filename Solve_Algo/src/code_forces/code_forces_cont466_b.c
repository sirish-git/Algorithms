
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

#define INT_MAX				 99999999
#define INT_MIN				-99999999
#define SUCCESS				0
#define MAX_DIM				20001

static signed long long N;
static signed long long max_scr;


static void test_wrapper()
{
	int test_cases, T;
	signed long long i, j;
	long long n, k, A, B;
	long long val, prev_val, new_val, min_cost;
	long long costA, costB;
	long long rem, cnt;
	
#ifdef WINDOWS_TEST
	/* Read number of test cases */
	scanf("%d", &T);
	for(test_cases = 1; test_cases <= T; test_cases++)
#endif
	{
		/* Read Inputs */
		scanf("%I64d", &n);
		scanf("%I64d", &k);
		scanf("%I64d", &A);
		scanf("%I64d", &B);

		if(n == 1)
		{
			min_cost = 0;
		}
		else if(k == 1)
		{
			min_cost = (n - 1) * A;
		}
		else
		{
			min_cost = 0;
			val = n;
			while(val > 1)
			{
				new_val = (val / k);
				rem = val - new_val * k;
				if(rem == 0)
				{
					//divisible
					costA = (val - new_val) * A;
					if(costA < B)
					{
						min_cost += costA;
					}
					else
					{
						min_cost += B;
					}
					val = new_val;
				}
				else if(new_val == 0)
				{
					//k > val
					val = val - 1;
					min_cost += val * A;
					val = 1;
				}
				else
				{
					//not divisible: so subtract
					val = val - rem;
					min_cost += rem * A;
				}
			}
		}

		printf("%I64d\n", min_cost);
	}
}

int main()
{
	/* test wrapper function */
	test_wrapper();

	return 0;
}