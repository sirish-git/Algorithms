
#include <stdio.h>
#include <string.h>

#define INT_MAX				 99999999
#define INT_MIN				-99999999
#define VISITED				1
#define NOT_VISITED			-1
#define SUCCESS				0
#define MAX_DIM				21

int off[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

struct bfs
{
	char val;
	char visited;
	int d;
	//char parent;
};

struct bfs bfs_visit[MAX_DIM][MAX_DIM];
int que[MAX_DIM * MAX_DIM][2];
int dirty_pos[MAX_DIM][2], dirty_cnt;
int W, H;
int cur_r, cur_c;

static void find_path_bfs()
{
	int first, last;
	int dist;
	int r, c;
	int row, col;
	int cnt;

	//enq first element
	bfs_visit[cur_r][cur_c].d = 0;
	bfs_visit[cur_r][cur_c].visited = VISITED;
	que[0][0] = cur_r;
	que[0][1] = cur_c;

	first = 0; last = 1;
	while (first < last)
	{
		//dq
		r = que[first][0];
		c = que[first][1];
		dist = bfs_visit[r][c].d;
		first++;

		//check all 4 directions
		for (cnt = 0; cnt < 4; cnt++)
		{
			row = r + off[cnt][0];
			col = c + off[cnt][1];
			if (row >= 0 && row < H && col >= 0 && col < W)
			{
				if (bfs_visit[row][col].visited == NOT_VISITED)
				{
					bfs_visit[row][col].visited = VISITED;
					bfs_visit[row][col].d = dist + 1;
					//enq
					que[last][0] = row;
					que[last][1] = col;
					last++;
				}
			}
		}
	}

}

//static to get inlined
static void test_wrapper()
{
	int test_cases, T;
	int i, j, id, cnt;
	int dist, min_dist;
	char ch, str[25];
	int r, c;
	int tot_dist;

#ifdef WINDOWS_TEST
	/* Read number of test cases */
	scanf("%d", &T);
	for (test_cases = 1; test_cases <= T; test_cases++)
#endif
	{
		/* Read Inputs */
		scanf("%d %d", &W, &H);

		dirty_cnt = 0;
		for (i = 0; i < H; i++)
		{
			scanf("%s", str);
			for (j = 0; j < W; j++)
			{
				ch = str[j];
				bfs_visit[i][j].val = ch;
				bfs_visit[i][j].visited = NOT_VISITED;
				bfs_visit[i][j].d = INT_MAX;

				switch (ch)
				{
				case '*':
					dirty_pos[dirty_cnt][0] = i;
					dirty_pos[dirty_cnt][1] = j;
					dirty_cnt++;
					break;

				case 'o':
					cur_r = i;
					cur_c = j;
					break;

				case 'x':
					bfs_visit[i][j].visited = VISITED;
					break;

				default:
					break;
				}
			}
		}

		tot_dist = 0;
		for(cnt = 0; cnt < dirty_cnt; cnt++)
		{
			//clear visited array
			for (i = 0; i < H; i++)
			{
				for (j = 0; j < W; j++)
				{
					ch = bfs_visit[i][j].val;
					if (ch != 'x')
					{
						bfs_visit[i][j].visited = NOT_VISITED;
						bfs_visit[i][j].d = INT_MAX;
					}
				}
			}

			//bfs: find all paths from source to dirty
			find_path_bfs();

			//find min dist in all paths
			min_dist = INT_MAX;
			for (i = 0; i < dirty_cnt; i++)
			{
				r = dirty_pos[i][0];
				c = dirty_pos[i][1];
				if (r != -1 && c != -1)
				{
					dist = bfs_visit[r][c].d;
					//check if any target is not reachable
					if (dist == INT_MAX)
					{
						break;
					}
					if (dist < min_dist)
					{
						min_dist = dist;
						id = i;
					}
				}
			}
			//check if any target is not reachable
			if (dist == INT_MAX)
			{
				tot_dist = -1;
				break;
			}

			//add dist
			tot_dist += min_dist;
			//save the next coord
			cur_r = dirty_pos[id][0];
			cur_c = dirty_pos[id][1];
			//mark visited positions
			dirty_pos[id][0] = -1;
			dirty_pos[id][1] = -1;
		}

		if (tot_dist == -1)
		{
			printf("-1\n");
		}
		else
		{
			printf("%d\n", tot_dist);
		}
	}
}

int main()
{
	/* test wrapper function */
	test_wrapper();

	return 0;
}