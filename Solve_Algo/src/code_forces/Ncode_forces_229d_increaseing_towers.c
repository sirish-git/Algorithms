
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

#define RESET				999999
#define INT_MAX				99999999
#define INT_MIN				-99999999
#define DP_EMPTY			-1
#define DP_INIT				-9999
#define SUCCESS				0
#define MAX_DIM				5001

static signed long long input[MAX_DIM];
static signed long long N;
static signed long long min_scr;


/* Actual algo funciton */
#if 0
static int core_fn(int pos)
{
	signed long long i, j, id, flag1, flag2;
	signed long long op_cnt, min_op;
	signed long long cur, prv, nxt, org;

	//base case
	if(pos >= N)
	{
		if(input[N-1] < input[N-2] || input[N-2] < input[N-3])
		{
			if(input[N-1] < input[N-2])
			{
				return 1;
			}
			else
			{
				return INT_MAX;
			}
		}
		else
		{
			return 0;
		}
	}

	flag1 = 0;
	min_op = INT_MAX;
	op_cnt = 0;
	for(i = pos; i < N; i++)
	{
		prv = input[i-1];
		cur = input[i];
		if(cur < prv)
		{
			flag1 = 1;
			//2 possibilities
			//keeping on left
			{
				//prv = input[i-1];
				input[i-1] = prv + cur;
				input[i] = prv + cur;
				op_cnt = 1;
				op_cnt += core_fn(i+1);
				if(op_cnt < min_op)
				{
					min_op = op_cnt;
				}
				//restore original value
				input[i-1] = prv;
				input[i] = cur;
			}
			//keeping on right
			flag2 = 0;
			j = i;
			nxt = 0;
			while(j < N)
			{
				nxt += input[j];
				id = j;
				if(nxt >= prv)
				{
					flag2 = 1;
					break;
				}
				j++;
			}
			if(flag2)
			{
				org = input[id];
				input[id] = nxt;
				op_cnt = id - i;
				op_cnt += core_fn(id);
				if(op_cnt < min_op)
				{
					min_op = op_cnt;
				}
				//restore original value
				input[id] = org;
			}

			break;
		}
	}
	//all non-decreasing
	if(flag1 == 0)
	{
		min_op = 0;
	}

	return min_op;
}
#else
static int core_fn(int left, int cur, int pos, int op_cnt)
{
	int cur_val, left_val, right_val;

	/* base case */
	if(pos >= N)
	{
		if(cur <= left)
		{
			op_cnt ++;
		}
		if(op_cnt < min_scr)
		{
			min_scr = op_cnt;
		}

		return 0;
	}

	if(pos == N-1)
	{
		if((cur + input[pos]) <= left)
		{
			cur_val = cur + input[pos];
			//put on left if less
			if(cur != 0 && cur_val <=  left)
			{
				op_cnt ++;
			}
			core_fn(left + cur_val, INT_MAX, pos + 1, op_cnt + 1);
		}
		else
		{
			core_fn(input[pos], 0, pos + 1, op_cnt);
		}

		return 0;
	}

	if((cur + input[pos]) <= left)
	{
		//2 possibilities: putting on left or right
		//place it on left
		core_fn(left + cur + input[pos], 0, pos + 1, op_cnt + 1);

		//place it on right
		if(pos < (N-1))
		{
			right_val = cur + input[pos] + input[pos + 1];
			if(right_val > left)
			{
				left_val = right_val;
				cur_val = 0;
			}
			else
			{
				left_val = left;
				cur_val = right_val;
			}
			core_fn(left_val, cur_val, pos + 2, op_cnt + 1);
		}
	}
	else
	{
		//already in ascending order: so no operation needed
		core_fn(input[pos], 0, pos + 1, op_cnt);
	}

	return 0;
}
#endif

static void test_wrapper()
{
	int test_cases, T;
	char str[10];
	signed long long ans, correct_ans;
	signed long long i, val;
	
#ifdef WINDOWS_TEST
	/* Read number of test cases */
	scanf("%d", &T);
	for(test_cases = 1; test_cases <= T; test_cases++)
#endif
	{
		/* Read Inputs */
		scanf("%I64d", &N);
		for(i = 0; i < N; i++)
		{
			scanf("%I64d", &val);
			input[i] = val;
		}

		/* algo function call */
		min_scr = INT_MAX;
		core_fn(0, 0, 0, 0);

		
#ifdef WINDOWS_TEST
		/* Print output */
		printf("#%d %I64d\n", test_cases, min_scr);

		/* Test the answer with reference output kept in input file */
		scanf("%s", str);
		scanf("%I64d", &correct_ans);
		ans = min_scr;
		if(correct_ans == ans)
		{
			printf(" Success: Output is matching with Reference output\n");
		}
		else
		{
			printf(" !!FAILURE: Output is NOT matching with Reference output\n");
		}
#else
		printf("%I64d\n", min_scr);
#endif
	}
}

void main()
{
#ifdef WINDOWS_TEST
	printf("\n\n ++++++++ Code forces - 229d ++++++++\n\n");

	freopen("../test/code_forces/code_forces_229d.txt", "r", stdin);
#endif

	/* test wrapper function */
	test_wrapper();
}