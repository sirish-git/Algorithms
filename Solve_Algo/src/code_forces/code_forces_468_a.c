
#include <stdio.h>
#include <string.h>

#define INT_MAX				 99999999
#define INT_MIN				-99999999
#define SUCCESS				0
#define MAX_DIM				20001

signed long long input[MAX_DIM];
signed long long N;


void test_wrapper()
{
	int test_cases, T;
	char str[50];
	signed long long correct_ans;
	signed long long i, j;
	int a, b, length, mid, len1, len2, scr;
	
#ifdef WINDOWS_TEST
	/* Read number of test cases */
	scanf("%d", &T);
	for(test_cases = 1; test_cases <= T; test_cases++)
#endif
	{
		/* Read Inputs */
		scanf("%d", &a);
		scanf("%d", &b);
	
		length = (a > b) ? (a - b) : (b-a);
		if(length == 1)
		{
			printf("1\n");
		}
		else
		{
			mid = (a + b) / 2;
			len1 = (a > mid) ? (a-mid) : (mid-a);
			len2 = (b > mid) ? (b-mid) : (mid-b);
			scr = (len1 * (len1 + 1)) / 2;
			scr += (len2 * (len2 + 1)) / 2;
			printf("%d\n", scr);
		}
	}
}

int main()
{
	/* test wrapper function */
	test_wrapper();

	return 0;
}