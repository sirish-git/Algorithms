
/*
Problem Source:
http://www.spoj.com/problems/SUBXOR/

Editorial/Logic/Ideas Sources: 
1) 
*/


/*
Problem Description:

*/

#include <stdio.h>
#include <string.h>

#define FALSE	0
#define TRUE	1
int N, K;

typedef struct trie
{
	struct trie *child[10];
	char is_end_of_word;
	char char_cnt;
	int xor_val;
};

#define MAX_WORD_LEN	10
#define MAX_WORDS		100001
struct trie trie_list[MAX_WORD_LEN * MAX_WORDS];
int g_trie_list_cnt;
long long g_result;

char num_list[MAX_WORDS];

//init trie root node
void init_trie_node(struct trie *trie_node)
{
	int i;

	trie_node->is_end_of_word = FALSE;
	trie_node->char_cnt = 0;
	trie_node->xor_val = 1000000 + 1; //10^6
	for(i = 0; i < 10; i++)
	{
		trie_node->child[i] = NULL;
	}
}

//build trie
int build_trie()
{
	int i, j, idx;
	int xor_val;
	struct trie *trie_node;

	//add chars in trie

	//build trie for all subarrays
	for(i = 0; i < N; i++)
	{
		//root node
		trie_node = &trie_list[0];
		idx = num_list[i];
		if(trie_node->child[idx] == NULL)
		{
			//incremnt for new char
			trie_node->char_cnt++;
			//create new child node from array pool
			g_trie_list_cnt++;
			trie_node->child[idx] = &trie_list[g_trie_list_cnt];
			//init child node
			init_trie_node(trie_node->child[idx]);
			//xor val for root original value
			trie_node->xor_val = idx;
		}
		xor_val = idx;
		//point to child node
		trie_node = trie_node->child[idx];

		//build trie for all subarrays
		for(j = i+1; j < N; j++)
		{
			idx = num_list[j];
			if(trie_node->child[idx] == NULL)
			{
				//incremnt for new char
				trie_node->char_cnt++;
				//create new child node from array pool
				g_trie_list_cnt++;
				trie_node->child[idx] = &trie_list[g_trie_list_cnt];
				//init child node
				init_trie_node(trie_node->child[idx]);
				//compute xor val
				trie_node->xor_val = xor_val ^ idx;
				xor_val = trie_node->xor_val;
			}
			else
			{
				xor_val = trie_node->xor_val;
			}
			//update result
			if(xor_val < K)
			{
				g_result++;
			}
			else
			{
				//break;
			}

			//point to child node
			trie_node = trie_node->child[idx];
		}
	}

	return 0;
}


static void test_wrapper()
{
	int test_cases, T;
	int i, j, status, val;
	char word[11];
	
	/* Read number of test cases */
	scanf("%d", &T);
	for(test_cases = 1; test_cases <= T; test_cases++)
	{
		/* Read Inputs */
		scanf("%d %d", &N, &K);
		g_result = 0;
		for(i = 0; i < N; i++)
		{
			scanf("%d", &val);
			num_list[i] = val;
			if(val < K)
			{
				g_result++;
			}
		}

		//init root node
		init_trie_node(&trie_list[0]);
		//build trie
		g_trie_list_cnt = 0;
		build_trie();

		printf("%d\n", g_result);
	}
}

int main()
{
#ifdef WINDOWS_TEST
	printf("\n\n ++++++++ SPOJ - SUBXOR ++++++++\n\n");

	freopen("../test/trie/spoj_SUBXOR.txt", "r", stdin);
#endif

	/* test wrapper function */
	test_wrapper();

	return 0;
}