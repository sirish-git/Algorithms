
/*
Problem Source:
http://www.spoj.com/problems/DICT/

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
	struct trie *child[26];
	char is_end_of_word;
	char char_cnt;
};

#define MAX_WORD_LEN	20
#define MAX_WORDS		25001
struct trie trie_list[MAX_WORD_LEN * MAX_WORDS];
int g_trie_list_cnt;

char result_word[21];
char g_prefix_cnt;

//init trie root node
void init_trie_node(struct trie *trie_node)
{
	int i;

	trie_node->is_end_of_word = FALSE;
	trie_node->char_cnt = 0;
	for(i = 0; i < 26; i++)
	{
		trie_node->child[i] = NULL;
	}
}

//build trie
void build_trie()
{
	int i, idx;
	char word[21];
	struct trie *trie_node;

	//read the word
	scanf("%s", &word[0]);

	//check the validity of char
	i = 0;
	while(word[i] != '\0')
	{
		if(word[i] < 'a' || word[i] > 'z')
		{
			//incorrect char
			return;
		}
		i++;
	}

	//root node
	trie_node = &trie_list[0];

	//add chars in trie
	i = 0;
	while(word[i] != '\0')
	{
		idx = word[i] - 'a';
		if(trie_node->child[idx] == NULL)
		{
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
}


//search trie for multiple words
void rec_search_words(struct trie *trie_node, int str_len)
{
	int i;
	int ch_cnt = 0, total_cnt;
	int str_cnt;

	//print words ending here
	if(trie_node->is_end_of_word == TRUE)
	{
		if(str_len != g_prefix_cnt)
		{
			result_word[str_len] = '\0';
			printf("%s\n", result_word);
		}
	}

	//search for other words
	total_cnt = trie_node->char_cnt;
	if(total_cnt > 0)
	{
		for(i = 0; i < 26; i++)
		{
			if(trie_node->child[i] != NULL)
			{
				ch_cnt++;

				//add char to result
				result_word[str_len] = 'a' + i;

				//recursive call
				rec_search_words(trie_node->child[i], str_len + 1);
			}
			if(ch_cnt >= total_cnt)
			{
				break;
			}
		}
	}
}

//search trie
void search_trie()
{
	int i, idx;
	char word[21];
	struct trie *trie_node;

	//read the word
	scanf("%s", &word[0]);

	//root node
	trie_node = &trie_list[0];

	//search pre-fix
	g_prefix_cnt = 0;
	i = 0;
	while(word[i] != '\0')
	{
		idx = word[i] - 'a';
		if(trie_node->child[idx] == NULL)
		{
			printf("No match.\n");
			return;
		}
		//point to child node
		trie_node = trie_node->child[idx];

		//update pre-fix word
		result_word[g_prefix_cnt] = word[i];
		g_prefix_cnt++;

		i++;
	}

	//search multiple words with above pre-fix
	rec_search_words(trie_node, g_prefix_cnt);
}

static void test_wrapper()
{
#ifdef WINDOWS_TEST
	int test_cases, T;
#endif
	int i;
	int K;
	
#ifdef WINDOWS_TEST
	/* Read number of test cases */
	scanf("%d", &T);
	for(test_cases = 1; test_cases <= T; test_cases++)
#endif
	{
		/* Read Inputs */
		scanf("%d", &N);

		//init root node
		init_trie_node(&trie_list[0]);
		//build trie
		g_trie_list_cnt = 0;
		for(i = 0; i < N; i++)
		{
			build_trie();
		}

		//search trie
		scanf("%d", &K);
		for(i = 1; i <= K; i++)
		{
			printf("Case #%d:\n", i);
			search_trie();
		}
	}
}

int main()
{
#ifdef WINDOWS_TEST
	printf("\n\n ++++++++ SPOJ - DICT ++++++++\n\n");

	freopen("../test/trie/spoj_DICT.txt", "r", stdin);
#endif

	/* test wrapper function */
	test_wrapper();

	return 0;
}