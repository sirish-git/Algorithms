#include <stdio.h>

#define NULL			0x0
#define MAX_AREAS		10
#define MAX_USERS		1000
#define MAX_FRENS		20
#define HASH_TBL_SZ		8009
#define MAX_PIDS		40005			

struct _aid
{
	int pid;
	int cost;
	struct _aid *nd_prv;
	struct _aid *nd_nxt;
};
struct _pid
{
	int pid;
	int cost;
	int area_id;
	struct _aid *aid_nd;
	struct _pid *nd_nxt;
};
struct _aid_cnts
{
	int reserve_cnt;
	int availbl_cnt;
};
struct _frens
{
	int cnt;
	int frens_id[MAX_FRENS];
};

//data structures
struct _pid *g_hash_pid[HASH_TBL_SZ];
struct _aid *g_aid_list[MAX_AREAS];
struct _aid_cnts g_aid_cnts[MAX_AREAS];
struct _frens g_frens_lst[MAX_USERS][MAX_FRENS];
int g_usr_aid_cnts[MAX_USERS][MAX_AREAS];

//memory pools
struct _pid g_pid_pool[MAX_PIDS * 10]; int g_pid_pool_cnt;
struct _aid g_aid_pool[MAX_PIDS * 10]; int g_aid_pool_cnt;

int g_users_cnt, g_areas_cnt;

void init(int N, int M)
{
	int i, j;
	g_areas_cnt = N;
	g_users_cnt = M;
	//clear pool counters
	g_pid_pool_cnt = 0;
	g_aid_pool_cnt = 0;
	//clear hash table
	for (i = 0; i < HASH_TBL_SZ; i++)
	{
		g_hash_pid[i] = NULL;
	}
	//clear area id lists & counts
	for (i = 0; i < g_areas_cnt; i++)
	{
		g_aid_list[i] = NULL;
		g_aid_cnts[i].availbl_cnt = 0;
		g_aid_cnts[i].reserve_cnt = 0;
	}
	//clear frens count, area counts for each user
	for (i = 0; i < g_users_cnt; i++)
	{
		g_frens_lst[i]->cnt = 0;
		for (j = 0; j < g_areas_cnt; j++)
		{
			g_usr_aid_cnts[i][j] = 0;
		}
	}
}

int find_hash_pid(int pid)
{
	//to reduce collissions
	long long pid_l = pid + ((pid / 10) + 7) * pid;
	int hash;

	hash = (pid_l % HASH_TBL_SZ);
	return hash;
}

struct _aid *get_aid_nd(int cost, int pid)
{
	struct _aid *new_nd;
	new_nd = &g_aid_pool[g_aid_pool_cnt++];
	//init
	new_nd->cost = cost;
	new_nd->pid = pid;
	new_nd->nd_nxt = NULL;
	new_nd->nd_prv = NULL;
	return new_nd;
}

struct _pid *get_pid_nd(int cost, int pid, 
						int area_id, struct _aid *aid_nd)
{
	struct _pid *new_nd;
	new_nd = &g_pid_pool[g_pid_pool_cnt++];
	//init
	new_nd->cost = cost;
	new_nd->pid = pid;
	new_nd->area_id = area_id;
	new_nd->aid_nd = aid_nd;
	new_nd->nd_nxt = NULL;
	return new_nd;
}

void add_aid_node(struct _aid *aid_new_nd, int area_id)
{
	struct _aid *nd_prv, *nd_cur;
	nd_prv = NULL;
	nd_cur = g_aid_list[area_id];
	//sort based on cost
	while (nd_cur != NULL && aid_new_nd->cost > nd_cur->cost)
	{
		nd_prv = nd_cur;
		nd_cur = nd_cur->nd_nxt;
	}
	//sort based on pid, if costs are same
	while (nd_cur != NULL && aid_new_nd->cost == nd_cur->cost &&
							 aid_new_nd->pid  <  nd_cur->pid)
	{
		nd_prv = nd_cur;
		nd_cur = nd_cur->nd_nxt;
	}
	//update links appropriately
	if (nd_prv == NULL)
	{
		//new node to be added at the start
		aid_new_nd->nd_nxt = nd_cur;
		g_aid_list[area_id] = aid_new_nd;
	}
	else if (nd_cur == NULL)
	{
		//new node to be added at the end
		aid_new_nd->nd_prv = nd_prv;
		nd_prv->nd_nxt = aid_new_nd;
	}
	else
	{
		//new node to be inserted in the middle
		//update prev link
		aid_new_nd->nd_prv = nd_prv;
		nd_prv->nd_nxt = aid_new_nd;
		//update next link
		aid_new_nd->nd_nxt = nd_cur;
		nd_cur->nd_prv = aid_new_nd;
	}
}

int add_pid(int pid, int cost, int area_id)
{
	int hash;
	struct _aid *aid_new_nd;
	struct _pid *pid_new_nd;

	hash = find_hash_pid(pid);
	//create new nodes (aid, pid)
	aid_new_nd = get_aid_nd(cost, pid);
	pid_new_nd = get_pid_nd(cost, pid, area_id, aid_new_nd);
	//add pid to hash table
	pid_new_nd->nd_nxt = g_hash_pid[hash];
	g_hash_pid[hash] = pid_new_nd;
	//add aid to the sorted area id list
	add_aid_node(aid_new_nd, area_id);
	//update aread id counts
	g_aid_cnts[area_id].availbl_cnt++;
}

void add_frens(int usr1_id, int usr2_id)
{
	int cnt;
	cnt = g_frens_lst[usr1_id]->cnt;
	//add fren id
	g_frens_lst[usr1_id]->frens_id[cnt] = usr2_id;
	//update count
	g_frens_lst[usr1_id]->cnt++;
}
int add_friend(int usr1_id, int usr2_id)
{
	//add usr1 frend
	add_frens(usr1_id, usr2_id);
	//add usr2 frend
	add_frens(usr2_id, usr1_id);
}

struct _pid *search_pid_nd(int hash, int pid)
{
	struct _pid *pid_nd_prv, *pid_nd_cur;
	pid_nd_prv = NULL;
	pid_nd_cur = g_hash_pid[hash];
	while (pid_nd_cur != NULL && pid_nd_cur->pid != pid)
	{
		pid_nd_prv = pid_nd_cur;
		pid_nd_cur = pid_nd_cur->nd_nxt;
	}
	//update links
	if (pid_nd_prv == NULL)
	{
		//first node to be removed
		g_hash_pid[hash] = pid_nd_cur->nd_nxt;
	}
	else
	{
		pid_nd_prv->nd_nxt = pid_nd_cur->nd_nxt;
	}
	return pid_nd_cur;
}
void remove_aid_nd(struct _aid *aid_nd_cur, int area_id)
{
	struct _aid *aid_nd_prv, *aid_nd_nxt;
	aid_nd_prv = aid_nd_cur->nd_prv;
	aid_nd_nxt = aid_nd_cur->nd_nxt;
	if (aid_nd_prv == NULL)
	{
		//first node to be removed
		g_aid_list[area_id] = aid_nd_nxt;
		aid_nd_nxt->nd_prv = NULL;
	}
	else if (aid_nd_nxt == NULL)
	{
		//last node to be removed
		aid_nd_prv->nd_nxt = NULL;
	}
	else
	{
		//middle node to be removed
		aid_nd_prv->nd_nxt = aid_nd_nxt;
		aid_nd_nxt->nd_prv = aid_nd_prv;
	}
}
int reserve(int pid, int uid)
{
	int hash, area_id;
	struct _pid *pid_nd;	

	hash = find_hash_pid(pid);
	//search for pid
	pid_nd = search_pid_nd(hash, pid);
	//update aread id counts
	area_id = pid_nd->area_id;
	g_aid_cnts[area_id].reserve_cnt++;
	g_aid_cnts[area_id].availbl_cnt--;
	//update user reserve counts
	g_usr_aid_cnts[uid][area_id]++;
	//remove aread id node
	remove_aid_nd(pid_nd->aid_nd, area_id);
}

int recommend(int usr_id)
{

}


void main()
{
}