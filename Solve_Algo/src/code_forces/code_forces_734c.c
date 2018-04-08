
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
#define MAX_DIM				200001

static signed long long type1_points[MAX_DIM], type1_sec[MAX_DIM];
static signed long long type2_points[MAX_DIM], type2_potion_cnt[MAX_DIM];
static signed long long n_potion_cnt, m_t1_spells_cnt, k_t2_spells_cnt;
static signed long long x_sec, s_total_points;
static signed long long min_time;


signed long long find_type2_max_potions_bin_search(long long rem_points)
{
	signed long long i, potions, points, left, right, mid;
	signed long long max;

	if(rem_points <= 0)
	{
		return 0;
	}

	max = 0;
	if(k_t2_spells_cnt == 1)
	{
		if(rem_points >= type2_points[0])
		{
			max = type2_potion_cnt[0];
		}
	}

	left = 0;
	right = k_t2_spells_cnt-1;
	while(right >= left)
	{
		if(type2_points[left] > rem_points)
		{
			break;
		}

		mid = left + (right - left) / 2;
		if(type2_points[mid] > rem_points)
		{
			right = mid - 1;
		}
		else
		{
			left = mid + 1;
			max = type2_potion_cnt[mid];
		}
	}

	return max;
}

/* Actual algo funciton */
static signed long long core_fn()
{
	signed long long i, j;
	signed long long points, time, potions, new_time;

	/* Select type1 and Search all type2 */
	for(i = 0; i < m_t1_spells_cnt; i++)
	{
		points = type1_points[i];
		time = type1_sec[i];

		if(points <= s_total_points)
		{
			//type1 & type2
			potions = find_type2_max_potions_bin_search(s_total_points - points);
			new_time = (n_potion_cnt - potions) * time;
			if(new_time < min_time)
			{
				min_time = new_time;
			}
		}

		//only type2
		{
			potions = find_type2_max_potions_bin_search(s_total_points);
			new_time = (n_potion_cnt - potions) * x_sec;
			if(new_time < min_time)
			{
				min_time = new_time;
			}
		}
	}

	return 0;
}

static void test_wrapper()
{
#ifdef WINDOWS_TEST
	int test_cases, T;
	char str[50];
	signed long long correct_ans;
#endif
	signed long long i, j;
	
#ifdef WINDOWS_TEST
	/* Read number of test cases */
	scanf("%d", &T);
	for(test_cases = 1; test_cases <= T; test_cases++)
#endif
	{
		/* Read Inputs */
		scanf("%I64d %I64d %I64d", &n_potion_cnt, &m_t1_spells_cnt, &k_t2_spells_cnt);
		scanf("%I64d %I64d", &x_sec, &s_total_points);
		for(i = 0; i < m_t1_spells_cnt; i++)
		{
			scanf("%I64d", &type1_sec[i]);
		}
		for(i = 0; i < m_t1_spells_cnt; i++)
		{
			scanf("%I64d", &type1_points[i]);
		}
		for(i = 0; i < k_t2_spells_cnt; i++)
		{
			scanf("%I64d", &type2_potion_cnt[i]);
		}
		for(i = 0; i < k_t2_spells_cnt; i++)
		{
			scanf("%I64d", &type2_points[i]);
		}

		/* algo function call */
		min_time = n_potion_cnt * x_sec;
		core_fn();

		
#ifdef WINDOWS_TEST
		/* Print output */
		printf("#%d %I64d\n", test_cases, min_time);

		/* Test the answer with reference output kept in input file */
		scanf("%s", str);
		scanf("%I64d", &correct_ans);
		if(min_time == correct_ans)
		{
			printf(" Success: Output is matching with Reference output\n");
		}
		else
		{
			printf(" !!FAILURE: Output is NOT matching with Reference output\n");
		}
#else
		printf("%I64d\n", min_time);
#endif
	}
}

int main()
{
#ifdef WINDOWS_TEST
	printf("\n\n ++++++++ Code forces - 734 ++++++++\n\n");

	freopen("../test/code_forces/code_forces_734c.txt", "r", stdin);
#endif

	/* test wrapper function */
	test_wrapper();

	return 0;
}