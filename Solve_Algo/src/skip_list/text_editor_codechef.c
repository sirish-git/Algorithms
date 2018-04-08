#include <stdio.h>

#define MAX_SZ		100001
#define SKIP_LEN	5

struct _nd
{
	char ch;
	//int idx;
	struct _nd *nd_nxt;
};

struct _skipnd
{
	int idx;
	struct _skipnd *skip_nxt;
	struct _nd *nd_ptr;
};

struct _skipnd *g_skip_root, *g_skip_tmp;
struct _nd *g_nd_root, *g_nd_tmp;

struct _skipnd skip_pool[MAX_SZ];
struct _nd node_pool[MAX_SZ];
int skip_pool_cnt, node_pool_cnt;

int g_idx, g_len;
char g_str[MAX_SZ];

struct _nd *create_new_nd(char ch)
{
	struct _nd *nd_new;

	nd_new = &node_pool[node_pool_cnt];
	node_pool_cnt++;
	//init
	nd_new->ch = ch;
	nd_new->nd_nxt = NULL;

	return nd_new;
}

struct _skipnd *create_new_skip_nd(struct _nd *node, int idx)
{
	struct _skipnd *skip_new;

	skip_new = &skip_pool[skip_pool_cnt];
	skip_pool_cnt++;
	//init
	skip_new->idx = idx;
	skip_new->nd_ptr = node;
	skip_new->skip_nxt = NULL;

	return skip_new;
}

void build_list(char *str, struct _nd *nd_cur, struct _skipnd *skip_cur, 
				int pos, int idx)
{
	int i, cnt;
	struct _nd *nd_new;
	struct _skipnd *skip_new;

	cnt = 0;
	for (i = pos; str[i] != '\0'; i++)
	{
		nd_new = create_new_nd(str[i]);
		//swap
		nd_new->nd_nxt = nd_cur->nd_nxt;
		nd_cur->nd_nxt = nd_new;
		nd_cur = nd_new;
		cnt++;
		if (cnt > SKIP_LEN)
		{
			cnt = 0;
			skip_new = create_new_skip_nd(nd_cur, idx + i + 1);
			//swap
			skip_new->skip_nxt = skip_cur->skip_nxt;
			skip_cur->skip_nxt = skip_new;
			skip_cur = skip_new;
		}
	}

	//save current link pointers
	g_skip_tmp = skip_cur;
	g_nd_tmp = nd_cur;
}

void insert_string(char *str, int idx)
{
	int cnt, len;
	struct _nd *nd_new, *nd_cur;
	struct _skipnd *skip_new, *skip_cur, *skip_prev;

	if (g_skip_root == NULL)
	{
		//first string

		//first char
		nd_new = create_new_nd(str[0]);
		g_nd_root = nd_cur = nd_new;
		skip_new = create_new_skip_nd(nd_cur, 1);
		g_skip_root = skip_cur = skip_new;
		//build list
		build_list(str, nd_cur, skip_cur, 1, 0);
	}
	else
	{
		//string exists

		if (idx == 0)
		{
			//insert at the start
			nd_new = create_new_nd(str[0]);
			skip_new = create_new_skip_nd(nd_new, 1);
			//build list
			build_list(str, nd_new, skip_new, 1, 0);
			//add link
			g_nd_tmp->nd_nxt = g_nd_root;
			g_skip_tmp->skip_nxt = g_skip_root;
			//update root
			g_nd_root = nd_new;
			g_skip_root = skip_new;
		}
		else
		{
			//find skip link to add
			skip_cur = g_skip_root;
			while (skip_cur != NULL && skip_cur->idx <= idx)
			{
				skip_prev = skip_cur;
				skip_cur = skip_cur->skip_nxt;
			}

			//reach node link
			nd_cur = skip_prev->nd_ptr;
			cnt = skip_prev->idx;
			while (nd_cur != NULL && cnt < idx)
			{
				cnt++;
				nd_cur = nd_cur->nd_nxt;
			}

			//insert at the start
			nd_new = create_new_nd(str[0]);
			skip_new = create_new_skip_nd(nd_new, 1);
			//build list
			build_list(str, nd_new, skip_new, 1, 0);
			//add link
			g_skip_tmp->skip_nxt = skip_prev->skip_nxt;
			skip_prev->skip_nxt = skip_new;
			//node
			g_nd_tmp->nd_nxt = nd_cur->nd_nxt;
			nd_cur->nd_nxt = nd_new;
		}

		//update the index's for next skip nodes
		len = idx;
		skip_cur = g_skip_tmp;
		while (skip_cur != NULL)
		{
			skip_cur->idx += len;
			skip_cur = skip_cur->skip_nxt;
		}
	}
}

void get_string(char *str, int idx, int len)
{
	int i;
	int cnt;
	struct _nd *nd_new, *nd_cur;
	struct _skipnd *skip_new, *skip_cur, *skip_prev;

	//find skip link to add
	skip_cur = g_skip_root;
	while (skip_cur != NULL && skip_cur->idx < idx)
	{
		skip_prev = skip_cur;
		skip_cur = skip_cur->skip_nxt;
	}

	//reach node link
	nd_cur = skip_prev->nd_ptr;
	cnt = skip_prev->idx;
	while (nd_cur != NULL && cnt < idx)
	{
		cnt++;
		nd_cur = nd_cur->nd_nxt;
	}

	//save string
	cnt = 0;
	while (nd_cur != 0 && cnt < len)
	{
		str[cnt] = nd_cur->ch;
		cnt++;
		nd_cur = nd_cur->nd_nxt;
	}
}

int main()
{
	int i;
	char sign[2];
	int Q;

	//init
	skip_pool_cnt = 0;
	node_pool_cnt = 0;
	g_skip_root = NULL;
	g_nd_root = NULL;

	scanf("%d", &Q);
	for (i = 0; i < Q; i++)
	{
		scanf("%s %d", &sign, &g_idx);

		if (sign[0] == '+')
		{
			scanf("%s", g_str);
			//insert
			insert_string(g_str, g_idx);
		}
		else if (sign[0] == '?')
		{
			scanf("%d", &g_len);
			//get string
			get_string(g_str, g_idx, g_len);
			printf("%s\n", g_str);
		}
	}

	return 0;
}