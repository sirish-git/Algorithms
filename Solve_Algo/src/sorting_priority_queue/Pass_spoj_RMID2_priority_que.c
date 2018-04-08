#include <stdio.h>

#define MAX_SZ	200002

//ds, arrsy
int max_heap[MAX_SZ], min_heap[MAX_SZ];
int max_heap_sz, min_heap_sz;


static void max_heapify(int id)
{
	int left, right, large, tmp;

	left = (id << 1);
	right = (id << 1) + 1;

	//check left child
	if (left <= max_heap_sz && max_heap[left] > max_heap[id])
		large = left;
	else
		large = id;
	//check right child
	if (right <= max_heap_sz && max_heap[right] > max_heap[large])
		large = right;

	if (id != large)
	{
		//swap values
		tmp = max_heap[id];
		max_heap[id] = max_heap[large];
		max_heap[large] = tmp;
		//maintain heap for child
		max_heapify(large);
	}
}

static void min_heapify(int id)
{
	int left, right, small, tmp;

	left = (id << 1);
	right = (id << 1) + 1;

	//check left child
	if (left <= min_heap_sz && min_heap[left] < min_heap[id])
		small = left;
	else
		small = id;
	//check right child
	if (right <= min_heap_sz && min_heap[right] < min_heap[small])
		small = right;

	if (id != small)
	{
		//swap values
		tmp = min_heap[id];
		min_heap[id] = min_heap[small];
		min_heap[small] = tmp;
		//maintain heap for child
		min_heapify(small);
	}
}

void insert_max_heap(int id)
{
	int i, par, tmp;
	i = id;
	par = (i >> 1);

	while (i > 1 && max_heap[par] < max_heap[i])
	{
		//swap parent and child
		tmp = max_heap[i];
		max_heap[i] = max_heap[par];
		max_heap[par] = tmp;
		//change id to parent
		i = par;
		par = (i >> 1);
	}
}

void insert_min_heap(int id)
{
	int i, par, tmp;
	i = id;
	par = (i >> 1);

	while (i > 1 && min_heap[par] > min_heap[i])
	{
		//swap parent and child
		tmp = min_heap[i];
		min_heap[i] = min_heap[par];
		min_heap[par] = tmp;
		//change id to parent
		i = par;
		par = (i >> 1);
	}
}

int main()
{
	int t, t_cnt;
	int val, med;
	int cnt;

	scanf("%d", &t);
	for (t_cnt = 0; t_cnt < t; t_cnt++)
	{
		cnt = 0;
		max_heap_sz = 0;
		min_heap_sz = 0;
		while (1)
		{
			scanf("%d", &val);
			if (val == 0)
			{
				break;
			}
			else if (val == -1)
			{
				//find median
				if (max_heap_sz == min_heap_sz)
				{
#if 0	//generally take avg, but as per this problem take min
					med = (max_heap[1] + min_heap[1]) / 2;
					//remove median element
					max_heap[1] = max_heap[max_heap_sz];
					max_heap_sz--;
					max_heapify(1);
					//remove median element
					min_heap[1] = min_heap[min_heap_sz];
					min_heap_sz--;
					min_heapify(1);
#else
					if (max_heap[1] < min_heap[1])
					{
						med = max_heap[1];
						//remove median element
						max_heap[1] = max_heap[max_heap_sz];
						max_heap_sz--;
						max_heapify(1);
					}
					else
					{
						med = min_heap[1];
						//remove median element
						min_heap[1] = min_heap[min_heap_sz];
						min_heap_sz--;
						min_heapify(1);
					}
#endif
				}
				else if (max_heap_sz > min_heap_sz)
				{
					med = max_heap[1];
					//remove median element
					max_heap[1] = max_heap[max_heap_sz];
					max_heap_sz--;
					max_heapify(1);
				}
				else
				{
					med = min_heap[1];
					//remove median element
					min_heap[1] = min_heap[min_heap_sz];
					min_heap_sz--;
					min_heapify(1);
				}
				printf("%d\n", med);
			}
			else
			{
				if (cnt == 0 || val < max_heap[1])
				{
					//if value less than root on max heap

					//add to end of array
					max_heap_sz++;
					max_heap[max_heap_sz] = val;
					//heap insert
					insert_max_heap(max_heap_sz);
				}
				else
				{
					//if value greater than root on min heap

					//add to end of array
					min_heap_sz++;
					min_heap[min_heap_sz] = val;
					//heap insert
					insert_min_heap(min_heap_sz);
				}
			}

			//balance the heap sizes to max 1 element
			if ((max_heap_sz - min_heap_sz) > 1)
			{
				//add max heap root element to min heap

				val = max_heap[1];
				max_heap[1] = max_heap[max_heap_sz];
				max_heap_sz--;
				max_heapify(1);

				//add to end of array
				min_heap_sz++;
				min_heap[min_heap_sz] = val;
				//heap insert
				insert_min_heap(min_heap_sz);
			}
			else if ((min_heap_sz - max_heap_sz) > 1)
			{
				//add min heap root element to max heap

				val = min_heap[1];
				min_heap[1] = min_heap[min_heap_sz];
				min_heap_sz--;
				min_heapify(1);

				//add to end of array
				max_heap_sz++;
				max_heap[max_heap_sz] = val;
				//heap insert
				insert_max_heap(max_heap_sz);
			}
			
			cnt++;
		}
	}

	return 0;
}