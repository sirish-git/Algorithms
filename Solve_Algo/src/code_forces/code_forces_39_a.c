
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
	int sumB, sumC, val;
	
#ifdef WINDOWS_TEST
	/* Read number of test cases */
	scanf("%d", &T);
	for(test_cases = 1; test_cases <= T; test_cases++)
#endif
	{
		/* Read Inputs */
		scanf("%I64d", &N);
	
		sumB = 0;
		sumC = 0;
		for(i = 0; i < N; i++)
		{
			scanf("%d", &val);
			if(val > 0)
				sumB += val;
			else
				sumC += val;
		}
		printf("%d\n", sumB-sumC);
	}
}

int main()
{
	/* test wrapper function */
	test_wrapper();

	return 0;
}