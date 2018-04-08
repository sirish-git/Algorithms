//Distinct substrings lexicographic order using suffix array

#include <stdio.h>
#include <string.h>

#define MAX_LEN		90001
struct suf_arr_
{
	int index;
	int rank_cur;
	int rank_nxt;
};
struct suf_arr_ suf_arr[MAX_LEN];
int g_lcp[MAX_LEN];
int g_index[MAX_LEN];
int g_str_len;
char g_inp[MAX_LEN];


//store sort index, start & end index of org string
//int g_sort_idx[MAX_LEN * 1500][2];
int g_substr_cnt;

struct suf_arr_ sa_tmp[MAX_LEN];
int count_cur[MAX_LEN], count_nxt[MAX_LEN];

void count_sort()
{
	int i, max;

	max = g_str_len > 256 ? g_str_len : 256;

	//clear counts
	for(i = 0; i <= max; i++)
	{
		count_cur[i] = 0;
		count_nxt[i] = 0;
	}

	//fill histogram counts
	for(i = 0; i < g_str_len; i++)
	{
		count_cur[suf_arr[i].rank_cur + 1] += 1; //+1 since -1 rank can be there
		count_nxt[suf_arr[i].rank_nxt + 1] += 1; //+1 since -1 rank can be there
	}

	//find cumulative indexes
	for(i = 1; i <= max; i++)
	{
		count_cur[i] += count_cur[i-1];
		count_nxt[i] += count_nxt[i-1];
	}

	//sort counts based on next ranks
	for(i = 0; i < g_str_len; i++)
	{
		//sort next and copy complete structure
		sa_tmp[count_nxt[suf_arr[i].rank_nxt + 1] - 1] = suf_arr[i]; //-1 for count sort indexing
		//decrement counts
		count_nxt[suf_arr[i].rank_nxt + 1] --;
	}

	//finally sort the current ranks based on sorted next ranks
	for(i = g_str_len - 1; i >= 0; i--) //index from end
	{
		int actual_idx, suffix_idx;

		//sort cur ranks based next ranks
		suf_arr[count_cur[sa_tmp[i].rank_cur + 1] - 1] = sa_tmp[i];

		//save index
		actual_idx = suf_arr[count_cur[sa_tmp[i].rank_cur + 1] - 1].index;
		suffix_idx = count_cur[sa_tmp[i].rank_cur + 1] - 1;
		g_index[actual_idx] = suffix_idx;

		//decrement counts
		count_cur[sa_tmp[i].rank_cur + 1] --;
	}
}

void construct_suffix_array()
{
	int i, j, id;
	int rank, rank_c;
	int len;

	//assign ranks to 1st, 2nd chars
	for(i = 0; i < (g_str_len - 1); i++)
	{
		suf_arr[i].index = i;
		suf_arr[i].rank_cur = g_inp[i]; //use ASCII value as rank
		suf_arr[i].rank_nxt = g_inp[i+1];
	}
	//for last char
	suf_arr[i].index = i;
	suf_arr[i].rank_cur = g_inp[i]; //use ASCII value as rank
	suf_arr[i].rank_nxt = -1; //next char not there, so assign least

	//sort ranks
	count_sort();

	//processes string in terms of 2^i lengths
	for(i = 4; i < 2 * g_str_len; i = 2 * i)
	{
		//assign ranks based on (cur, nxt) rank pair current suffix and prev suffix
		{
			rank_c = suf_arr[0].rank_cur;
			//first rank is zero
			suf_arr[0].rank_cur = 0;
			rank = 0;
			for(j = 1; j < g_str_len; j++)
			{
				if(suf_arr[j].rank_cur == rank_c && suf_arr[j].rank_nxt == suf_arr[j-1].rank_nxt)
				{
				}
				else
				{
					rank++;
				}
				rank_c = suf_arr[j].rank_cur;
				suf_arr[j].rank_cur = rank;
			}
		}

		//find next ranks
		{
			len = i/2;
			for(j = 0; j < g_str_len; j++)
			{
				//cur suffix index
				id = suf_arr[j].index;
				//add length to go next string
				id += len;
				if(id >= g_str_len)
				{
					//next string is not avialable, so assign least
					rank = -1;
				}
				else
				{
					//find corresponding suffix index for rank
					id = g_index[id];
					rank = suf_arr[id].rank_cur;
				}
				suf_arr[j].rank_nxt = rank;
			}
		}

		//sort ranks
		count_sort();
	}
}

void construct_lcp_array()
{
	int i, j, id, k;

	k = 0;
	for(i = 0; i < g_str_len; i++)
	{
		//if suffix index is last so no next string
		if(g_index[i] == (g_str_len - 1))
		{
			k = 0;
			g_lcp[g_str_len - 1] = 0;
			continue;
		}

		//find next suffix index
		j = suf_arr[g_index[i] + 1].index;

		//compare these two suffixes to find match length
		//idea: we are checking within the input string, if match is len k, then next match would be >=k-1
		//hence start matching from k
		while((i + k) < g_str_len && (j + k) < g_str_len && g_inp[i + k] == g_inp[j + k])
		{
			k++;
		}
		//store lcp
		g_lcp[g_index[i]] = k;

		//delete 1 char
		if(k > 0)
		{
			k--;
		}
	}
}

void find_dist_substrings()
{
	int i, id, j;
	int lcp, len, cnt;

	//this arranges in lexicographical order

	//core idea is, find lcp length, the chars beyond lcp length will contribute to distinct substings
	//which starting from the start char of current string

	//compare from current string to previous string lcp
	lcp = 0; //for first char
	for(i = 0; i < g_str_len; i++)
	{		
		//find length of suffix using index's
		id = suf_arr[i].index;
		len = g_str_len - id;
		//find count of sub strings possible (which is beyond lcp length)
		cnt = len - lcp;
		if(cnt > 0)
		{
			//store sub strigns id's (to save the memory by avoiding storing of strings itself)
			//for(j = 0; j < cnt; j++)
			//{
				//start id
				//g_sort_idx[g_substr_cnt + j][0] = id;
				//end id
				//g_sort_idx[g_substr_cnt + j][1] = id + lcp + j;
			//}
			//update substring counter
			g_substr_cnt += cnt;
		}
		//lcp for next suffix comparison
		lcp = g_lcp[i];
	}
}

int main()
{
	int i, j;
	int q, k;
	int start_id, end_id;
	int k_arr[501];

	int T, test_cases;

	scanf("%d", &T);

	for(test_cases = 0; test_cases < T; test_cases++)
	{
		//read input string
		scanf("%s", g_inp);
		g_str_len = strlen(g_inp);

		construct_suffix_array();

		construct_lcp_array();

		g_substr_cnt = 0;
		find_dist_substrings();

		printf("%d\n", g_substr_cnt);
	}

	return 0;
}