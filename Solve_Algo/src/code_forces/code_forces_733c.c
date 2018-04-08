
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
#define MAX_DIM				555

static signed long long input[MAX_DIM], out[MAX_DIM], out_cord[MAX_DIM];
static signed long long sub_ids[MAX_DIM], max_ids[MAX_DIM], id_cnt;
static signed long long N, K;
static signed long long max_scr, out_cnt;
static signed char action[MAX_DIM];


/* Actual algo funciton */
static signed long long core_fn()
{
	signed long long i, j, val, sum, out_sum, max, max_id;
	signed long long cnt1, cnt2, length, len_tmp, flag1, flag_equal, max_val, flag_new;

	max_scr = 0;
	//process sub intervals to match with output
	sum = 0;
	id_cnt = 1;
	max = INT_MIN;
	for(i = 1; i <= N; i++)
	{
		val = input[i];
		out_sum = out[id_cnt];
		sum += val;
		if(val > max)
		{
			max = val;
			max_id = i;
		}

		if(sum == out_sum)
		{
			sum = 0;
			max = INT_MIN;
			sub_ids[id_cnt] = i;
			max_ids[id_cnt] = max_id;
			id_cnt++;
		}
		//not possible to get output order
		if(sum > out_sum)
		{
			max_scr = INT_MIN;
			return 0;
		}
	}
	if((id_cnt -1) != K)
	{
		max_scr = INT_MIN;
		return 0;
	}

	//process all the sub arrays
	out_cnt = 0;
	length = 0;
	cnt1 = 1;

	for(i = 1; i < id_cnt; i++)
	{
		cnt2 = sub_ids[i];
		max_id = max_ids[i];
		
		if(cnt2 == cnt1)
		{
		}
		else
		{
			if(max_id == cnt2)
			{
				//max val is last: eat left
				if(input[max_id] <= input[max_id - 1])
				{
					max_scr = INT_MIN;
					break;
				}
				for(j = cnt2; j > cnt1; j--)
				{
					out_cord[out_cnt] = j - length;
					action[out_cnt] = 'L';
					out_cnt++;
				}
			}
			else 
			{
				//find weight higher than neighbor
				flag_new = 0;
				flag_equal = 1;
				max_val = input[max_id];
				for(j = max_id; j < cnt2; j++)
				{
					val = input[j];
					if(val == max_val)
					{
						if(j == cnt1)
						{
							//left not available
							flag1 = val > input[j+1];
						}
						else
						{
							flag1 = val > input[j-1] || val > input[j+1];
						}
						if(flag1)
						{
							flag_equal = 0;
							if(j != max_id)
							{
								flag_new = 1;
							}
							max_id = j;
							break;
						}
					}
				}
				//all are equal
				if(flag_equal == 1)
				{
					max_scr = INT_MIN;
					return 0;
				}

				if(max_id == cnt1)
				{
					//max val is first: eat right
					if(input[max_id] <= input[max_id + 1])
					{
						max_scr = INT_MIN;
						break;
					}
					for(j = cnt1; j < cnt2; j++)
					{
						out_cord[out_cnt] = cnt1 - length;
						action[out_cnt] = 'R';
						out_cnt++;
					}
				}
				else
				{
					//max val in middle

					if(flag_new == 0)
					{
						//first left: eat left
						for(j = max_id; j > cnt1; j--)
						{
							out_cord[out_cnt] = j - length;
							action[out_cnt] = 'L';
							out_cnt++;
						}
						//right
						len_tmp = length + (max_id - cnt1);
						for(j = max_id; j < cnt2; j++)
						{
							out_cord[out_cnt] = max_id - len_tmp;
							action[out_cnt] = 'R';
							out_cnt++;
						}
					}
					else
					{
						//right
						for(j = max_id; j < cnt2; j++)
						{
							out_cord[out_cnt] = max_id - length;
							action[out_cnt] = 'R';
							out_cnt++;
						}

						//left: eat left
						for(j = max_id; j > cnt1; j--)
						{
							out_cord[out_cnt] = j - length;
							action[out_cnt] = 'L';
							out_cnt++;
						}
					}
				}
			}
		}

		length += (cnt2 - cnt1);
		cnt1 = cnt2 + 1;
	}

	return max;
}

static void test_wrapper()
{
#ifdef WINDOWS_TEST
	int test_cases, T;
	char str[10];
	signed long long correct_ans;
#endif
	signed long long i, val;
	
#ifdef WINDOWS_TEST
	/* Read number of test cases */
	scanf("%d", &T);
	for(test_cases = 1; test_cases <= T; test_cases++)
#endif
	{
		/* Read Inputs */
		scanf("%I64d", &N);
		for(i = 1; i <= N; i++)
		{
			scanf("%I64d", &input[i]);
		}
		scanf("%I64d", &K);
		for(i = 1; i <= K; i++)
		{
			scanf("%I64d", &out[i]);
		}
		input[0] = input[N+1] = INT_MAX;

		/* algo function call */
		core_fn();

		
#ifdef WINDOWS_TEST
		/* Print output */
		if(max_scr == INT_MIN)
		{
			printf("#%d NO\n", test_cases);
		}
		else
		{
			printf("#%d YES\n", test_cases);
			for(i = 0; i < out_cnt; i++)
			{
				printf("%I64d %c\n", out_cord[i], action[i]);
			}
		}

		/* Test the answer with reference output kept in input file */
		scanf("%s", str);
		scanf("%s", str);

#if 0
		if(max_scr == correct_ans)
		{
			printf(" Success: Output is matching with Reference output\n");
		}
		else
		{
			printf(" !!FAILURE: Output is NOT matching with Reference output\n");
		}
#endif
#else
		if(max_scr == INT_MIN)
		{
			printf("NO\n");
		}
		else
		{
			printf("YES\n");
			for(i = 0; i < out_cnt; i++)
			{
				printf("%I64d %c\n", out_cord[i], action[i]);
			}
		}
#endif
	}
}

int main()
{
#ifdef WINDOWS_TEST
	printf("\n\n ++++++++ Code forces - 733c ++++++++\n\n");

	freopen("../test/code_forces/code_forces_733c.txt", "r", stdin);
#endif

	/* test wrapper function */
	test_wrapper();

	return 0;
}