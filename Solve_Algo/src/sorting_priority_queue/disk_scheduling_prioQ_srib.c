#include <stdio.h>

#define MAX_SZ			100001
#define MAX_THRESH		(MAX_SZ * 5)
#define ABS(x) ((x) > 0 ? (x) : -(x))

int g_fcfs_track[MAX_SZ], g_fcfs_cnt, g_fcfs_sz;
int g_scfs_track[MAX_SZ], g_scfs_sz;
int g_look_track[MAX_SZ], g_look_sz;
int g_clook_track[MAX_SZ], g_clook_sz;
int g_head, g_track_sz;

//static helper functions
static void min_heapify(int *arr, int id, int len)
{
	int l, r, small, tmp;

	l = (id << 1);
	r = (id << 1) + 1;
	//check
	if (l <= len && ABS(arr[l] - g_head) < ABS(arr[id] - g_head))
		small = l;
	else
		small = id;
	if (r <= len && ABS(arr[r] - g_head) < ABS(arr[small] - g_head))
		small = r;

	if (small != id)
	{
		//swap
		tmp = arr[id];
		arr[id] = arr[small];
		arr[small] = tmp;
		//recursive heapify child
		min_heapify(arr, small, len);
	}
}

static void insert_min_heap(int *arr, int len)
{
	int id, par, tmp;

	id = len;
	par = (id >> 1);
	while (id > 1 && ABS(arr[id] - g_head) < ABS(arr[par] - g_head))
	{
		//swap child and parent
		tmp = arr[id];
		arr[id] = arr[par];
		arr[par] = tmp;
		//update id, parent
		id = par;
		par = (id >> 1);
	}
}

//API's
void init(int track_size, int head)
{
	g_track_sz = track_size;
	g_head = head;

	//init variables
	g_fcfs_cnt = 1;
	g_fcfs_sz = 0;
	g_scfs_sz = 0;
	g_look_sz = 0;
	g_clook_sz = 0;
}

void track(int track)
{
	//add to all 4 arrays
	g_fcfs_sz++; 
	g_fcfs_track[g_fcfs_sz] = track;
	//need min heap
	g_scfs_sz++;
	g_scfs_track[g_scfs_sz] = track;
	//use min heap (add offset for values greater than head)
	g_look_sz++;
	g_look_track[g_look_sz] = (track > g_head) ? (track + MAX_THRESH) : track;
	//use min heap (add offset for values greater than head and make last values small)
	g_clook_sz++;
	g_clook_track[g_clook_sz] = (track > g_head) ? (MAX_THRESH - track) : track;

	//insert in to min heaps
	//scfs
	insert_min_heap(g_scfs_track, g_scfs_sz);
	//look
	insert_min_heap(g_look_track, g_look_sz);
	//clook
	insert_min_heap(g_clook_track, g_clook_sz);
}

int fcfs()
{
	int track;

	track = g_fcfs_track[g_fcfs_cnt];
	g_fcfs_cnt++;

	return track;
}

int scfs()
{
	int track;

	track = g_scfs_track[1];

	//remove root and heapify
	g_scfs_track[1] = g_scfs_track[g_scfs_sz];
	g_scfs_sz--;
	min_heapify(g_scfs_track, 1, g_scfs_sz);

	return track;
}

int look()
{
	int track;

	track = g_look_track[1];
	track = (track > g_head) ? (track - MAX_THRESH) : track;

	//remove root and heapify
	g_look_track[1] = g_look_track[g_look_sz];
	g_look_sz--;
	min_heapify(g_look_track, 1, g_look_sz);

	return track;
}

int clook()
{
	int track;

	track = g_clook_track[1];
	track = (track > g_head) ? (MAX_THRESH - track) : track;

	//remove root and heapify
	g_clook_track[1] = g_clook_track[g_clook_sz];
	g_clook_sz--;
	min_heapify(g_clook_track, 1, g_clook_sz);

	return track;
}

//test application
int main()
{
	int t, t_cnt;
	int n, val;
	int total_sz, head;
	int i;

	scanf("%d", &t);
	for (t_cnt = 0; t_cnt < t; t_cnt++)
	{
		scanf("%d %d %d", &total_sz, &n, &head);
		init(total_sz, head);

		for (i = 0; i < n; i++)
		{
			scanf("%d", &val);

			track(val);
		}

		printf(" fcfs output\n");
		for (i = 0; i < n; i++)
		{
			val = fcfs();
			printf("%d ", val);
		}
		printf("\n");

		printf(" scfs output\n");
		for (i = 0; i < n; i++)
		{
			val = scfs();
			printf("%d ", val);
		}
		printf("\n");

		printf(" look output\n");
		for (i = 0; i < n; i++)
		{
			val = look();
			printf("%d ", val);
		}
		printf("\n");

		printf(" clook output\n");
		for (i = 0; i < n; i++)
		{
			val = clook();
			printf("%d ", val);
		}
		printf("\n");
	}

	return 0;
}