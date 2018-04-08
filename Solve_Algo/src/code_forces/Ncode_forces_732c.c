
/*
Problem Source:
http://codeforces.com/contest/732/problem/C

Editorial/Logic/Ideas Sources: 
1) 
*/


/*
Problem Description:

Vasiliy spent his vacation in a sanatorium, came back and found that he completely forgot details of his vacation!

Every day there was a breakfast, a dinner and a supper in a dining room of the sanatorium (of course, in this order). The only thing that Vasiliy has now is a card from the dining room contaning notes how many times he had a breakfast, a dinner and a supper (thus, the card contains three integers). Vasiliy could sometimes have missed some meal, for example, he could have had a breakfast and a supper, but a dinner, or, probably, at some days he haven't been at the dining room at all.

Vasiliy doesn't remember what was the time of the day when he arrived to sanatorium (before breakfast, before dinner, before supper or after supper), and the time when he left it (before breakfast, before dinner, before supper or after supper). So he considers any of these options. After Vasiliy arrived to the sanatorium, he was there all the time until he left. Please note, that it's possible that Vasiliy left the sanatorium on the same day he arrived.

According to the notes in the card, help Vasiliy determine the minimum number of meals in the dining room that he could have missed. We shouldn't count as missed meals on the arrival day before Vasiliy's arrival and meals on the departure day after he left.

Input
The only line contains three integers b, d and s (0 ≤ b, d, s ≤ 1018,  b + d + s ≥ 1) — the number of breakfasts, dinners and suppers which Vasiliy had during his vacation in the sanatorium.

Output
Print single integer — the minimum possible number of meals which Vasiliy could have missed during his vacation.

Examples
input
3 2 1
output
1

input
1 0 0
output
0

input
1 1 1
output
0

input
1000000000000000000 0 1000000000000000000
output
999999999999999999


Note
In the first sample, Vasiliy could have missed one supper, for example, in case he have arrived before breakfast, have been in the sanatorium for two days (including the day of arrival) and then have left after breakfast on the third day.

In the second sample, Vasiliy could have arrived before breakfast, have had it, and immediately have left the sanatorium, not missing any meal.

In the third sample, Vasiliy could have been in the sanatorium for one day, not missing any meal.

*/

#include <stdio.h>
#include <string.h>

#define RESET				999999
#define INT_MAX				99999999
#define INT_MIN				-99999999
#define DP_INIT				-9999
#define SUCCESS				0
#define MAX_DIM				200001

static signed long long input[MAX_DIM];
static signed long long bf, dn, sp;
static signed long long min_scr;


/* Actual algo funciton */
static void core_fn()
{
	signed long long max, mid, min;

	min_scr = 0;
	if(bf == dn && bf == sp)
	{
		return;
	}

#if 0
	if(bf < dn)
	{
		if(bf < sp)
		{
			//bf smallest

			if(dn == sp)
			{
				min_scr = (dn - bf) - 1;
				return;
			}
			else
			{
				if(dn > sp)
				{
					min_scr = (dn - bf - 1) + (dn - sp - 1);
					return;
				}
				else
				{
					min_scr = (sp - bf - 1) + (sp - dn - 1);
					return;
				}
			}
		}
		else
		{
			//sp smallest, bf mid, dn big
			if(bf == dn)
			{
				min_scr = (bf - sp - 1);
			}
			else
			{
				min_scr = (bf - dn - 1) + (bf - sp - 1);
			}
		}
	}
	else
	{
		if(dn < sp)
		{
			//dn smallest

			if(bf == sp)
			{
				min_scr = (sp - dn) - 1;
				return;
			}
			else
			{
				if(bf > sp)
				{
					min_scr = (bf - dn - 1) + (bf - sp - 1);
					return;
				}
				else
				{
					min_scr = (sp - bf - 1) + (sp - dn - 1);
					return;
				}
			}
		}
		else
		{
			//sp smallest, bf mid, dn big
			if(bf == dn)
			{
				min_scr = (bf - sp - 1);
			}
			else
			{
				min_scr = (bf - dn - 1) + (bf - sp - 1);
			}
			return;
		}
	}
#else
	if(bf < dn)
	{
		if(bf < sp)
		{
			min = bf;
			if(dn < sp)
			{
				mid = dn;
				max = sp;
			}
			else
			{
				mid = sp;
				max = dn;
			}
		}
		else
		{
			min = sp;
			mid = bf;
			max = dn;
		}
	}
	else
	{
		if(dn < sp)
		{
			min = dn;
			if(bf < sp)
			{
				mid = bf;
				max = sp;
			}
			else
			{
				mid = sp;
				max = bf;
			}
		}
		else
		{
			min = sp;
			mid = dn;
			max = bf;
		}
	}

	if(mid == min)
	{
		min_scr = (max - mid - 1);
	}
	else
	{
		min_scr = (max - mid - 1) + (max - min - 1);
	}
#endif
}

void test_wrap()
{
	int test_cases, T;
	char str[10];
	signed long long ans, correct_ans;
	int i;
	
#ifdef WINDOWS_TEST
	/* Read number of test cases */
	scanf("%d", &T);
	for(test_cases = 1; test_cases <= T; test_cases++)
#endif
	{
		/* Read Inputs */
		scanf("%lld %lld %lld", &bf, &dn, &sp);

		/* algo function call */
		core_fn();

		
#ifdef WINDOWS_TEST
		/* Print output */
		printf("#%d %lld\n", test_cases, min_scr);

		/* Test the answer with reference output kept in input file */
		scanf("%s", str);
		scanf("%lld", &correct_ans);
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
		printf("%lld\n", min_scr);
#endif
	}
}

void main()
{
#ifdef WINDOWS_TEST
	printf("\n\n ++++++++ Code forces - 732c ++++++++\n\n");

	freopen("../test/code_forces/code_forces_732c.txt", "r", stdin);
#endif

	/* test wrapper function */
	test_wrap();
}