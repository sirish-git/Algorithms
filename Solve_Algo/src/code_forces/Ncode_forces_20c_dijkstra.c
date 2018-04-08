
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
#define MAX_DIM				100001

static signed int neighbor[MAX_DIM][MAX_DIM];
static signed int q_graph_id[MAX_DIM], q_ids[MAX_DIM];
static signed int adg_wt[MAX_DIM][MAX_DIM], q_graph_dist[MAX_DIM], min_dist;
static signed int N, edg_cnt, q_cnt;

int maintain_min_prior_q(int id)
{
	int left, right, small;
	int temp;

	left = id * 2;
	right = id * 2 + 1;

	small = id;
	if(left <= q_cnt)
	{
		if(q_graph_dist[q_graph_id[left]] < q_graph_dist[q_graph_id[id]])
		{
			small = left;
		}
		else
		{
			small = id;
		}
	}
	if(right <= q_cnt)
	{
		if(q_graph_dist[q_graph_id[right]] < q_graph_dist[q_graph_id[small]])
		{
			small = right;
		}
	}

	if(small != id)
	{
		/* swap */
		//swap id's: only node id values are swapped based on the dist values. 
		temp = q_graph_id[id];
		q_graph_id[id] = q_graph_id[small];
		q_graph_id[small] = temp;
		//swap Q id's corresponding to original node order
		q_ids[q_graph_id[id]] = id;
		q_ids[q_graph_id[small]] = small;

		//swap values: swapping these also gives incorrect output
		//temp = q_graph_dist[id];
		//q_graph_dist[id] = q_graph_dist[small];
		//q_graph_dist[small] = temp;

		maintain_min_prior_q(q_ids[small] >> 1);
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

	maintain_min_prior_q(1);

	return min_id;
}

int build_min_prior_q()
{
	int i;
	for(i = (q_cnt >> 1); i > 0; i--)
	{
		maintain_min_prior_q(i);
	}
	return 0;
}

/* Actual algo funciton */
static signed int core_fn()
{
	signed int i;
	signed int node, child, dist, num_neibh;

	while(q_cnt > 0)
	{
		node = extract_min_priorty_queue();
		num_neibh = neighbor[node][0];
		for(i = 1; i <= num_neibh; i++)
		{
			child = neighbor[node][i];

			//relax edge
			dist = q_graph_dist[node] + adg_wt[node][child];
			if(dist <= q_graph_dist[child])
			{
				q_graph_dist[child] = dist;
				//update min prioirty q
				//maintain_min_prior_q(child >> 1);
				maintain_min_prior_q(q_ids[child] >> 1);
			}
		}
		//build_min_prior_q();
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
#ifdef WINDOWS_TEST
	int test_cases, T;
	signed char str[50];
	signed int correct_ans;
#endif
	signed int i, j, neib_cnt, id, dist, num_paths, result, cnt;
	int s, d, wt;
	
#ifdef WINDOWS_TEST
	/* Read number of test cases */
	scanf("%d", &T);
	for(test_cases = 1; test_cases <= T; test_cases++)
#endif
	{
		/* Read Inputs */
		scanf("%d %d", &N, &edg_cnt);
		//clear neighbor counts
		for(i = 1; i <= N; i++)
		{
			neighbor[i][0] = 0;
		}

		for(i = 1; i <= edg_cnt; i++)
		{
			scanf("%d %d %d", &s, &d, &wt);
			if(s != d)
			{
				//no self loop
				neighbor[s][0] ++;
				neighbor[d][0] ++;
				//store neighbors
				cnt = neighbor[s][0];
				neighbor[s][cnt] = d;
				//store neighbors: undirected
				cnt = neighbor[d][0];
				neighbor[d][cnt] = s;

				//store weights
				adg_wt[s][d] = wt;
				adg_wt[d][s] = wt;
			}
		}
		/* algo function call */
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
			q_graph_dist[1] = 0;
			build_min_prior_q();

			core_fn();
		}

		if(q_graph_dist[N] == INT_MAX)
		{
			min_dist = -1;
		}
		else
		{
			min_dist = q_graph_dist[N];
		}
		
#ifdef WINDOWS_TEST
		/* Print output */
		printf("#%d %d\n", test_cases, min_dist);

		/* Test the answer with reference output kept in input file */
		scanf("%s", str);
		scanf("%d", &correct_ans);
		if(q_graph_dist[N] == correct_ans)
		{
			printf(" Success: Output is matching with Reference output\n");
		}
		else
		{
			printf(" !!FAILURE: Output is NOT matching with Reference output\n");
		}
#else
		printf("%d\n", min_dist);
#endif
	}
}

int main()
{
#ifdef WINDOWS_TEST
	printf("\n\n ++++++++ Code forces - 20c ++++++++\n\n");

	freopen("../test/code_forces/code_forces_20c.txt", "r", stdin);
#endif

	/* test wrapper function */
	test_wrapper();

	return 0;
}