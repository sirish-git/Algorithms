
/*
Problem Source:
http://codeforces.com/contest/731/problem/F

Solution: 

1) 
*/

/*
Little Vlad is fond of popular computer game Bota-2. Recently, the developers announced the new add-on named Bota-3. Of course, Vlad immediately bought only to find out his computer is too old for the new game and needs to be updated.

There are n video cards in the shop, the power of the i-th video card is equal to integer value ai. As Vlad wants to be sure the new game will work he wants to buy not one, but several video cards and unite their powers using the cutting-edge technology. To use this technology one of the cards is chosen as the leading one and other video cards are attached to it as secondary. For this new technology to work it's required that the power of each of the secondary video cards is divisible by the power of the leading video card. In order to achieve that the power of any secondary video card can be reduced to any integer value less or equal than the current power. However, the power of the leading video card should remain unchanged, i.e. it can't be reduced.

Vlad has an infinite amount of money so he can buy any set of video cards. Help him determine which video cards he should buy such that after picking the leading video card and may be reducing some powers of others to make them work together he will get the maximum total value of video power.

Input
The first line of the input contains a single integer n (1 ≤ n ≤ 200 000) — the number of video cards in the shop.

The second line contains n integers a1, a2, ..., an (1 ≤ ai ≤ 200 000) — powers of video cards.

Output
The only line of the output should contain one integer value — the maximum possible total power of video cards working together.

Examples
input
4
3 2 15 9
output
27
input
4
8 2 2 7
output
18
Note
In the first sample, it would be optimal to buy video cards with powers 3, 15 and 9. The video card with power 3 should be chosen as the leading one and all other video cards will be compatible with it. Thus, the total power would be 3 + 15 + 9 = 27. If he buys all the video cards and pick the one with the power 2 as the leading, the powers of all other video cards should be reduced by 1, thus the total power would be 2 + 2 + 14 + 8 = 26, that is less than 27. Please note, that it's not allowed to reduce the power of the leading video card, i.e. one can't get the total power 3 + 1 + 15 + 9 = 28.

In the second sample, the optimal answer is to buy all video cards and pick the one with the power 2 as the leading. The video card with the power 7 needs it power to be reduced down to 6. The total power would be 8 + 2 + 2 + 6 = 18.



*/

#include <stdio.h>
#include <string.h>

#define RESET				999999
#define INT_MAX				99999999
#define INT_MIN				-99999999
#define DP_INIT				-9999
#define SUCCESS				0
#define MAX_DIM				200001

static unsigned long long inp_string[MAX_DIM];
static unsigned long long N, a, b, c;
static unsigned long long min_rot_cnt, max_power, max_val;


/* Actual algo funciton */
static void video_cards_max()
{
	unsigned long long prim_v, sec_v, div, total_power;
	unsigned long long i, j, val, val2;
	unsigned long long div_num, div_offset;

	for(i = 1; i <= max_val; i++)
	{
		val = inp_string[i];
		total_power = 0;
		if(val > 0)
		{
			prim_v = i;
			div_offset = i;
			div_num = i;
			for(j = i+1; j <= max_val; j++)
			{
				//find next divisible number to avoid division
				if(j >= (i + div_offset))
				{
					div_offset += i;
					div_num = j;
				}

				val2 = inp_string[j];
				if(val2 > 0)
				{
					sec_v = div_num;
					total_power += (sec_v * val2);
				}
			}

			total_power += val * i;
			if(total_power > max_power)
			{
				max_power = total_power;
			}
		}
	}
}

void test_video_cards()
{
	int test_cases, T;
	char str[10];
	int ans, correct_ans;
	int i, val;
	
#ifdef WINDOWS_TEST
	/* Read number of test cases */
	scanf("%d", &T);
	for(test_cases = 1; test_cases <= T; test_cases++)
#endif
	{
		/* Read */
		/* Read */
		scanf("%d", &N);
		for(i = 1; i < MAX_DIM; i++)
		{
			inp_string[i] = 0;
		}
		max_val = 0;
		for(i = 1; i <= N; i++)
		{
			scanf("%d", &val);
			inp_string[val]++;
			if(val > max_val)
			{
				max_val = val;
			}
		}

		/* algo function call */
		max_power = 0;
		video_cards_max();

		
#ifdef WINDOWS_TEST
		/* Print output */
		printf("#%d %d\n", test_cases, max_power);

		/* Test the answer with reference output kept in input file */
		scanf("%s", str);
		scanf("%d", &correct_ans);
		ans = max_power;
		if(correct_ans == ans)
		{
			printf(" Success: Output is matching with Reference output\n");
		}
		else
		{
			printf(" !!FAILURE: Output is NOT matching with Reference output\n");
		}
#else
		printf("%d\n", max_power);
#endif
	}
}

void main()
{
#ifdef WINDOWS_TEST
	printf("\n\n ++++++++ Code forces - 376_Contest ++++++++\n\n");

	freopen("../test/code_forces/code_forces_731f.txt", "r", stdin);
#endif

	/* test wrapper function */
	test_video_cards();
}