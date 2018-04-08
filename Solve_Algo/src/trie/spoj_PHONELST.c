
/*
Problem Source:
http://www.spoj.com/problems/PHONELST/

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
int N;

typedef struct trie
{
	struct trie *child[10];
	char is_end_of_word;
	char char_cnt;
};

#define MAX_WORD_LEN	10
#define MAX_WORDS		10001
struct trie trie_list[MAX_WORD_LEN * MAX_WORDS];
int g_trie_list_cnt;

//init trie root node
void init_trie_node(struct trie *trie_node)
{
	int i;

	trie_node->is_end_of_word = FALSE;
	trie_node->char_cnt = 0;
	for(i = 0; i < 10; i++)
	{
		trie_node->child[i] = NULL;
	}
}

//build trie
int build_trie()
{
	int i, idx;
	char word[21];
	struct trie *trie_node;

	//read the word
	scanf("%s", &word[0]);

	//root node
	trie_node = &trie_list[0];

	//add chars in trie
	i = 0;
	while(word[i] != '\0')
	{
		idx = word[i] - '0';
		if(trie_node->child[idx] == NULL)
		{
			if(trie_node->is_end_of_word == TRUE)
			{
				//a number already exist with this prefix
				return -1;
			}

			//incremnt for new char
			trie_node->char_cnt++;
			//create new child node from array pool
			g_trie_list_cnt++;
			trie_node->child[idx] = &trie_list[g_trie_list_cnt];
			//init child node
			init_trie_node(trie_node->child[idx]);
		}
		else
		{
		}
		//point to child node
		trie_node = trie_node->child[idx];

		i++;
	}
	//mark last child as end of word
	trie_node->is_end_of_word = TRUE;
	if(trie_node->char_cnt >= 1)
	{
		//a number already exist with this prefix
		return -1;
	}

	return 0;
}


static void test_wrapper()
{
	int test_cases, T;
	int i, status;
	char word[11];
	
	/* Read number of test cases */
	scanf("%d", &T);
	for(test_cases = 1; test_cases <= T; test_cases++)
	{
		/* Read Inputs */
		scanf("%d", &N);

		//init root node
		init_trie_node(&trie_list[0]);
		//build trie
		g_trie_list_cnt = 0;
		for(i = 0; i < N; i++)
		{
			status = build_trie();
			if(status == -1)
			{
				i++;
				//dummy parsing of input
				for(; i < N; i++)
				{
					//read the word
					scanf("%s", &word[0]);
				}
				break;
			}
		}

		if(status == 0)
			printf("YES\n");
		else
			printf("NO\n");
	}
}

int main()
{
#ifdef WINDOWS_TEST
	printf("\n\n ++++++++ SPOJ - PHONELST ++++++++\n\n");

	freopen("../test/trie/spoj_PHONELST.txt", "r", stdin);
#endif

	/* test wrapper function */
	test_wrapper();

	return 0;
}