
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

#define NULL 0x0

#define MAX_SIZE		1000000
#define MAX_INP_SIZE	100
#define MAX_BLK_SIZE	4

struct arr_blocks
{
	int size_blk;
	char arr_blk[MAX_BLK_SIZE];
	struct arr_blocks *nxt_blk;
};
struct arr_blocks *root_blk;
struct arr_blocks arr_blks_pool[MAX_SIZE];
int arr_pool_cnt;

int select_id, select_len;

//APIs
void init(char *str)
{
	int i, cnt;
	char *arr_ptr;
	struct arr_blocks *blk_ptr, *blk_new;

	//init
	arr_pool_cnt = 0;
	select_id = -1;
	select_len = 0;

	//init root
	blk_ptr = root_blk = &arr_blks_pool[arr_pool_cnt];
	arr_pool_cnt++;
	blk_ptr->size_blk = 0;
	blk_ptr->nxt_blk = NULL;

	//fill the blocks with input
	cnt = 0;
	arr_ptr = &blk_ptr->arr_blk[cnt];
	for(i = 0; str[i] != '\0'; i++)
	{
		//check if block is full
		if(cnt >= MAX_BLK_SIZE)
		{
			cnt = 0;
			//get next link node
			blk_new = &arr_blks_pool[arr_pool_cnt];
			arr_pool_cnt++;
			//init node
			blk_new->size_blk = 0;
			blk_new->nxt_blk = NULL;
			//add link
			blk_ptr->nxt_blk = blk_new;
			//get array pointer
			blk_ptr = blk_new;
			arr_ptr = &blk_ptr->arr_blk[cnt];
		}

		//copy data
		arr_ptr[cnt] = str[i];
		cnt++;
		blk_ptr->size_blk = cnt;
	}
}

void insert()
{
}

void select(int id, int len)
{
	select_id = id;
	select_len = len;
}

void copy()
{
}

void cut()
{
}

void paste()
{
}

enum _api_type
{
	API_INIT = 0,
	API_INSERT,
	API_SELECT,
	API_COPY,
	API_CUT,
	API_PASTE,
};

char g_str[MAX_INP_SIZE];

static void test_wrapper()
{
	int test_cases, T;
	int api_calls, N;
	int api;
	int i, j;
	
	/* Read number of test cases */
	scanf("%d", &T);
	for(test_cases = 1; test_cases <= T; test_cases++)
	{
		/* Read Inputs */
		scanf("%d", &N);
		for(api_calls = 0; api_calls < N; api_calls++)
		{
			scanf("%d", &api);
			switch(api)
			{
			case API_INIT:
				//read input
				//call api
				init(&g_str[0]);
				break;

			case API_INSERT:
				break;

			case API_SELECT:
				//read input
				//call api
				break;

			case API_COPY:
				break;

			case API_CUT:
				break;

			case API_PASTE:
				break;

			default:
				break;
			}
		}
	}
}

int main()
{
#ifdef WINDOWS_TEST
	freopen("../test/good_probs/text_editor.txt", "r", stdin);
#endif

	/* test wrapper function */
	test_wrapper();

	return 0;
}