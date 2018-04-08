#include <stdio.h>

#define MAX_LEN		10001

int inp_ar[MAX_LEN];


static int max_heapify(int id, int len)
{
	int tmp;
	int l, r;
	int large;

	l = id * 2;
	r = id * 2 + 1;

	//check left large
	if (l <= len && inp_ar[l] > inp_ar[id])
		large = l;
	else
		large = id;

	//check right large
	if (r <= len && inp_ar[r] > inp_ar[large])
		large = r;

	//check if any child is large
	if (id != large)
	{
		//swap elements
		tmp = inp_ar[id];
		inp_ar[id] = inp_ar[large];
		inp_ar[large] = tmp;
		//recursively check childs
		max_heapify(large, len);
	}
}

static int build_max_heap(int len)
{
	int i;

	//max heapify from half to 1
	for (i = len / 2; i >= 1; i--)
	{
		max_heapify(i, len);
	}
}

static void max_heap_sort(int len)
{
	int i, tmp;

	//build max heap
	build_max_heap(len);

	//build sort elements
	for (i = len; i >= 1; i--)
	{
		//swap root (max) element with end
		tmp = inp_ar[1];
		inp_ar[1] = inp_ar[i];
		inp_ar[i] = tmp;
		//max heapify root element with reduces heap size
		max_heapify(1, i-1);
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
		for (i = 1; i <= N; i++)	//a[1] should contain root, so start from 1, carefull with indexing
		{
			scanf("%d", &val);
			inp_ar[i] = val;
		}

		//pass length N
		max_heap_sort(N);	//similarly can sort using min heap

		//print sorted array
		for (i = 1; i <= N; i++)
		{
			printf("%d ", inp_ar[i]);
		}
		printf("\n");
	}

	return 0;
}