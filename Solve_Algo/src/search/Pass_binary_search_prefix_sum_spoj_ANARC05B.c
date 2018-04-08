#include <stdio.h>

#define MAX_LEN		10005

int inp1[MAX_LEN];
int inp2[MAX_LEN];
int pref_sum1[MAX_LEN];
int pref_sum2[MAX_LEN];
int cnt_map[MAX_LEN * 2];
int match_val[MAX_LEN], match_id[MAX_LEN], match_cnt;
int n1, n2;

void build_pref_sum(int len, int inp[MAX_LEN], int pref_sum[MAX_LEN])
{
	int i, val, sum;

	pref_sum[0] = 0;
	sum = 0;
	for (i = 1; i <= len; i++)
	{
		scanf("%d", &val);
		sum += val;

		inp[i] = val;
		pref_sum[i] = sum;

		cnt_map[val + MAX_LEN]++;
		//store matched values
		if (cnt_map[val + MAX_LEN] == 2)
		{
			match_val[match_cnt] = val;
			match_id[match_cnt] = i;
			match_cnt++;
		}
	}
}

int binary_search(int inp[MAX_LEN], int left, int right, int val)
{
	int mid;

	while (left <= right)
	{
		mid = left + (right - left) / 2;
		if (inp[mid] == val)
		{
			return mid;
		}
		if (val < inp[mid])
		{
			right = mid - 1;
		}
		else
		{
			left = mid + 1;
		}
	}

	return left;
}

int main()
{
	int i;
	int id1, id2;
	int id1_prv, id2_prv;
	int val;
	int sum1, sum2, max_sum;

	while(1)
	{
		match_cnt = 0;
		scanf("%d", &n1);
		if (n1 == 0) 
			break;
	
		//clear map
		cnt_map[0] = 0;
		for (i = 0; i < (MAX_LEN * 2); i++)
		{
			cnt_map[i] = 0;
		}

		build_pref_sum(n1, inp1, pref_sum1);

		scanf("%d", &n2);
		build_pref_sum(n2, inp2, pref_sum2);

		max_sum = 0;
		id1 = id2 = 0;
		id1_prv = id2_prv = 0;
		for (i = 0; i < match_cnt; i++)
		{
			id2 = match_id[i]; //2nd array id
			val = match_val[i];

			//search val in first array
			id1 = binary_search(inp1, 1, n1, val);

			//find max sum
			sum1 = pref_sum1[id1] - pref_sum1[id1_prv];
			sum2 = pref_sum2[id2] - pref_sum2[id2_prv];
			if (sum1 > sum2)
				max_sum += sum1;
			else
				max_sum += sum2;

			//swap
			id1_prv = id1;
			id2_prv = id2;
		}

		//find max sum (till array length)
		sum1 = pref_sum1[n1] - pref_sum1[id1];
		sum2 = pref_sum2[n2] - pref_sum2[id2];
		if (sum1 > sum2)
			max_sum += sum1;
		else
			max_sum += sum2;

		printf("%d\n", max_sum);
	}

	return 0;
}