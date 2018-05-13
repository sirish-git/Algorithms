#include <stdio.h>

#define NULL			0

#define MAX_LEN			100005
#define HASH_MOD		16001
#define HASH_PRIME		7

struct _hash
{
	int idx;
	struct _hash *nxt;
};
struct _hash h_pool[MAX_LEN];
int h_pool_cnt;
struct _hash *h_tbl[HASH_MOD];

char g_inp[MAX_LEN];
int N, K;
int unique_cnt;

static struct _hash *get_new_node(int index)
{
	struct _hash *new_nd;

	new_nd = &h_pool[h_pool_cnt];
	h_pool_cnt++;

	//init
	new_nd->idx = index;
	new_nd->nxt = NULL;

	return new_nd;
}

static int search_hash(int hash, int id)
{
	struct _hash *new_nd, *cur_nd;
	int i, j;
	int status = 0;
	int match_flag;

	if (h_tbl[hash] == NULL)
	{
		new_nd = get_new_node(id);
		h_tbl[hash] = new_nd;
	}
	else
	{
		//match strings
		cur_nd = h_tbl[hash];
		while (cur_nd != NULL)
		{
			match_flag = 0;
			j = id;
			for (i = cur_nd->idx; i < (cur_nd->idx + K); i++)
			{
				if (g_inp[i] != g_inp[j])
				{
					match_flag = -1;
					break;
				}
				j++;
			}
			//at least 1 string match repeated
			if (match_flag == 0)
			{
				status = -1;
				break;
			}

			cur_nd = cur_nd->nxt;
		}

		//no match
		if (status == 0)
		{
			new_nd = get_new_node(id);
			new_nd->nxt = h_tbl[hash];
			h_tbl[hash] = new_nd;
		}
	}

	return status;
}

void find_unique_strings()
{
	int i, j;
	int hash, hash_p, hash_p_mod;
	struct _hash *new_nd;
	int status;

	hash = 0;
	hash_p = HASH_PRIME;
	for (i = K - 1; i >= 0; i--)
	{
		hash = (hash + g_inp[i] * hash_p) % HASH_MOD;
		hash_p_mod = hash_p;
		hash_p = (hash_p * HASH_PRIME) % HASH_MOD;
	}
	//add this entry to has table
	unique_cnt++;
	new_nd = get_new_node(0);
	h_tbl[hash] = new_nd;

	for (i = K; i < N; i++)
	{
		j = i - K;
		hash = ((((hash - (g_inp[j] * hash_p_mod) /*% HASH_MOD*/ + g_inp[i]) * HASH_PRIME))) % HASH_MOD;
		if (hash < 0)
		{
			hash += HASH_MOD;
		}

		status = search_hash(hash, j + 1);
		if (status == 0)
		{
			unique_cnt++;
		}
	}
}


int main()
{
	int t, t_cnt;
	int i;

	scanf("%d", &t);
	for (t_cnt = 0; t_cnt < t; t_cnt++)
	{
		scanf("%d %d", &N, &K);
		scanf("%s", &g_inp[0]);

		//clear hash table
		if (K == N)
		{
			unique_cnt = 1;
		}
		else
		{
			h_pool_cnt = 0;
			for (i = 0; i < HASH_MOD; i++)
			{
				h_tbl[i] = NULL;
			}

			unique_cnt = 0;
			find_unique_strings();
		}
		printf("%d\n", unique_cnt);
	}

	return 0;
}