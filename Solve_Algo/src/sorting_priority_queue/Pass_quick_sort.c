#include <stdio.h>

#define MAX_LEN		10001

int inp_ar[MAX_LEN];


static int partition(int p, int r)
{
	int x;
	int i, j;
	int tmp;

	x = inp_ar[r];
	i = p - 1;
	for (j = p; j < r; j++)
	{
		if (inp_ar[j] <= x)
		{
			i++;
			//swap
			tmp = inp_ar[i];
			inp_ar[i] = inp_ar[j];
			inp_ar[j] = tmp;
		}
	}

	//swap with pivot
	i++;
	tmp = inp_ar[r];
	inp_ar[r] = inp_ar[i];
	inp_ar[i] = tmp;

	return i;
}

static void quick_sort(int p, int r)
{
	int q;
	if (p < r)
	{
		q = partition(p, r); //qth element is sorted, so sort lower, higher sub-arrays below
		quick_sort(p, q-1);
		quick_sort(q + 1, r);
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
		quick_sort(0, N - 1);

		//print sorted array
		for (i = 0; i < N; i++)
		{
			printf("%d ", inp_ar[i]);
		}
		printf("\n");
	}

	return 0;
}