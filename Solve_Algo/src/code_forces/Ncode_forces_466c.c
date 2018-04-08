
/*
Problem Source:
http://codeforces.com/problemset/problem/466/C


Editorial/Logic/Ideas Sources: 
1) 
*/


/*
Problem Description:

You've got array a[1], a[2], ..., a[n], consisting of n integers. Count the number of ways to split all the elements of the array into three contiguous parts so that the sum of elements in each part is the same.

More formally, you need to find the number of such pairs of indices i, j (2 ≤ i ≤ j ≤ n - 1), that .

Input
The first line contains integer n (1 ≤ n ≤ 5·105), showing how many numbers are in the array. The second line contains n integers a[1], a[2], ..., a[n] (|a[i]| ≤  109) — the elements of array a.

Output
Print a single integer — the number of ways to split the array into three parts with the same sum.

Examples
input
5
1 2 3 0 3
output
2
input
4
0 1 -1 0
output
1
input
2
4 1
output
0

*/

#include <stdio.h>
#include <string.h>

#define RESET				999999
#define INT_MAX				99999999
#define INT_MIN				-99999999
#define DP_INIT				-9999
#define SUCCESS				0
#define MAX_DIM				5000001

static signed long long input[MAX_DIM];
static signed long long N;
static signed long long max_scr, zero_cnt, val, sum;


/* Actual algo funciton */
static void core_fn()
{
	signed long long i, j, tmp, sum_by3, rem;
	signed long long tmp_sum, sum1, sum2, sum3, off1, off2, flag;

	max_scr = 0;
	if(N < 3)
	{
		return;
	}
	if(zero_cnt == N)
	{
		tmp = N - 2;
		max_scr = ((tmp * (tmp + 1)) >> 1);
		return;
	}

	sum_by3 = (sum / 3);
	rem = sum - (sum_by3 * 3);
	if(rem != 0)
	{
		return;
	}

	j = 0;
	for( i = 1; i <= 3; i++)
	{
		flag = 1;
		tmp_sum = 0;
		tmp = 0;
		for(; j < N; j++)
		{
			val = input[j];
			tmp_sum += val;
			if(i > 1)
			{
				if(val != 0 && flag == 1)
				{
					flag = 0;
				}
				tmp += flag;
			}
			if(tmp_sum == sum_by3)
			{
				j++;
				break;
			}
		}

		if(i == 1)
		{
			if(j == N)
			{
				return;
			}
			sum1 = tmp_sum;
		}
		if(i == 2)
		{
			if(j == N)
			{
				return;
			}
			sum2 = tmp_sum;
			off1 = tmp;
		}
		if(i == 3)
		{
			if(tmp_sum != sum_by3)
			{
				return;
			}
			sum3 = tmp_sum;
			if(sum3 == 0)
			{
				off2 = 0;
			}
			else
			{
				off2 = tmp;
			}
		}
	}
	max_scr = (off1 + 1) * (off2 + 1);
}

void test_wrap()
{
	int test_cases, T;
	char str[10];
	signed long long ans, correct_ans;
	signed long long i;
	
#ifdef WINDOWS_TEST
	/* Read number of test cases */
	scanf("%d", &T);
	for(test_cases = 1; test_cases <= T; test_cases++)
#endif
	{
		/* Read Inputs */
		scanf("%I64d", &N);
		zero_cnt = 0;
		sum = 0;
		for(i = 0; i < N; i++)
		{
			scanf("%I64d", &val);
			input[i] = val;
			sum += val;
			if(val == 0)
			{
				zero_cnt ++;
			}
		}

		/* algo function call */
		core_fn();

		
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
		printf("%I64d\n", max_scr);
#endif
	}
}

void main()
{
#ifdef WINDOWS_TEST
	printf("\n\n ++++++++ Code forces - 466c ++++++++\n\n");

	freopen("../test/code_forces/code_forces_466c.txt", "r", stdin);
#endif

	/* test wrapper function */
	test_wrap();
}