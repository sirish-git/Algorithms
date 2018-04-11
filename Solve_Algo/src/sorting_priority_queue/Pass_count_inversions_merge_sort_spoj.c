#include <stdio.h>

#define INT_MAX		999999999
#define MAX_LEN		200005

int inp_arr[MAX_LEN];
int tmp_arr1[MAX_LEN / 2];
int tmp_arr2[MAX_LEN / 2];

long long merge_combine(int p, int q, int r)
{
	int n1, n2;
	int i, j, k;
	long long inv_cnt;

	n1 = q - p + 1;
	n2 = r - q;
	//copy left array to temp
	for (k = 0; k < n1; k++)
	{
		tmp_arr1[k] = inp_arr[p + k];
	}
	//store max
	tmp_arr1[k] = INT_MAX;
	//copy right array to temp
	for (k = 0; k < n2; k++)
	{
		tmp_arr2[k] = inp_arr[q + 1 + k];
	}
	//store max
	tmp_arr2[k] = INT_MAX;

	inv_cnt = 0;
	//combine
	i = j = 0;
	for (k = p; k <= r; k++)
	{
		if (tmp_arr1[i] <= tmp_arr2[j])
		{
			inp_arr[k] = tmp_arr1[i];
			i++;
		}
		else
		{
			inp_arr[k] = tmp_arr2[j];
			j++;

			if(tmp_arr1[i] != INT_MAX)
			{
				inv_cnt += (n1-i); //remainig elements are all greater than this right array element
			}
		}
	}

	return inv_cnt;
}

long long merge_sort(int p, int r)
{
	long long q, inv_cnt;

	inv_cnt = 0;
	if (p < r)
	{
		q = p + ((r - p) >> 1);

		inv_cnt  = merge_sort(p, q);
		inv_cnt += merge_sort(q+1, r);

		inv_cnt += merge_combine(p, q, r);
	}
	return inv_cnt;
}

int main()
{
	int T, t_cnt;
	int N;
	int i, j;
	long long inv_cnt;

	scanf("%d", &T);
	//scanf("%d", &N); //dummy
	for (t_cnt = 0; t_cnt < T; t_cnt++)
	{
		scanf("%d", &N);
		for (i = 0; i < N; i++)
		{
			scanf("%d", &inp_arr[i]);
		}
		//scanf("%d", &inp_arr[i]); //dummy

		inv_cnt = merge_sort(0, N - 1);
		printf("%lld\n", inv_cnt);
	}

	return 0;
}