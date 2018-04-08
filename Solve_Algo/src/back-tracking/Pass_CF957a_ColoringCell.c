#include <stdio.h>
#include <string.h>

#define INT_MAX				 99999999
#define INT_MIN				-99999999
#define SUCCESS				0
#define FAIL				-1
#define FAIL_STOP			-2
#define MAX_DIM				101

char color[3];
char arr[MAX_DIM];
int sz;
int dest_cnt = 0;

static int dfs_color(int id, char par_clr)
{
	int cnt;
	int status = FAIL;

	//base: dest
	if (id == sz)
	{
		dest_cnt++;
		return SUCCESS;
	}
	//base: parent color
	if (par_clr == arr[id])
	{
		return FAIL;
	}

	if (arr[id] == '?')
	{
		//check all 3 colors
		for (cnt = 0; cnt < 3; cnt++)
		{
			if (color[cnt] != par_clr)
			{
				status = dfs_color(id + 1, color[cnt]);
				if (dest_cnt >= 2)
				{
					return SUCCESS;
				}
				if (status == FAIL_STOP)
				{
					break;
				}
			}
		}
	}
	else
	{
		//if already filled pass
		//check next color, if both are same then not possible
		if ((id + 1) < sz && arr[id] == arr[id + 1])
		{
			return FAIL_STOP;
		}
		else
		{
			status = dfs_color(id + 1, arr[id]);
			if (dest_cnt >= 2)
			{
				return SUCCESS;
			}
		}
	}

	return status;
}

//static to get inlined
static void test_wrapper()
{
	int test_cases, T;
	int status;

	color[0] = 'C';
	color[1] = 'M';
	color[2] = 'Y';

#ifdef WINDOWS_TEST
	/* Read number of test cases */
	scanf("%d", &T);
	for (test_cases = 1; test_cases <= T; test_cases++)
#endif
	{
		/* Read Inputs */
		scanf("%d", &sz);
		scanf("%s", arr);
		dest_cnt = 0;
		status = dfs_color(0, 0);
		if (dest_cnt >= 2)
		{
			printf("Yes\n");
		}
		else
		{
			printf("No\n");
		}
	}
}

int main()
{
	/* test wrapper function */
	test_wrapper();

	return 0;
}