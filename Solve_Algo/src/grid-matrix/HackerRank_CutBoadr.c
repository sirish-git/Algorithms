
#include <stdio.h>
#include <string.h>

#define INT_MAX				 99999999
#define INT_MIN				-99999999
#define SUCCESS				0
#define FAILURE				-1

#define INVALID				-1
#define VISITED				0
#define NOT_VISITED			255
#define MAX_DIM				102

int g_grid[MAX_DIM][MAX_DIM];
int g_row, g_col;
int g_rem_cells;

int g_cord_dfs[MAX_DIM * MAX_DIM][2];
int g_cord_dfs_cnt = 0;

//l,r,t,b
int index_arr[4][2] = {{0, -1},
					   {0, 1}, 
					   {-1, 0}, 
					   {1, 0}};


int dfs(int row, int col, int cell_cnt)
{
	int status;
	int r, c;
	int i;

#if 0
	//base case: check cords
	if(row < 1 || row > g_row || col < 1 || col > g_col)
	{
		return FAILURE;
	}
	//base case: check cell state
	if(g_grid[row][col] == INVALID || g_grid[row][col] == VISITED)
	{
		return FAILURE;
	}
#endif

	//add the co-ords to list
	g_cord_dfs[cell_cnt][0] = row;
	g_cord_dfs[cell_cnt][1] = col;

	//base case: one full path is done
	if((cell_cnt + 1) == g_rem_cells)
	{
		g_cord_dfs_cnt = cell_cnt + 1;
		return SUCCESS;
	}

	//all 4 directions
	for(i = 0; i < 4; i++)
	{
		r = row + index_arr[i][0];
		c = col + index_arr[i][1];

		if(r >= 1 && r <= g_row && c >= 1 && c <= g_col)
		{
			if(g_grid[r][c] == NOT_VISITED)
			{
				//mark the cell as visited
				g_grid[r][c] = VISITED;

				status = dfs(r, c, cell_cnt + 1);
				if(status == SUCCESS)
				{
					return SUCCESS;
				}
				else
				{
					//un mark
					g_grid[r][c] = NOT_VISITED;
				}
			}
		}
	}

	return FAILURE;
}


static void test_wrapper(int n, int m, int x, int y)
{
	int i, j;
	int status;
	
	g_row = n;
	g_col = m;
			
		g_rem_cells = g_row * g_col - (x + y);
		if(g_rem_cells & 0x1)
		{
			printf("NO\n");
			//odd number is remained, so not possible
			return;
		}

		//fill the grid
		for(i = 1; i <= g_row; i++) //indexing from 1
		{
			if(i == 1)
			{
				//first row
				for(j = 1; j <= g_col; j++)
				{
					if(j <= x)
					{
						g_grid[i][j] = INVALID;
					}
					else
					{
						g_grid[i][j] = NOT_VISITED;
					}
				}
			}
			else if(i == g_row)
			{
				//last row
				for(j = 1; j <= g_col; j++)
				{
					if(j > (g_col - y))
					{
						g_grid[i][j] = INVALID;
					}
					else
					{
						g_grid[i][j] = NOT_VISITED;
					}
				}
			}
			else
			{
				for(j = 1; j <= g_col; j++)
				{
					g_grid[i][j] = NOT_VISITED;
				}
			}
		}

		g_cord_dfs_cnt = 0;
		//mark the cell as visited
		g_grid[1][x+1] = VISITED;

		//find path
		status = dfs(1, x+1, 0);
		if(status == SUCCESS)
		{
			//print all the cords
			printf("YES\n");
			printf("%d\n", g_cord_dfs_cnt);
			for(i = 0; i < g_cord_dfs_cnt; i+=2)
			{
				if(g_cord_dfs[i][0] == g_cord_dfs[i+1][0])
				{
					if(g_cord_dfs[i][1] < g_cord_dfs[i+1][1])
					{
						printf("%d %d %d %d\n", g_cord_dfs[i][0], g_cord_dfs[i][1], g_cord_dfs[i+1][0], g_cord_dfs[i+1][1]);
					}
					else
					{
						printf("%d %d %d %d\n", g_cord_dfs[i+1][0], g_cord_dfs[i+1][1], g_cord_dfs[i][0], g_cord_dfs[i][1]);
					}
				}
				else
				if(g_cord_dfs[i][0] < g_cord_dfs[i+1][0])
				{
					printf("%d %d %d %d\n", g_cord_dfs[i][0], g_cord_dfs[i][1], g_cord_dfs[i+1][0], g_cord_dfs[i+1][1]);
				}
				else
				{
					printf("%d %d %d %d\n", g_cord_dfs[i+1][0], g_cord_dfs[i+1][1], g_cord_dfs[i][0], g_cord_dfs[i][1]);
				}
			}
		}
		else
		{
			printf("NO\n");
		}
}

int main()
{
#ifdef WINDOWS_TEST
	int test_cases, T;
#endif
	int x, y;

#ifdef WINDOWS_TEST
	/* Read number of test cases */
	scanf("%d", &T);
	for(test_cases = 1; test_cases <= T; test_cases++)
#endif
	{
		/* Read Inputs */
		scanf("%d %d %d %d", &g_row, &g_col, &x, &y);

		/* test wrapper function */
		test_wrapper(g_row, g_col, x, y);
	}
	return 0;
}