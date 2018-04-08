#include <stdio.h>

#define MAX_SZ		200
struct _pq
{
	int priority;
	int pos_act;
	int pos_new;
};
struct _pq pq_list[MAX_SZ];
struct _pq pq_tmp;

void max_heapify(int id, int len, int flag)
{
	int l, r, large;

	l = (id << 1);
	r = (id << 1) + 1;

	//use flag only first comparison for prioiry once swapped, do it based on position

	//check priority
	if (flag && l <= len && pq_list[l].priority > pq_list[id].priority)
		large = l;
	else if (l <= len && pq_list[l].priority == pq_list[id].priority
					  && pq_list[l].pos_new < pq_list[id].pos_new) //check pos, if priority is same
		large = l;
	else
		large = id;

	if (flag && r <= len && pq_list[r].priority > pq_list[large].priority)
		large = r;
	else if (r <= len && pq_list[r].priority == pq_list[large].priority
					  && pq_list[r].pos_new < pq_list[large].pos_new)
		large = r;

	if (large != id)
	{
		//swap structure elements
		pq_tmp = pq_list[id];
		pq_list[id] = pq_list[large];
		pq_list[large] = pq_tmp;
		//update new position (to go to the end of list)
		if (flag == 1)
			pq_list[large].pos_new += MAX_SZ;
		else
			pq_list[id].pos_new += MAX_SZ;

		max_heapify(large, len, 0);
	}
}
int main()
{
	int t, t_cnt;
	int n, m;
	int val;
	int i;
	int cnt;

	scanf("%d", &t);
	for (t_cnt = 0; t_cnt < t; t_cnt++)
	{
		scanf("%d %d", &n, &m);
		for (i = 1; i <= n; i++)
		{
			scanf("%d", &val);
			//fill structure
			pq_list[i].priority = val;
			pq_list[i].pos_act = i - 1;
			//add offset to push first index to last
			pq_list[i].pos_new = MAX_SZ - i - 1;
		}
		//build max heap
		for (i = n / 2; i >= 1; i--)
		{
			max_heapify(i, n, 1);
		}
		//heap sort
		cnt = 0;
		for (i = n; i >= 1; i--)
		{
			cnt++;
			if (pq_list[1].pos_act == m)
			{
				break;
			}

			//swap structure elements
			pq_tmp = pq_list[1];
			pq_list[1] = pq_list[i];
			pq_list[i] = pq_tmp;

			max_heapify(1, i-1, 1);
		}
		printf("%d\n", cnt);
	}

	return 0;
}