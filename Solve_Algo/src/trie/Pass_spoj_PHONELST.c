#include <stdio.h>

#define MAX_LEN_WD		11
#define MAX_ENTRIES		10005 * MAX_LEN_WD

struct _tri
{
	struct _tri *ch_nd[10];
	char is_end_of_word;
	char child_cnt;
};

struct _tri tri;
struct _tri tri_pool[MAX_ENTRIES];
int tri_pool_cnt;
int prefix_exist;

struct _tri *get_node()
{
	int i;
	struct _tri *new_nd;

	new_nd = &tri_pool[tri_pool_cnt];
	tri_pool_cnt++;

	//init
	new_nd->is_end_of_word = 0;
	new_nd->child_cnt = 0;
	for (i = 0; i < 10; i++)
	{
		new_nd->ch_nd[i] = NULL;
	}

	return new_nd;
}

void build_tri(char *str)
{
	int i;
	char ch;
	struct _tri *new_nd, *cur_nd;

	cur_nd = &tri;
	for (i = 0; str[i] != '\0'; i++)
	{
		ch = str[i] - '0';
		if (cur_nd->ch_nd[ch] == NULL)
		{
			cur_nd->ch_nd[ch] = get_node();
			cur_nd->child_cnt++;
		}
		cur_nd = cur_nd->ch_nd[ch];

		//check if its a full word already exist
		if (cur_nd->is_end_of_word == 1)
		{
			//dont build trie further
			prefix_exist = 1;
			break;
		}
	}

	//a number already exisit
	if (cur_nd->child_cnt >= 1)
	{
		prefix_exist = 1;
	}

	cur_nd->is_end_of_word = 1;	
}

int main()
{
	int t, t_cnt;
	int n;
	int i;
	char str[11];

	scanf("%d", &t);
	for (t_cnt = 0; t_cnt < t; t_cnt++)
	{
		scanf("%d", &n);

		//clear trie
		tri_pool_cnt = 0;
		tri.is_end_of_word = 0;
		tri.child_cnt = 0;
		for (i = 0; i < 10; i++)
		{
			tri.ch_nd[i] = NULL;
		}

		//build trie
		tri_pool_cnt = 0;
		prefix_exist = 0;
		for (i = 0; i < n; i++)
		{
			scanf("%s", str);
			if (prefix_exist == 0)
			{
				build_tri(str);
			}
		}

		if (prefix_exist == 0)
		{
			printf("YES\n");
		}
		else
		{
			printf("NO\n");
		}
	}

	return 0;
}
