#include <stdio.h>

#define MAX_CHAR	21
#define MAX_STR		25001 * MAX_CHAR

struct _tri
{
	struct _tri *c_nd[26];
	int is_end_of_wd;
	int child_cnt;
};

struct _tri tri_pool[MAX_STR];
struct _tri tri;
int tri_pool_cnt;
char res_str[MAX_CHAR];
int g_str_cnt;

struct _tri *get_new_node()
{
	int i;
	struct _tri *new_nd;

	new_nd = &tri_pool[tri_pool_cnt];
	tri_pool_cnt++;

	//clear trie
	new_nd->child_cnt = 0;
	new_nd->is_end_of_wd = 0;
	for (i = 0; i < 26; i++)
	{
		new_nd->c_nd[i] = NULL;
	}

	return new_nd;
}

void build_trie(char *str)
{
	int i;
	char ch;
	struct _tri *cur_nd;

	cur_nd = &tri;
	for (i = 0; str[i] != '\0'; i++)
	{
		ch = str[i] - 'a';
		if (cur_nd->c_nd[ch] == NULL)
		{
			cur_nd->c_nd[ch] = get_new_node();
			cur_nd->child_cnt++;
		}
		cur_nd = cur_nd->c_nd[ch];
	}
	cur_nd->is_end_of_wd = 1;
}

void search_tri_rec(struct _tri *cur_nd, int cnt)
{
	int i;
	int ch_cnt;
	if (cur_nd->is_end_of_wd == 1 && cnt > g_str_cnt)
	{
		res_str[cnt] = '\0';
		printf("%s\n", res_str);
	}

	//search available strings
	ch_cnt = 0;
	for (i = 0; i < 26; i++)
	{
		if (cur_nd->c_nd[i] != NULL)
		{
			res_str[cnt] = 'a' + i;
			search_tri_rec(cur_nd->c_nd[i], cnt + 1);
			ch_cnt++;
		}
		if (ch_cnt >= cur_nd->child_cnt)
		{
			break;
		}
	}
}

int search_trie(char *str)
{
	int i;
	char ch;
	int cnt;
	struct _tri *cur_nd;

	//search prefix
	cur_nd = &tri;
	for (i = 0; str[i] != '\0'; i++)
	{
		ch = str[i] - 'a';
		if (cur_nd->c_nd[ch] == NULL)
		{
			printf("No match.\n");
			return -1;
		}
		cur_nd = cur_nd->c_nd[ch];
	}

	for (cnt = 0; str[cnt] != '\0'; cnt++)
	{
		res_str[cnt] = str[cnt];
	}
	g_str_cnt = cnt;

	//search available strings
	search_tri_rec(cur_nd, cnt);
}

int main()
{
	int N, K;
	int i;
	char str[21];

	//clear trie
	tri_pool_cnt = 0;
	tri.child_cnt = 0;
	tri.is_end_of_wd = 0;
	for (i = 0; i < 26; i++)
	{
		tri.c_nd[i] = NULL;
	}

	scanf("%d", &N);
	//build trie
	for (i = 0; i < N; i++)
	{
		scanf("%s", str);
		build_trie(str);
	}

	scanf("%d", &K);
	//search trie
	for (i = 1; i <= K; i++)
	{
		scanf("%s", str);
		printf("Case #%d:\n", i);
		search_trie(str);
	}

	return 0;
}
