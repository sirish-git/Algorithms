
#include <stdio.h>
#include <string.h>

#define INT_MAX				 99999999
#define INT_MIN				-99999999
#define VISITED				1
#define NOT_VISITED			-1
#define SUCCESS				0
#define MAX_DIM				1000001

struct bfs
{
	char visited;
	int d;
	//char parent;
};

int f, s, g, u, d;
struct bfs bfs_visit[MAX_DIM];
int que[MAX_DIM];

static int find_path_bfs()
{
	int first, last;
	int dist;
	int min_cnt;
	int id, nx;

	//enq first element
	bfs_visit[s].d = 0;
	bfs_visit[s].visited = VISITED;
	que[0] = s;

	first = 0; last = 1;
	min_cnt = -1;
	while (first < last)
	{
		//dq
		id = que[first];
		dist = bfs_visit[id].d;
		first++;

		if (id == g)
		{
			min_cnt = dist;
			break;
		}

		//up
		nx = id + u;
		if (nx <= f)
		{
			if (bfs_visit[nx].visited == NOT_VISITED)
			{
				bfs_visit[nx].visited = VISITED;
				bfs_visit[nx].d = dist + 1;
				//enq
				que[last] = nx;
				last++;
			}
		}

		//down
		nx = id - d;
		if (nx >= 1)
		{
			if (bfs_visit[nx].visited == NOT_VISITED)
			{
				bfs_visit[nx].visited = VISITED;
				bfs_visit[nx].d = dist + 1;
				//enq
				que[last] = nx;
				last++;
			}
		}
	}

	return min_cnt;
}

//static to get inlined
static void test_wrapper()
{
	int test_cases, T;
	int i;
	int min_cnt;

#ifdef WINDOWS_TEST
	/* Read number of test cases */
	scanf("%d", &T);
	for (test_cases = 1; test_cases <= T; test_cases++)
#endif
	{
		/* Read Inputs */
		scanf("%d %d %d %d %d", &f, &s, &g, &u, &d);
		min_cnt = 0;
		if (s == g)
		{
			min_cnt = 0;
		}
		else
		{
			//clear visited array
			for (i = 0; i <= f; i++)
			{
				bfs_visit[i].visited = NOT_VISITED;
				bfs_visit[i].d = INT_MAX;
			}
			//bfs
			min_cnt = find_path_bfs();
		}

		if (min_cnt == -1)
		{
			printf("use the stairs\n");
		}
		else
		{
			printf("%d\n", min_cnt);
		}
	}
}

int main()
{
	/* test wrapper function */
	test_wrapper();

	return 0;
}