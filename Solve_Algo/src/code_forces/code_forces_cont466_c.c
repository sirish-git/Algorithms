
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
#define MAX_DIM				100001

char input[MAX_DIM];
char alphabet[26];
int N, K;

static void test_wrapper()
{
	int test_cases, T;
	int i, j, id, index;
	int alpha_cnt, alpha_id_start, alpha_id_end;
	char ch;
	
#ifdef WINDOWS_TEST
	/* Read number of test cases */
	scanf("%d", &T);
	for(test_cases = 1; test_cases <= T; test_cases++)
#endif
	{
		/* Read Inputs */
		scanf("%d %d", &N, &K);
		scanf("%s", &input[0]);

		//clear alphabets
		for(i = 0; i < 26; i++)
		{
			alphabet[i] = 0;
		}

		//fill the available alphabets
		alpha_cnt = 0;
		alpha_id_start = 26;
		alpha_id_end = -1;
		for(i = 0; input[i] != '\0'; i++)
		{
			id = input[i] - 'a';
			if(alphabet[id] == 0)
			{
				alphabet[id] = 1;
				alpha_cnt++;
				if(id > alpha_id_end)
				{
					alpha_id_end = id;
				}
				if(id < alpha_id_start)
				{
					alpha_id_start = id;
				}
			}
			//check if all alphabets filled
			if(alpha_cnt >= 26)
			{
				break;
			}
		}

		//create the lexographically next string compared to 'input'
		if(K > N)
		{
			//append the smallest letters at the end
			ch = alpha_id_start + 'a';
			for(i = N; i < K; i++)
			{
				input[i] = ch;
			}
			input[i] = '\0';
		}
		else
		{
			//check for next big letter available from the end
			ch = alpha_id_end + 'a';
			index = 0;
			for(i = K-1; i >= 0; i--)
			{
				if(ch > input[i])
				{
					index = i;
					break;
				}
			}
			//find next big letter
			id = input[index] - 'a';
			for(i = alpha_id_start; i <= alpha_id_end; i++)
			{
				if(alphabet[i] == 1)
				{
					if(i > id)
					{
						id = i;
						break;
					}
				}
			}
			//write next big letter
			input[index] = id + 'a';
			//fill next positions with small letter till the end
			ch = alpha_id_start + 'a';
			for(i = index + 1; i < K; i++)
			{
				input[i] = ch;
			}
			input[i] = '\0';
		}

		//output
		printf("%s\n", &input[0]);
	}
}

int main()
{
	/* test wrapper function */
	test_wrapper();

	return 0;
}