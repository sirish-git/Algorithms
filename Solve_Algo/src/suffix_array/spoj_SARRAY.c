//suffix array

#include <stdio.h>
#include <string.h>

#define MAX_LEN		100002
struct suf_arr_
{
	int index;
	int rank_cur;
	int rank_nxt;
};
struct suf_arr_ suf_arr[MAX_LEN];
char g_inp[MAX_LEN];
int g_index[MAX_LEN];
int g_str_len;

#define COUNT_SORT
#ifdef COUNT_SORT
#else
#define SORT_OPT
#ifdef SORT_OPT
int g_rank0[MAX_LEN], g_rank1[MAX_LEN];
int *g_rank_curr, *g_rank_prev;
int g_opt_flag = 0;
#endif
#endif

#ifdef COUNT_SORT

struct suf_arr_ sa_tmp[MAX_LEN];
int count_cur[MAX_LEN], count_nxt[MAX_LEN];

void count_sort()
{
	//counting sort reduces the complexity

	/*
	core idea:
	> first sort the next ranks
	> sort the current ranks based on the next ranks
	> use next rank as index from bottom
	*/

	int i, max = 256; //256 is max ASCII number

	max = g_str_len > max ? g_str_len : max;

	//clear the counts (both cur, nxt)
	for(i = 0; i <= max; i++) //<= since to count -1 also
	{
		count_cur[i] = 0;
		count_nxt[i] = 0;
	}

	//find histogram (both cur, nxt)
	for(i = 0; i < g_str_len; i++)
	{
		count_cur[suf_arr[i].rank_cur + 1] += 1; //+1 since -1 rank can be there
		count_nxt[suf_arr[i].rank_nxt + 1] += 1; //+1 since -1 rank can be there
	}

	//find cumulative indexes (both cur, nxt)
	for(i = 1; i <= max; i++)
	{
		count_cur[i] += count_cur[i-1];
		count_nxt[i] += count_nxt[i-1];
	}

	//sort next ranks
	for(i = 0; i < g_str_len; i++)
	{
		//copy full structure
		sa_tmp[count_nxt[suf_arr[i].rank_nxt + 1] - 1] = suf_arr[i]; //-1 as indexing is from 1
		//decrement copied index
		count_nxt[suf_arr[i].rank_nxt + 1] --;
	}
	
	//sort current ranks (based on next ranks)
	//finally sort the current ranks based on sorted next ranks
	for(i = g_str_len - 1; i >= 0; i--) //from bottom for correct sorting (check with an example)
	{
		int actual_idx, suffix_idx;

		//copy full structure
		suf_arr[count_cur[sa_tmp[i].rank_cur + 1] - 1] = sa_tmp[i]; //-1 as indexing is from 1

		//save suffix index (reverese index)
		actual_idx = suf_arr[count_cur[sa_tmp[i].rank_cur + 1] - 1].index;
		suffix_idx = count_cur[sa_tmp[i].rank_cur + 1] - 1;
		g_index[actual_idx] = suffix_idx;

		//decrement copied index
		count_cur[sa_tmp[i].rank_cur + 1] --;
	}
}
#else
void sort_ranks_opt()
{
	int i, j, id, index;
	int rank_c, rank_n;
#ifdef SORT_OPT
	int rank_start;
#endif

	for(i = 0; i < g_str_len; i++)
	{
		rank_c = suf_arr[i].rank_cur;
		rank_n = suf_arr[i].rank_nxt;
#ifdef SORT_OPT
		rank_start = g_rank_prev[i];
#endif
		id = i;
		//sort based on both cur and nxt ranks
		for(j = i+1; j < g_str_len; j++)
		{
#ifdef SORT_OPT
			//stop search if rank (prev) is incresed, only need to search in same rank (prev)
			if(g_opt_flag == 1 && g_rank_prev[j] > rank_start)
			{
				break;
			}
#endif
			if(suf_arr[j].rank_cur < rank_c)
			{
				id = j;
				rank_c = suf_arr[j].rank_cur;
				rank_n = suf_arr[j].rank_nxt;
			}
			else if(suf_arr[j].rank_cur == rank_c)
			{
				if(suf_arr[j].rank_nxt < rank_n)
				{
					id = j;
					rank_c = suf_arr[j].rank_cur;
					rank_n = suf_arr[j].rank_nxt;
				}
			}
		}
		if(id != i)
		{
			//swap values
			index = suf_arr[id].index;

			suf_arr[id].index = suf_arr[i].index;
			suf_arr[id].rank_cur = suf_arr[i].rank_cur;
			suf_arr[id].rank_nxt = suf_arr[i].rank_nxt;

			suf_arr[i].index = index;
			suf_arr[i].rank_cur = rank_c;
			suf_arr[i].rank_nxt = rank_n;
		}
		//save suffix index
		g_index[suf_arr[i].index] = i;
#ifdef SORT_OPT
		//save ranks for next sorting optimization
		g_rank_curr[i] = suf_arr[i].rank_cur;
#endif
	}
}
#endif

void construct_suffix_array()
{
	int i, j, id;
	int rank, rank_c;
	int len;

#ifdef SORT_OPT
	int *temptr;
	g_rank_curr = g_rank0;
	g_rank_prev = g_rank1;
	g_opt_flag = 0;
#endif

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
#ifdef COUNT_SORT
	count_sort();
#else
	sort_ranks_opt();
#endif

	//processes string in terms of 2^i lengths
	for(i = 4; i < 2 * g_str_len; i = 2 * i)
	{
#ifdef SORT_OPT
		g_opt_flag = 1;
		//swap rank arrays
		temptr = g_rank_curr;
		g_rank_curr = g_rank_prev;
		g_rank_prev = temptr;
#endif
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
#ifdef COUNT_SORT
		count_sort();
#else
		sort_ranks_opt();
#endif
	}
}

int main()
{
	int i, id;

#ifdef WINDOWS_TEST
	int test_cases, T;

	/* Read number of test cases */
	scanf("%d", &T);
	for(test_cases = 1; test_cases <= T; test_cases++)
#endif
	{
		/* Read Inputs */
		scanf("%s", g_inp);
		g_str_len = strlen(g_inp);

		construct_suffix_array();

		//print sorted array
		for(i = 0; i < g_str_len; i++)
		{
			id = suf_arr[i].index;
			printf("%d\n", id);
		}
	}

	return 0;
}
