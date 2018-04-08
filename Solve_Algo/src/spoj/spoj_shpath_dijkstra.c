
/*
Problem Source:
http://www.spoj.com/problems/SHPATH/

Editorial/Logic/Ideas Sources: 
1) 
*/


/*
Problem Description:

SHPATH - The Shortest Path
#shortest-path #dijkstra-s-algorithm
You are given a list of cities. Each direct connection between two cities has its transportation cost (an integer bigger than 0). The goal is to find the paths of minimum cost between pairs of cities. Assume that the cost of each path (which is the sum of costs of all direct connections belongning to this path) is at most 200000. The name of a city is a string containing characters a,...,z and is at most 10 characters long.

Input
 

s [the number of tests <= 10]
n [the number of cities <= 10000]
NAME [city name]
p [the number of neighbours of city NAME]
nr cost [nr - index of a city connected to NAME (the index of the first city is 1)]
           [cost - the transportation cost]
r [the number of paths to find <= 100]
NAME1 NAME2 [NAME1 - source, NAME2 - destination]
[empty line separating the tests]
 

Output
 

cost [the minimum transportation cost from city NAME1 to city NAME2 (one per line)]
 

Example
 

Input:
1
4
gdansk
2
2 1
3 3
bydgoszcz
3
1 1
3 1
4 4
torun
3
1 3
2 1
4 1
warszawa
2
2 4
3 1
2
gdansk warszawa
bydgoszcz warszawa

Output:
3
2

*/

#include <stdio.h>
#include <string.h>

#define INT_MAX				 99999999
#define INT_MIN				-99999999
#define SUCCESS				0
#define MAX_DIM				10001

static signed char names[MAX_DIM][20];
static signed short neighbor[MAX_DIM][MAX_DIM];
static signed short q_graph_id[MAX_DIM], src[MAX_DIM], dst[MAX_DIM], q_ids[MAX_DIM];
static signed int adj_grid[MAX_DIM][MAX_DIM], q_graph_dist[MAX_DIM], min_dist[MAX_DIM];
static signed int N, q_cnt;

int maintain_min_prior_q_parent(int parent)
{
	int left, right, small;
	int temp;

	if(parent < 1)
	{
		return 0;
	}

	left = parent * 2;
	right = parent * 2 + 1;

	small = parent;
	if(left <= q_cnt)
	{
		if(q_graph_dist[q_graph_id[left]] < q_graph_dist[q_graph_id[parent]])
		{
			small = left;
		}
		else
		{
			small = parent;
		}
	}
	if(right <= q_cnt)
	{
		if(q_graph_dist[q_graph_id[right]] < q_graph_dist[q_graph_id[small]])
		{
			small = right;
		}
	}

	if(small != parent)
	{
		/* swap */
		//swap id's: only node id values are swapped based on the dist values. 
		temp = q_graph_id[parent];
		q_graph_id[parent] = q_graph_id[small];
		q_graph_id[small] = temp;
		//swap Q id's corresponding to original node order
		q_ids[q_graph_id[parent]] = parent;
		q_ids[q_graph_id[small]] = small;

		//swap values: swapping these also gives incorrect output
		//temp = q_graph_dist[id];
		//q_graph_dist[id] = q_graph_dist[small];
		//q_graph_dist[small] = temp;

		maintain_min_prior_q_parent(parent >> 1);
	}
	return 0;
}
int maintain_min_prior_q_child(int parent)
{
	int left, right, small;
	int temp;

	if(parent < 1)
	{
		return 0;
	}

	left = parent * 2;
	right = parent * 2 + 1;

	small = parent;
	if(left <= q_cnt)
	{
		if(q_graph_dist[q_graph_id[left]] < q_graph_dist[q_graph_id[parent]])
		{
			small = left;
		}
		else
		{
			small = parent;
		}
	}
	if(right <= q_cnt)
	{
		if(q_graph_dist[q_graph_id[right]] < q_graph_dist[q_graph_id[small]])
		{
			small = right;
		}
	}

	if(small != parent)
	{
		/* swap */
		//swap id's: only node id values are swapped based on the dist values. 
		temp = q_graph_id[parent];
		q_graph_id[parent] = q_graph_id[small];
		q_graph_id[small] = temp;
		//swap Q id's corresponding to original node order
		q_ids[q_graph_id[parent]] = parent;
		q_ids[q_graph_id[small]] = small;

		//swap values: swapping these also gives incorrect output
		//temp = q_graph_dist[id];
		//q_graph_dist[id] = q_graph_dist[small];
		//q_graph_dist[small] = temp;

		maintain_min_prior_q_child(small);
	}
	return 0;
}

int extract_min_priorty_queue()
{
	int min_id, temp;

	if(q_cnt < 1)
	{
		//queue underflow
	}

	//swap Q id's corresponding to original node order
	q_ids[q_graph_id[1]] = q_cnt;
	q_ids[q_graph_id[q_cnt]] = 1;
	//swap id's
	temp = q_graph_id[1];
	q_graph_id[1] = q_graph_id[q_cnt];
	q_graph_id[q_cnt] = temp;
	
	min_id = temp;
	q_cnt --;

	maintain_min_prior_q_child(1);

	return min_id;
}

int build_min_prior_q()
{
	int i;
	for(i = (q_cnt >> 1); i > 0; i--)
	{
		maintain_min_prior_q_child(i);
	}
	return 0;
}

/* Actual algo funciton */
static signed int core_fn()
{
	signed int i;
	signed int node, child, dist, num_neibh, flag;

	while(q_cnt > 0)
	{
		node = extract_min_priorty_queue();
		num_neibh = neighbor[node][0];
		flag = 0;
		for(i = 1; i <= num_neibh; i++)
		{
			child = neighbor[node][i];

			//relax edge
			dist = q_graph_dist[node] + adj_grid[node][child];
			if(dist <= q_graph_dist[child])
			{
				q_graph_dist[child] = dist;
				flag = 1;
				//update min prioirty q: since adding small values so change parent tree only
				maintain_min_prior_q_parent(q_ids[child] >> 1);
			}
		}
#if 0
		if(flag == 1)
			build_min_prior_q();
#endif
	}
	return 0;
}

int strcmp_own(signed char *src_str, signed char *dst_str)
{
	int i, result;

	i = 0;
	result = 0;
	while(src_str[i] != '\0' && dst_str[i] != '\0')
	{
		if(src_str[i] != dst_str[i])
		{
			result = 1;
			break;
		}
		i++;
	}

	return result;
}

static void test_wrapper()
{
#if 1//def WINDOWS_TEST
	int test_cases, T;
	signed char str[50], name1[50], name2[50];
	signed int correct_ans;
#endif
	signed int i, j, neib_cnt, id, dist, num_paths, result, flag;
	
#if 1//def WINDOWS_TEST
	/* Read number of test cases */
	scanf("%d", &T);
	for(test_cases = 1; test_cases <= T; test_cases++)
#endif
	{
		/* Read Inputs */
		scanf("%d", &N);
		for(i = 1; i <= N; i++)
		{
			scanf("%s", &names[i][0]);
			scanf("%d", &neib_cnt);

			//save neighbor info
			neighbor[i][0] = neib_cnt;
			for(j = 1; j <= neib_cnt; j++)
			{
				scanf("%d %d", &id, &dist);
				neighbor[i][j] = id;
				adj_grid[i][id] = dist;
			}
		}
		scanf("%d", &num_paths);
		for(i = 1; i <= num_paths; i++)
		{
			scanf("%s %s", &name1[0], &name2[0]);
			//find src index
			for(j = 1; j <= N; j++)
			{
				result = strcmp_own(&name1[0], &names[j][0]);
				if(result == 0)
				{
					src[i] = j;
					break;
				}
			}
			//find dst index
			for(j = 1; j <= N; j++)
			{
				result = strcmp_own(&name2[0], &names[j][0]);
				if(result == 0)
				{
					dst[i] = j;
					break;
				}
			}
		}

		/* algo function call */
		for(i = 1; i <= num_paths; i++)
		{
			/* Fill queue */
			q_cnt = N;
			for(j = 1; j <= N; j++)
			{
				q_graph_dist[j] = INT_MAX;
				q_graph_id[j] = j;
				q_ids[j] = j;
			}
			//clear the src node
			q_graph_dist[src[i]] = 0;
			build_min_prior_q();

			core_fn();
			min_dist[i] = q_graph_dist[dst[i]];
		}

		
#ifdef WINDOWS_TEST
		/* Print output */
		printf("#%d ", test_cases);

		/* Test the answer with reference output kept in input file */
		scanf("%s", str);
		flag = 1;
		for(i = 1; i <= num_paths; i++)
		{
			printf("%d ", min_dist[i]);
			scanf("%d", &correct_ans);
			if(min_dist[i] != correct_ans)
			{
				flag = -1;
			}
		}
		if(flag == 1)
		{
			printf(" Success: Output is matching with Reference output\n");
		}
		else
		{
			printf(" !!FAILURE: Output is NOT matching with Reference output\n");
		}
#else
		for(i = 1; i <= num_paths; i++)
		{
			printf("%d\n", min_dist[i]);
		}
#endif
	}
}

int main()
{
#ifdef WINDOWS_TEST
	printf("\n\n ++++++++ spoj - shpath ++++++++\n\n");

	freopen("../test/spoj/spoj_shpath.txt", "r", stdin);
#endif

	/* test wrapper function */
	test_wrapper();

	return 0;
}