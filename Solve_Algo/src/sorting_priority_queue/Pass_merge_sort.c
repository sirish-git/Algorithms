/*
	=> Problems to solve:
	- https://www.hackerearth.com/practice/algorithms/sorting/merge-sort/tutorial/

*/

#include <stdio.h>

#define INT_MAX		9999999
#define MAX_LEN		10001

int inp_ar[MAX_LEN];
int tmp_ar1[MAX_LEN / 2 + 1];
int tmp_ar2[MAX_LEN / 2 + 1];

static void merge_combine(int p, int q, int r)
{
	int i, j, k;
	int n1, n2;

	//find sizes
	n1 = q - p + 1;
	n2 = r - q;
	//copy the input to temp arrays
	for (i = 0; i < n1; i++)
	{
		tmp_ar1[i] = inp_ar[p + i];
	}
	for (i = 0; i < n2; i++)
	{
		tmp_ar2[i] = inp_ar[q + 1 + i];
	}
	//store max at end (if partitions are of unequal size, it avoids wrong copy)
	tmp_ar1[n1] = INT_MAX;
	tmp_ar2[n2] = INT_MAX;

	//combine
	i = 0;
	j = 0;
	for (k = p; k <= r; k++)	//index 'r' is included
	{
		if (tmp_ar1[i] <= tmp_ar2[j])
		{
			inp_ar[k] = tmp_ar1[i];
			i++;
		}
		else
		{
			inp_ar[k] = tmp_ar2[j];
			j++;
		}
	}
}

//keep reducing the partition length
static void merge_sort(int p, int r)
{
	int q;
	if (p < r)
	{
		//mid point
		//q = (p + r) / 2;
		q = p + (r - p) / 2;	//same as above but avoids addittion overflow for big numbers

		merge_sort(p, q);
		merge_sort(q + 1, r);

		merge_combine(p, q, r);
	}
}

int main()
{
	int t, t_cnt;
	int i, val;
	int N;

	freopen("../test/sorting/sort_inp.txt", "r", stdin);

	scanf("%d", &t);
	for (t_cnt = 0; t_cnt < t; t_cnt++)
	{
		scanf("%d", &N);
		//read input
		for (i = 0; i < N; i++)
		{
			scanf("%d", &val);
			inp_ar[i] = val;
		}

		//pass 0 and length (N-1)
		merge_sort(0, N-1);

		//print sorted array
		for (i = 0; i < N; i++)
		{
			printf("%d ", inp_ar[i]);
		}
		printf("\n");
	}

	return 0;
}