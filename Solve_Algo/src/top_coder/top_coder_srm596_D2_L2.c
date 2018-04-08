
/*
Problem Source:
https://community.topcoder.com/stat?c=round_overview&rd=15708

Editorial/Logic/Ideas Sources: 
1) 
*/


/*
Problem Description:

Problem Statement for ColorfulRoad


Problem Statement
    	
There is a one-dimensional road. The road is separated into N consecutive parts. The parts are numbered 0 through N-1, in order. Ciel is going to walk from part 0 to part N-1.

Ciel also noticed that each part of the road has a color: either red, green, or blue. Part 0 is red.

Ciel is going to perform a sequence of steps. Each step must lead in the positive direction. That is, if her current part is i, the next step will take her to one of the parts i+1 through N-1, inclusive. Her steps can be arbitrarily long. However, longer steps are harder: a step of length j costs j*j energy.

Additionally, Ciel wants to step on colors in a specific order: red, green, blue, red, green, blue, ... That is, she starts on the red part 0, makes a step to a green part, from there to a blue part, and so on, always repeating red, green, and blue in a cycle. Note that the final part N-1 also has some color and thus Ciel must reach it in a corresponding step.

You are given a String road containing N elements. For each i, element i of road is the color of part i: 'R' represents red, 'G' green, and 'B' blue. If Ciel can reach part N-1 in the way described above, return the smallest possible total cost of doing so. Otherwise, return -1.

 
Definition
    	
Class:	ColorfulRoad
Method:	getMin
Parameters:	String
Returns:	int
Method signature:	int getMin(String road)
(be sure your method is public)
    
 
Constraints
-	road will contain between 2 and 15 characters, inclusive.
-	Each character of road will be either 'R' or 'G' or 'B'.
-	The first character of road will be 'R'.
 
Examples
0)	
    	
"RGGGB"
Returns: 8
The optimum solution is to step part 0 -> part 2 -> part 4. The total cost is 2*2 + 2*2 = 8.
1)	
    	
"RGBRGBRGB"
Returns: 8
The optimum solution is to make steps of length 1. It costs 1*1 = 1 per each step, so the total cost is 8.
2)	
    	
"RBBGGGRR"
Returns: -1
It is impossible to reach the destination.
3)	
    	
"RBRRBGGGBBBBR"
Returns: 50
4)	
    	
"RG"
Returns: 1
5)	
    	
"RBRGBGBGGBGRGGG"
Returns: 52


*/

#include <stdio.h>

#ifndef WINDOWS_TEST
//C++ code for Topcoder
#include <iostream>

using namespace std;
#endif


#define RESET				999999
#define INT_MAX				99999999
#define INT_MIN				-99999999
#define DP_EMPTY			-1
#define DP_INIT				-9999
#define SUCCESS				0
#define MAX_DIM				21


#ifdef WINDOWS_TEST
static signed char input[MAX_DIM];
#else
//C++ code for Topcoder
string input;
#endif

static signed int N;
static signed int max_scr;


#ifndef WINDOWS_TEST
////C++ code for Topcoder: Class name should be same as given in test
class ColorfulRoad
{
public:
#endif

/* Actual algo funciton */
int core_fn(int pos, char a_ch)
{
	int i, min, cost;
	char ch;

	/* base case: bounds */
	if(pos > N)
	{
		return INT_MAX;
	}
	/* base case: incorrect char */
	if(pos > 0)
	{
		switch(a_ch)
		{
		case 'R':
			if(input[pos] != 'G')
			{
				return INT_MAX;
			}
			break;
		case 'G':
			if(input[pos] != 'B')
			{
				return INT_MAX;
			}
			break;
		case 'B':
			if(input[pos] != 'R')
			{
				return INT_MAX;
			}
			break;
		}
	}
	if(pos == (N-1))
	{
		return 0;
	}

	/* return dp result */

	min = INT_MAX;
	ch = input[pos];
	for(i = pos+1; i < N; i++)
	{
		cost = (i-pos) * (i-pos);
		cost += core_fn(i, ch);
		if(cost < min)
		{
			min = cost;
		}
	}

	return min;
}

#ifdef WINDOWS_TEST
int getMin()
#else
//C++ code for Topcoder: Method name & args should be same as given in test
int getMin(string str)
#endif
{
#ifdef WINDOWS_TEST
	int test_cases, T;
	char str[10];
	signed int ans, correct_ans;
#endif
	signed int i;
	
#ifdef WINDOWS_TEST
	/* Read number of test cases */
	scanf("%d", &T);
	for(test_cases = 1; test_cases <= T; test_cases++)
#endif
	{
		/* Read Inputs */
#ifdef WINDOWS_TEST
		scanf("%s", &input[0]);
#else
		//C++ code for Topcoder
		input = str;
#endif
		i = 0;
		while(input[i] != '\0')
		{
			i++;
		}
		N = i;

		/* algo function call */
		max_scr = core_fn(0, 'R');
		if(max_scr == INT_MAX)
		{
			max_scr = -1;
		}
		
#ifdef WINDOWS_TEST
		/* Print output */
		printf("#%d %d\n", test_cases, max_scr);

		/* Test the answer with reference output kept in input file */
		scanf("%s", str);
		scanf("%d", &correct_ans);
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
		//printf("%d\n", max_scr);
		return max_scr;
#endif
	}
}
#ifndef WINDOWS_TEST
//C++ code for Topcoder
};
#endif

#ifdef WINDOWS_TEST
int main()
{
#ifdef WINDOWS_TEST
	printf("\n\n ++++++++ Top Coder - SRM596 DIV2-500 Level2 ++++++++\n\n");

	freopen("../test/top_coder/top_coder_srm596_div2-500.txt", "r", stdin);
#endif

	/* test wrapper function */
	getMin();

	return 0;
}
#endif