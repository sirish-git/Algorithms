
/*
Problem Source:


Editorial/Logic/Ideas Sources: 
1) 
*/


/*
Problem Description:



*/

#include <stdio.h>
#include <string.h>

#define NOT_VISITED			0
#define VISITED				1
#define PIZZA_HUT			32
#define BUILDING			64
#define INT_MAX				 99999999
#define INT_MIN				-99999999
#define SUCCESS				0
#define MAX_DIM				55
#define NODE_CNT			(MAX_DIM * MAX_DIM)


static signed int input[MAX_DIM][MAX_DIM], adj_grid[NODE_CNT][NODE_CNT], neighbor[NODE_CNT][NODE_CNT];
static signed int q_graph_id[NODE_CNT], q_ids[NODE_CNT];
static signed int q_graph_dist[NODE_CNT];
static signed int M, N, q_cnt, total_sum, min_diff, minimum_time;
static signed int min_time[NODE_CNT], build_cnt;

int abs(int diff)
{
	if(diff < 0)
		return -diff;
	else
		return diff;
}


int find_min_sub_set(int id, int sum1)
{
	int i, run_sum, set1_sum, set2_sum, diff;

	if(id > (build_cnt - 2))
	{
		//last 2 elements
		//
		set1_sum = sum1 + min_time[build_cnt-1];
		set2_sum = total_sum - set1_sum;
		diff = abs(set1_sum - set2_sum);
		if(diff < min_diff)
		{
			min_diff = diff;
			if(set1_sum > set2_sum)
			{
				minimum_time = set1_sum;
			}
			else
			{
				minimum_time = set2_sum;
			}
		}
		//
		set1_sum = sum1 + min_time[build_cnt];
		set2_sum = total_sum - set1_sum;
		diff = abs(set1_sum - set2_sum);
		if(diff < min_diff)
		{
			min_diff = diff;
			if(set1_sum > set2_sum)
			{
				minimum_time = set1_sum;
			}
			else
			{
				minimum_time = set2_sum;
			}
		}

		return 0;
	}

	for(i = id; i <= build_cnt; i++)
	{
		run_sum = sum1 + min_time[i];
		find_min_sub_set(i+1, run_sum);
	}

	return 0;
}


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
	}
	return 0;
}

static void test_wrapper()
{
#if 1//def WINDOWS_TEST
	int test_cases, T;
	char str[10], ch, inp[MAX_DIM];
	signed int correct_ans;
#endif
	signed int i, j, k, m, id, flag, val;
	signed int node, neighbor_cnt;
	signed int src_node, dst_nodes[NODE_CNT], min_scr;
	
#if 1//def WINDOWS_TEST
	/* Read number of test cases */
	scanf("%d", &T);
	for(test_cases = 1; test_cases <= T; test_cases++)
#endif
	{
		/* Read Inputs */
		scanf("%d %d", &M, &N);
		build_cnt = 0;
		for(i = 0; i < M; i++)
		{
			scanf("%s", &inp[0]);
			for(j = 0; j < N; j++)
			{
				ch = inp[j];
				switch(ch)
				{
				case 'X':
					input[i][j] = PIZZA_HUT;
					break;

				case '$':
					input[i][j] = BUILDING;
					build_cnt++;
					break;

				default:
					input[i][j] = inp[j] - 48;
					break;
				}
			}
		}

		//update as graph nodes
		id = 1;
		node = 1;
		for(i = 0; i < M; i++)
		{
			for(j = 0; j < N; j++)
			{
				neighbor_cnt = 0;
				val = input[i][j];
				switch(val)
				{
				case PIZZA_HUT:
					src_node = node;

					//update as graph nodes
					if(j > 0)
					{
						//left
						adj_grid[node][node-1] = 2;
						neighbor_cnt++;
						neighbor[node][neighbor_cnt] = node-1;
					}
					if(j < (N-1))
					{
						//right
						adj_grid[node][node+1] = 2;
						neighbor_cnt++;
						neighbor[node][neighbor_cnt] = node+1;
					}
					if(i > 0)
					{
						//top
						adj_grid[node][node-N] = 2;
						neighbor_cnt++;
						neighbor[node][neighbor_cnt] = node-N;
					}
					if(i < (M-1))
					{
						//bottom
						adj_grid[node][node+N] = 2;
						neighbor_cnt++;
						neighbor[node][neighbor_cnt] = node+N;
					}
					neighbor[node][0] = neighbor_cnt;

					break;

				case BUILDING:
					dst_nodes[id] = node;
					id++;

					//update as graph nodes
					if(j > 0)
					{
						//left
						adj_grid[node][node-1] = 2;
						neighbor_cnt++;
						neighbor[node][neighbor_cnt] = node-1;
					}
					if(j < (N-1))
					{
						//right
						adj_grid[node][node+1] = 2;
						neighbor_cnt++;
						neighbor[node][neighbor_cnt] = node+1;
					}
					if(i > 0)
					{
						//top
						adj_grid[node][node-N] = 2;
						neighbor_cnt++;
						neighbor[node][neighbor_cnt] = node-N;
					}
					if(i < (M-1))
					{
						//bottom
						adj_grid[node][node+N] = 2;
						neighbor_cnt++;
						neighbor[node][neighbor_cnt] = node+N;
					}
					neighbor[node][0] = neighbor_cnt;

					break;

				default:
					//update as graph nodes
					if(j > 0)
					{
						//left
						if(abs(input[i][j] - input[i][j-1]) == 0)
						{
							adj_grid[node][node-1] = 1;
							neighbor_cnt++;
							neighbor[node][neighbor_cnt] = node-1;
						}
						else
						if(abs(input[i][j] - input[i][j-1]) == 1)
						{
							adj_grid[node][node-1] = 3;
							neighbor_cnt++;
							neighbor[node][neighbor_cnt] = node-1;
						}
						else
						if(abs(input[i][j] - input[i][j-1]) > 16)
						{
							//building
							adj_grid[node][node-1] = 2;
							neighbor_cnt++;
							neighbor[node][neighbor_cnt] = node-1;
						}
					}
					if(j < (N-1))
					{
						//right
						if(abs(input[i][j] - input[i][j+1]) == 0)
						{
							adj_grid[node][node+1] = 1;
							neighbor_cnt++;
							neighbor[node][neighbor_cnt] = node+1;
						}
						else
						if(abs(input[i][j] - input[i][j+1]) == 1)
						{
							adj_grid[node][node+1] = 3;
							neighbor_cnt++;
							neighbor[node][neighbor_cnt] = node+1;
						}
						else
						if(abs(input[i][j] - input[i][j+1]) > 16)
						{
							//building
							adj_grid[node][node+1] = 2;
							neighbor_cnt++;
							neighbor[node][neighbor_cnt] = node+1;
						}
					}
					if(i > 0)
					{
						//top
						if(abs(input[i][j] - input[i-1][j]) == 0)
						{
							adj_grid[node][node-N] = 1;
							neighbor_cnt++;
							neighbor[node][neighbor_cnt] = node-N;
						}
						else
						if(abs(input[i][j] - input[i-1][j]) == 1)
						{
							adj_grid[node][node-N] = 3;
							neighbor_cnt++;
							neighbor[node][neighbor_cnt] = node-N;
						}
						else
						if(abs(input[i][j] - input[i-1][j]) > 16)
						{
							//building
							adj_grid[node][node-N] = 2;
							neighbor_cnt++;
							neighbor[node][neighbor_cnt] = node-N;
						}
					}
					if(i < (M-1))
					{
						//bottom
						if(abs(input[i][j] - input[i+1][j]) == 0)
						{
							adj_grid[node][node+N] = 1;
							neighbor_cnt++;
							neighbor[node][neighbor_cnt] = node+N;
						}
						else
						if(abs(input[i][j] - input[i+1][j]) == 1)
						{
							adj_grid[node][node+N] = 3;
							neighbor_cnt++;
							neighbor[node][neighbor_cnt] = node+N;
						}
						else
						if(abs(input[i][j] - input[i+1][j]) > 16)
						{
							//building
							adj_grid[node][node+N] = 2;
							neighbor_cnt++;
							neighbor[node][neighbor_cnt] = node+N;
						}
					}
					neighbor[node][0] = neighbor_cnt;

					break;
				}

				node++;
			}
		}


		/* Fill queue */
		q_cnt = node-1;
		for(j = 1; j < node; j++)
		{
			q_graph_dist[j] = INT_MAX;
			q_graph_id[j] = j;
			q_ids[j] = j;
		}
		//clear the src node
		q_graph_dist[src_node] = 0;
		build_min_prior_q();

		/* algo function call */
		core_fn();

		//clear
		for(k = 1; k <= (build_cnt + 1); k++)
		{
			min_time[k] = INT_MAX;
		}

		min_scr = -1;
		for(k = 1; k <= build_cnt; k++)
		{
			min_scr = q_graph_dist[dst_nodes[k]];

			if(min_scr >= INT_MAX)
			{
				min_scr = -1;
				break;
			}
			//sort & store the counts
			id = 1;
			flag = 0;
			for(m = 1; m < k; m++)
			{
				if(min_scr < min_time[m])
				{
					flag = 1;
					id = m;
					break;
				}
			}
			if(flag == 0)
			{
				min_time[k] = min_scr;
			}
			else
			{
				//move elements
				for(m = k; m >= id; m--)
				{
					min_time[m+1] = min_time[m];
				}
				min_time[id] = min_scr;
			}
		}

		if(min_scr != -1)
		{
			if(build_cnt == 1)
			{
				min_scr = min_time[1];
			}
			else if(build_cnt == 2)
			{
				if(min_time[1] > min_time[2])
				{
					min_scr = min_time[1];
				}
				else
				{
					min_scr = min_time[2];
				}
			}
			else
			{
				total_sum = 0;
				for(i = 1; i <= (build_cnt - 2); i++)
				{
					total_sum += (min_time[i] * 2);
					min_time[i] = min_time[i] * 2;
				}
				for(; i <= build_cnt; i++)
				{
					total_sum += min_time[i];
				}

				min_diff = INT_MAX;
				find_min_sub_set(1, 0);
				min_scr = minimum_time;
			}			
		}

	
#ifdef WINDOWS_TEST
		/* Print output */
		printf("#%d %d\n", test_cases, min_scr);

		/* Test the answer with reference output kept in input file */
		scanf("%s", str);
		scanf("%d", &correct_ans);
		if(min_scr == correct_ans)
		{
			printf(" Success: Output is matching with Reference output\n");
		}
		else
		{
			printf(" !!FAILURE: Output is NOT matching with Reference output\n");
		}
#else
		printf("%d\n", min_scr);
#endif
	}
}

int main()
{
#ifdef WINDOWS_TEST
	printf("\n\n ++++++++ spoj - deliver pizza ++++++++\n\n");

	freopen("../test/spoj/spoj_deliver_pizza.txt", "r", stdin);
#endif

	/* test wrapper function */
	test_wrapper();

	return 0;
}