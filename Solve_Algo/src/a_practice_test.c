
#include <stdio.h>
#include <string.h>

#define INT_MAX				 99999999
#define INT_MIN				-99999999
#define SUCCESS				0
#define MAX_DIM				20001

int n;
int min_pos, id_pos;
int g_inp[100001];

void main()
{
	int i;

#ifdef WINDOWS_TEST
	while (1)
	{
#endif
		min_pos = 0; id_pos = -1;
		/* Read Inputs */
		scanf("%d", &n);
		for (i = 0; i < n; i++)
		{
			scanf("%d", &g_inp[i]);
			if (g_inp[i] >= 0)
			{
				g_inp[i] = -g_inp[i] - 1;
			}

			if (g_inp[i] < min_pos)
			{
				min_pos = g_inp[i];
				id_pos = i;
			}
		}
		if (n % 2 != 0)
		{
			g_inp[id_pos] = -g_inp[id_pos] - 1;
		}

		for (i = 0; i < n; i++)
		{
			printf("%d ", g_inp[i]);
		}
		printf("\n");

#ifdef WINDOWS_TEST
	}
#endif
}