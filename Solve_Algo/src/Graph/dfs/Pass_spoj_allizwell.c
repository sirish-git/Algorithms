#include <stdio.h>

#define SUCCESS			0
#define NOT_VISITED		1
#define VISITED			-1
#define MAX_SZ			102

char inp_ar[MAX_SZ][MAX_SZ];
char visited[MAX_SZ][MAX_SZ];

char dst_str[11] = "ALLIZZWELL";
int rows, cols;
int dir_off[8][2] = { { 0, 1 },{ 0, -1 },{ 1, 0 },{ -1, 0 },{ -1, -1 },{ -1, 1 },{ 1, -1 },{ 1, 1 } };


static int find_path_dfs(int r, int c, int cnt)
{
	int i, j;
	int row, col;
	int status;

	//base: target value
	if (inp_ar[r][c] != dst_str[cnt])
	{
		return -1;
	}
	//base: target reached
	if (cnt == 9)
	{
		return SUCCESS;
	}

	//check for all directions
	status = -1;
	for (i = 0; i < 8; i++)
	{
		row = r + dir_off[i][0];
		col = c + dir_off[i][1];
		//boundary
		if (row >= 0 && row < rows && col >= 0 && col < cols)
		{
			if (visited[row][col] == NOT_VISITED)
			{
				//mark visited
				visited[row][col] = VISITED;
				status = find_path_dfs(row, col, cnt + 1);
				//mark visited
				visited[row][col] = NOT_VISITED;
				if (status == SUCCESS)
				{
					break;
				}
			}
		}
	}

	return status;
}

int main()
{
	int i, j;
	int t, t_cnt;
	int r, c;
	int status;

	scanf("%d", &t);
	for (t_cnt = 0; t_cnt < t; t_cnt++)
	{
		scanf("%d %d", &rows, &cols);
		for (i = 0; i < rows; i++)
		{
			scanf("%s", &inp_ar[i]);
		}

		//clear visited array
		for (r = 0; r < rows; r++)
		{
			for (c = 0; c < cols; c++)
			{
				visited[r][c] = NOT_VISITED;
			}
		}

		status = -1;
		for (i = 0; i < rows; i++)
		{
			for (j = 0; j < cols; j++)
			{
				if (inp_ar[i][j] == 'A')
				{
					//mark as visited
					visited[i][j] = VISITED;
					//dfs
					status = find_path_dfs(i, j, 0);
					//mark as visited
					visited[i][j] = NOT_VISITED;

					if (status == SUCCESS)
					{
						break;
					}
				}
			}
			if (status == SUCCESS)
			{
				break;
			}
		}

		if (status == SUCCESS)
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