#include <stdio.h>

#define SUCCESS				0
#define FAIL				-1

#define NOT_VISITED		1
#define VISITED			0

#define MAX_EDGES		1005
#define MAX_NODES		1005

enum _color
{
	WHITE = 1,
	GREY = 0,
	BLACK = -1,
};

struct _graph
{
	enum _color color;
	int node_id;
	int parent;
	int s_time;
	int f_time;
	struct _graph *nd_nxt;
};

struct _graph edge_pool[MAX_EDGES * 2];
int edge_pool_cnt;
struct _graph g_nodes[MAX_NODES];
int top_sort_nd[MAX_NODES];
int sort_cnt;
int in_degree[MAX_NODES];
int visited[MAX_NODES];
int min_heap[MAX_NODES];
int p_q_len;

int time = 0;

struct _graph *add_node(int v1, int v2)
{
	struct _graph *new_edge;

	new_edge = &edge_pool[edge_pool_cnt];
	edge_pool_cnt++;

	//init
	new_edge->node_id = v2;
	new_edge->color = WHITE;
	new_edge->nd_nxt = NULL;
	new_edge->parent = NULL;

	//add direct edge
	if (g_nodes[v1].nd_nxt == NULL)
	{
		g_nodes[v1].nd_nxt = new_edge;
	}
	else
	{
		new_edge->nd_nxt = g_nodes[v1].nd_nxt;
		g_nodes[v1].nd_nxt = new_edge;
	}

	return new_edge;
}

int check_adjacency(int v1, int v2)
{
	struct _graph *cur_nd;

	cur_nd = g_nodes[v1].nd_nxt;
	while (cur_nd != NULL)
	{
		if (cur_nd->node_id == v2)
		{
			return SUCCESS;
		}
		cur_nd = cur_nd->nd_nxt;
	}

	return FAIL;
}

void dfs(int v1)
{
	int v2;
	struct _graph *cur_nd;

	//assign start time and color
	time += 1;
	g_nodes[v1].s_time = time;
	g_nodes[v1].color = GREY;

	cur_nd = g_nodes[v1].nd_nxt;
	while (cur_nd != NULL)
	{
		//get adjacent node
		v2 = cur_nd->node_id;
		//check color
		if (g_nodes[v2].color == WHITE)
		{
			g_nodes[v2].parent = v1;
			dfs(v2);
		}
		cur_nd = cur_nd->nd_nxt;
	}

	//assign finish time and color
	time += 1;
	g_nodes[v1].f_time = time;
	g_nodes[v1].color = BLACK;

	//store vertex's for topologic order
	top_sort_nd[sort_cnt] = v1;
	sort_cnt++;
}

void insert_min_heap(int id)
{
	int parent;
	int i, tmp;

	i = id;
	parent = (i >> 1);

	while (id > 1 && min_heap[parent] > min_heap[i])
	{
		//swap parent and child
		tmp = min_heap[parent];
		min_heap[parent] = min_heap[i];
		min_heap[i] = tmp;
		//swap id's
		i = parent;
		parent = (i >> 1);
	}
}

void min_heapify(int id)
{
	int left, right, smallest;
	int tmp;

	left = id * 2;
	right = id * 2 + 1;

	//left child
	if (left <= p_q_len && min_heap[left] < min_heap[id])
		smallest = left;
	else
		smallest = id;
	//right child
	if (right <= p_q_len && min_heap[right] < min_heap[smallest])
		smallest = right;

	if (smallest != id)
	{
		//swap
		tmp = min_heap[smallest];
		min_heap[smallest] = min_heap[id];
		min_heap[id] = tmp;

		min_heapify(smallest);
	}
}

int extract_min_heap()
{
	int min;

	//extract root
	min = min_heap[1];
	//store last element to root
	min_heap[1] = min_heap[p_q_len];
	p_q_len--;
	//min heapify the heap
	min_heapify(1);

	return min;
}

void bfs_indegree()
{
	int v1, v2;
	struct _graph *cur_nd;

	while (p_q_len >= 1)
	{
		//deq
		v1 = extract_min_heap();
		//store vertex's for topologic order
		top_sort_nd[sort_cnt] = v1;
		sort_cnt++;

		//check adjacency
		cur_nd = g_nodes[v1].nd_nxt;
		while (cur_nd != NULL)
		{
			v2 = cur_nd->node_id;
			if (visited[v2] == NOT_VISITED)
			{
				//reduce in degree
				in_degree[v2]--;
				if (in_degree[v2] == 0)
				{
					visited[v2] = VISITED;
					//inset in min heap
					p_q_len++;
					min_heap[p_q_len] = v2;
					insert_min_heap(p_q_len);
				}
			}
			cur_nd = cur_nd->nd_nxt;
		}
	}
}

int main()
{
	int test_cases, T;
	int v1, v2;
	int n, m;
	int i;

#ifdef WINDOWS_TEST
	/* Read number of test cases */
	scanf("%d", &T);
	for (test_cases = 1; test_cases <= T; test_cases++)
#endif
	{
		scanf("%d %d", &n, &m);

		edge_pool_cnt = 0;
		//clear node points
		for (i = 1; i <= n; i++)
		{
			//clear nodes
			g_nodes[i].color = BLACK;
			g_nodes[i].f_time = 0;
			g_nodes[i].parent = NULL;
			g_nodes[i].nd_nxt = NULL;

			in_degree[i] = 0;
			visited[i] = NOT_VISITED;
		}

		//build adjacency list
		for (i = 0; i < m; i++)
		{
			scanf("%d %d", &v1, &v2);
			//clear vertex
			g_nodes[v1].color = WHITE;
			g_nodes[v2].color = WHITE;

			in_degree[v2]++;

			//directed graph
			add_node(v1, v2);
		}

#if 1
		//build min-priority queue for in-degree 0
		p_q_len = 0;
		for (i = 1; i <= n; i++)
		{
			if (in_degree[i] == 0)
			{
				g_nodes[i].color = BLACK;
				visited[i] = VISITED;

				p_q_len++;
				min_heap[p_q_len] = i;
				insert_min_heap(p_q_len);
			}
		}

		sort_cnt = 0;
		//bfs for top sort
		bfs_indegree();

		//print topology order from end
		for (i = 0; i < sort_cnt; i++)
		{
			printf("%d ", top_sort_nd[i]);
		}
		printf("\n");
#else
		//dfs for all white vertex
		sort_cnt = 0;
		for (i = 1; i <= n; i++)
		{
			if (g_nodes[i].color == WHITE)
			{
				dfs(i);
			}
		}

		//print topology order from end
		for (i = n - 1; i >= 0; i--)
		{
			printf("%d ", top_sort_nd[i]);
		}
		printf("\n");
#endif
	}

	return 0;
}