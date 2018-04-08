
/*
Problem Source:
http://codeforces.com/contest/732/problem/0

Editorial/Logic/Ideas Sources: 
1) 
*/


/*
Problem Description:  Buy a Shovel

Polycarp urgently needs a shovel! He comes to the shop and chooses an appropriate one. The shovel that Policarp chooses is sold for k burles. Assume that there is an unlimited number of such shovels in the shop.

In his pocket Polycarp has an unlimited number of "10-burle coins" and exactly one coin of r burles (1 ≤ r ≤ 9).

What is the minimum number of shovels Polycarp has to buy so that he can pay for the purchase without any change? It is obvious that he can pay for 10 shovels without any change (by paying the requied amount of 10-burle coins and not using the coin of r burles). But perhaps he can buy fewer shovels and pay without any change. Note that Polycarp should buy at least one shovel.

Input
The single line of input contains two integers k and r (1 ≤ k ≤ 1000, 1 ≤ r ≤ 9) — the price of one shovel and the denomination of the coin in Polycarp's pocket that is different from "10-burle coins".

Remember that he has an unlimited number of coins in the denomination of 10, that is, Polycarp has enough money to buy any number of shovels.

Output
Print the required minimum number of shovels Polycarp has to buy so that he can pay for them without any change.

Examples
input
117 3
output
9
input
237 7
output
1
input
15 2
output
2
Note
In the first example Polycarp can buy 9 shovels and pay 9·117 = 1053 burles. Indeed, he can pay this sum by using 10-burle coins and one 3-burle coin. He can't buy fewer shovels without any change.

In the second example it is enough for Polycarp to buy one shovel.

In the third example Polycarp should buy two shovels and pay 2·15 = 30 burles. It is obvious that he can pay this sum without any change.

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
static signed long long k, r;
static signed long long min_scr;


/* Actual algo funciton */
static void core_fn()
{
	int i;
	int item_val, rem;

	item_val = k;
	for(i = 1; i <= 10; i++)
	{
		rem = (item_val - ((item_val / 10) * 10));
		if(rem == 0 || rem == r)
		{
			min_scr = i;
			break;
		}
		item_val += k;
	}
}

void test_wrap()
{
	int test_cases, T;
	char str[10];
	int ans, correct_ans;
	int i;
	
#ifdef WINDOWS_TEST
	/* Read number of test cases */
	scanf("%d", &T);
	for(test_cases = 1; test_cases <= T; test_cases++)
#endif
	{
		/* Read Inputs */
		scanf("%d %d", &k, &r);

		/* algo function call */
		core_fn();

		
#ifdef WINDOWS_TEST
		/* Print output */
		printf("#%d %d\n", test_cases, min_scr);

		/* Test the answer with reference output kept in input file */
		scanf("%s", str);
		scanf("%d", &correct_ans);
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
		printf("%d\n", min_scr);
#endif
	}
}

void main()
{
#ifdef WINDOWS_TEST
	printf("\n\n ++++++++ Code forces - 732a ++++++++\n\n");

	freopen("../test/code_forces/code_forces_732a.txt", "r", stdin);
#endif

	/* test wrapper function */
	test_wrap();
}