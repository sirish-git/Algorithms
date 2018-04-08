
#include <stdio.h>
#include <string.h>

#define INT_MAX				 99999999
#define INT_MIN				-99999999
#define SUCCESS				0
#define MAX_DIM				20001


void test_wrapper()
{
	int test_cases, T;
	char str[50];
	signed long long correct_ans;
	signed long long i, j;
	int n, a, b;
	int cnt, round, max_round, left, right, mid;
	
#ifdef WINDOWS_TEST
	/* Read number of test cases */
	scanf("%d", &T);
	for(test_cases = 1; test_cases <= T; test_cases++)
#endif
	{
		/* Read Inputs */
		scanf("%d %d %d", &n, &a, &b);
	
		if((a <= (n/2) && b > (n/2)) || (b <= (n/2) && a > (n/2)))
		{
			printf("Final!\n");
		}
		else
		{
			int tmp;
			if(b < a)
			{
				tmp = a;
				a = b;
				b = tmp;
			}

			cnt = n/2;
			max_round = 0;
			while(cnt > 0)
			{
				max_round++;
				cnt = cnt / 2;
			}

			cnt = 0;
			round = 0;
			left = 1;
			right = n;
			mid = (left + right - 1)/2;
			while(cnt <= max_round)
			{
				if((a <= mid && b > mid) || (b <= mid && a > mid))
				{
					//opposite
					break;
				}
				else if(a < mid && b <= mid)
				{
					right = mid;
				}
				else
				{
					left = mid + 1;
				}
				mid = (left + right - 1)/2;
				round++;
				cnt++;
			}
			round = max_round - round;
			printf("%d\n", round);
		}
	}
}

int main()
{
	/* test wrapper function */
	test_wrapper();

	return 0;
}