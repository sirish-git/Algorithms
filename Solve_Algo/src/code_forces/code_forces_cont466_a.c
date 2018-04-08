
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
#define MAX_DIM				101

int input[MAX_DIM];
int N, D;
int max_scr;


static void test_wrapper()
{
	int test_cases, T;
	int i, j, id, val, min, min_val, max_val, max_dif;
	int min_elem, elem_cnt;
	
#ifdef WINDOWS_TEST
	/* Read number of test cases */
	scanf("%d", &T);
	for(test_cases = 1; test_cases <= T; test_cases++)
#endif
	{
		/* Read Inputs */
		scanf("%d %d", &N, &D);
		//read values
		for(i = 0; i < N; i++)
		{
			scanf("%d", &input[i]);
		}
		//sort
		for(i = 0; i < N; i++)
		{
			id = i;
			min = input[i];
			for(j = i + 1; j < N; j++)
			{
				if(input[j] < min)
				{
					id = j;
					min = input[j];
				}
			}
			if(id != i)
			{
				input[id] = input[i];
				input[i] = min;
			}
		}
		min_val = input[0];
		max_val = input[N-1];
		max_dif = max_val - min_val;

		if(max_dif == D)
		{
			min_elem = 0;
		}
		else
		{
			//remove from both sides with all combinations
			min_elem = 999;
			for(i = 0; i < N; i++)
			{
				for(j = N-1; j >= i; j--)
				{
					elem_cnt = (i - 0) + ((N-1) - j);//(N - 1) - (i + j);
					max_dif = input[j] - input[i];
					if(max_dif <= D)
					{
						if(elem_cnt < min_elem)
						{
							min_elem = elem_cnt;
						}
					}
				}
				if(min_elem == N)
				{
					break;
				}
			}
		}

		printf("%d\n", min_elem);
	}
}

int main()
{
	/* test wrapper function */
	test_wrapper();

	return 0;
}