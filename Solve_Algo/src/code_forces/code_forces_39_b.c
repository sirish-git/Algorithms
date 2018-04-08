
#include <stdio.h>
#include <string.h>

#define INT_MAX				 99999999
#define INT_MIN				-99999999
#define SUCCESS				0
#define MAX_DIM				20001

//signed long long input[MAX_DIM];
signed long long N;

//static to get inlined
static void test_wrapper()
{
	int test_cases, T;
	char str[50];
	signed long long correct_ans;
	signed long long i, j;
	long long a, b, c;
	
#ifdef WINDOWS_TEST
	/* Read number of test cases */
	scanf("%d", &T);
	for(test_cases = 1; test_cases <= T; test_cases++)
#endif
	{
		/* Read Inputs */
		scanf("%I64d %I64d", &a, &b);
	
		while(a > 0 && b > 0)
		{
			if(a == 0 || b == 0)
			{
				break;
			}
			else if(a >= (2 * b))
			{
				a %= (2 * b);
			}
			else if(b >= (2 * a))
			{
				b %= (2 * a);
			}
			else
			{
				break;
			}
		}

		printf("%I64d %I64d\n", a, b);
	}
}

int main()
{
	/* test wrapper function */
	test_wrapper();

	return 0;
}