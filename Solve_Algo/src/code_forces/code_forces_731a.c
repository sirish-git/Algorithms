
/*
Problem Source:
http://codeforces.com/contest/731/problem/0

Solution: 

1) 
*/

/*
Grigoriy, like the hero of one famous comedy film, found a job as a night security guard at the museum. At first night he received embosser and was to take stock of the whole exposition.

Embosser is a special devise that allows to "print" the text of a plastic tape. Text is printed sequentially, character by character. The device consists of a wheel with a lowercase English letters written in a circle, static pointer to the current letter and a button that print the chosen letter. At one move it's allowed to rotate the alphabetic wheel one step clockwise or counterclockwise. Initially, static pointer points to letter 'a'. Other letters are located as shown on the picture:


After Grigoriy add new item to the base he has to print its name on the plastic tape and attach it to the corresponding exhibit. It's not required to return the wheel to its initial position with pointer on the letter 'a'.

Our hero is afraid that some exhibits may become alive and start to attack him, so he wants to print the names as fast as possible. Help him, for the given string find the minimum number of rotations of the wheel required to print it.

Input
The only line of input contains the name of some exhibit — the non-empty string consisting of no more than 100 characters. It's guaranteed that the string consists of only lowercase English letters.

Output
Print one integer — the minimum number of rotations of the wheel, required to print the name given in the input.

Examples
input
zeus
output
18
input
map
output
35
input
ares
output
34
Note
 


To print the string from the first sample it would be optimal to perform the following sequence of rotations:

from 'a' to 'z' (1 rotation counterclockwise),
from 'z' to 'e' (5 clockwise rotations),
from 'e' to 'u' (10 rotations counterclockwise),
from 'u' to 's' (2 counterclockwise rotations).
In total, 1 + 5 + 10 + 2 = 18 rotations are required.

*/

#include <stdio.h>
#include <string.h>

#define RESET				999999
#define INT_MAX				99999999
#define INT_MIN				-99999999
#define DP_INIT				-9999
#define SUCCESS				0
#define MAX_DIM				101

static char inp_string[MAX_DIM];
static int N, a, b, c;
static int min_rot_cnt, max_power;


/* Actual algo funciton */
static int name_clock()
{
	int i = 0;
	char ch;
	int cur_ch, next_ch;
	int len, cnt, min_cnt;

	len = strlen(inp_string);

	min_rot_cnt = 0;
	cur_ch = 'a';
	while(i < len)
	{		
		next_ch = inp_string[i];
		cnt = next_ch - cur_ch;
		if(cnt < 0)
		{
			cnt = -cnt;
		}
		if(cnt < (26 - cnt))
		{
			min_cnt = cnt;
		}
		else
		{
			min_cnt = 26 - cnt;
		}
		min_rot_cnt += min_cnt;

		cur_ch = next_ch;
		i++;
	}

	return 0;
}

void test_name_clock()
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
		/* Read */
		scanf("%s", &inp_string[0]);

		/* algo function call */
		min_rot_cnt = 0;
		name_clock();

		
#ifdef WINDOWS_TEST
		/* Print output */
		printf("#%d %d\n", test_cases, min_rot_cnt);

		/* Test the answer with reference output kept in input file */
		scanf("%s", str);
		scanf("%d", &correct_ans);
		ans = min_rot_cnt;
		if(correct_ans == ans)
		{
			printf(" Success: Output is matching with Reference output\n");
		}
		else
		{
			printf(" !!FAILURE: Output is NOT matching with Reference output\n");
		}
#else
		printf("%d\n", min_rot_cnt);
#endif
	}
}


void main()
{
#ifdef WINDOWS_TEST
	printf("\n\n ++++++++ Code forces - 731a: 376_Contest ++++++++\n\n");

	freopen("../test/code_forces/code_forces_731a.txt", "r", stdin);
#endif

	/* test wrapper function */
	test_name_clock();
}