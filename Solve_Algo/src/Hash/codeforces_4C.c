
/*
Problem Source:
http://codeforces.com/problemset/problem/4/C

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
#define MAX_DIM				20001

static signed long long input[MAX_DIM];
static signed long long N;
static signed long long max_scr;

struct hash_str
{
	struct hash_str *node_nxt;
	char str[33];
	int hash_cnt;
};

#define MAX_HASH_SIZE	(100000 + 1)
struct hash_str hash_pool[MAX_HASH_SIZE];
int g_hash_pool_cnt;

#define HASH_PRIME		2
#define HASH_SIZE		107
struct hash_str hash_list[HASH_SIZE];

char g_str[33];


//init 
void init_hash_node(struct hash_str *hash_node)
{
	hash_node->node_nxt = NULL;
	hash_node->hash_cnt = 0;
}

int find_hash()
{
	int i;
	char ch;
	long long hash_val = 0;
	long long hash_pow;
	int hash_result;

	i = 0;
	hash_pow = 1;
	while(g_str[i] != '\0')
	{
		ch = g_str[i];
		hash_val += ch * hash_pow;
		hash_pow *= HASH_PRIME;

		i++;
	}

	hash_result = (hash_val % HASH_SIZE);
	return hash_result;
}

/* Actual algo funciton */
void core_fn()
{
	int i, j;
	int hash_val;
	int hash_found;
	struct hash_str *hash_root, *hash_node, *hash_nxt, *hash_tmp_ptr;

	for(i = 0; i < N; i++)
	{
		scanf("%s", &g_str[0]);
		hash_val = find_hash();

		//search/add in hash table
		hash_root = &hash_list[hash_val];
		if(hash_root->hash_cnt == 0)
		{
			//add new node

			//mark root as at least one element added
			hash_root->hash_cnt = 1;

			//get new node
			hash_node = &hash_pool[g_hash_pool_cnt];
			g_hash_pool_cnt++;
			//init new node
			init_hash_node(hash_node);
			//copy the string
			j = 0;
			while(g_str[j] != '\0')
			{
				hash_node->str[j] = g_str[j];
				j++;
			}
			hash_node->str[j] = '\0';
			//add the entry in hash table
			hash_root->node_nxt = hash_node;

			printf("OK\n");
		}
		else
		{
			//search and/or add new node
			hash_found = 0;
			hash_nxt = hash_root->node_nxt;
			while(hash_nxt != NULL)
			{
				//search the string
				j = 0;
				while(g_str[j] != '\0' || hash_nxt->str[j] != '\0')
				{
					if(g_str[j] != hash_nxt->str[j])
					{
						break;
					}
					j++;
				}
				if(g_str[j] == '\0' && hash_nxt->str[j] == '\0')
				{
					//both strigns are equal, string found
					hash_found = 1;
					break;
				}
				hash_nxt = hash_nxt->node_nxt;
			}

			if(hash_found == 1)
			{
				//both strigns are equal, string found
				hash_nxt->hash_cnt++;
				printf("%s%d\n", g_str, hash_nxt->hash_cnt);
			}
			else
			{
				//string not there in hash table
				//get new node
				hash_node = &hash_pool[g_hash_pool_cnt];
				g_hash_pool_cnt++;
				//init new node
				init_hash_node(hash_node);
				//copy the string
				j = 0;
				while(g_str[j] != '\0')
				{
					hash_node->str[j] = g_str[j];
					j++;
				}
				hash_node->str[j] = '\0';
				//add the entry in hash table
				hash_node->node_nxt = hash_root->node_nxt;
				hash_root->node_nxt = hash_node;

				printf("OK\n");
			}
		}
	}

	return;
}

static void test_wrapper()
{
#ifdef WINDOWS_TEST
	int test_cases, T;
#endif
	int i, j;
	
#ifdef WINDOWS_TEST
	/* Read number of test cases */
	scanf("%d", &T);
	for(test_cases = 1; test_cases <= T; test_cases++)
#endif
	{
		/* Read Inputs */
		scanf("%I64d", &N);

		//init the hash node
		for(i = 0; i < HASH_SIZE; i++)
		{
			init_hash_node(&hash_list[i]);
		}

		/* algo function call */
		g_hash_pool_cnt = 0;
		core_fn();
	}
}

int main()
{
#ifdef WINDOWS_TEST
	printf("\n\n ++++++++ Code forces - 4c ++++++++\n\n");

	freopen("../test/hash/code_forces_4c.txt", "r", stdin);
#endif

	/* test wrapper function */
	test_wrapper();

	return 0;
}