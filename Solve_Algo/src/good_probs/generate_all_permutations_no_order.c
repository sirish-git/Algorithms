/*
Generation all permutations without any order
*/

#include <stdio.h>


/**/
static void swap(char *ptr1, char *ptr2)
{
	int temp;

	temp = *ptr2;
	*ptr2 = *ptr1;
	*ptr1 = temp;
}
static int permute_all_swap_no_order(int left, int right, char *arr)
{
	int i;

	if(left == right)
	{
		//printf("%s", arr);
		for(i = 0; i < right; i++)
		{
			printf("%d ", arr[i]);
		}
		printf("\n");
	}
	else
	{
		for(i = left; i < right; i++)
		{
			swap(&arr[left], &arr[i]);
			permute_all_swap_no_order(left+1, right, arr);
			swap(&arr[left], &arr[i]);
		}
	}

	return 0;
}
static int generate_all_permute_no_order()
{
	int T, N;
	int i, j;
	char arr[10];

	scanf("%d", &T);
	for(i = 0; i < T; i++)
	{
		scanf("%d", &N);
		for(j = 0; j < N; j++)
		{
			scanf("%d", &arr[j]);
		}
		arr[j] = '\0';
		permute_all_swap_no_order(0, N, arr);
	}
}


void main()
{
#ifdef WINDOWS_TEST
	printf("\n\n ++++++++ Generating all permutations ++++++++\n\n");

	freopen("../test/good_probs/gen_all_permutations_no_order.txt", "r", stdin);
#endif

	generate_all_permute_no_order();
}