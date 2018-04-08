
#include <stdio.h>
#include <string.h>

#define INT_MAX				 99999999
#define INT_MIN				-99999999
#define SUCCESS				0
#define MAX_DIM				100005

//signed long long input[MAX_DIM];
signed long long N;
char inp_str[MAX_DIM];

//static to get inlined
static void test_wrapper()
{
	int test_cases, T;
	char str[50];
	signed long long correct_ans;
	signed long long i, j;
	int cnt, run_cnt, cnt1, nz_cnt;
	char ch;
	int flag;
	
#ifdef WINDOWS_TEST
	/* Read number of test cases */
	scanf("%d", &T);
	for(test_cases = 1; test_cases <= T; test_cases++)
#endif
	{
		/* Read Inputs */
		scanf("%s", &inp_str);
	
		cnt = 0;
		run_cnt = 0;
		nz_cnt = 0;
		for(i = 0; inp_str[i] != '\0'; i++)
		{
			cnt++;
			flag = 0;
			if(inp_str[i] == 'z' && nz_cnt == 25)
			{
				nz_cnt++;
				break;
			}

			if(inp_str[i] != 'z')
			{
				if(inp_str[i] <= ('a' + nz_cnt))// && inp_str[i] >= ('a' + nz_cnt))
				{
					inp_str[i] = 'a' + nz_cnt;
					nz_cnt++;
				}
			}
			if(nz_cnt >= 26)
			{
				break;
			}
		}

		if(cnt < 26)
		{
			printf("-1\n");
		}
		else if(nz_cnt < 26)
		{
			printf("-1\n");
		}
		else
		{
			printf("%s\n", inp_str);
		}
	}
}

int main()
{
	/* test wrapper function */
	test_wrapper();

	return 0;
}