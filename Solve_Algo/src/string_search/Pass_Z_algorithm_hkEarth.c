#include <stdio.h>
#include <string.h>

#define MAX_SZ		100005

char pat[MAX_SZ * 2]; //*2 for concat size of text + pattern
char txt[MAX_SZ];
int pat_sz, txt_sz;

int z_arr[MAX_SZ], z_cnt;
int max_id[MAX_SZ], max_cnt;

void z_algo(char *str)
{
	int i, j, k, cnt;
	int left, right, len;

	//first element is zero
	z_cnt = 0;
	z_arr[z_cnt] = 0;
	z_cnt++;

	left = right = 0;
	len = 0;
	i = 1;
	j = i;
	while(str[i] != '\0')
	{		
		//check match from start
		cnt = len;
		while (str[j + cnt] != '\0' && str[j + cnt] == str[cnt])
		{
			cnt++;
		}
		//find z-box bounds
		left = j + 1;
		right = j + cnt;
		//update indexes
		i++;
		len = 0;
		j = i; //for next compare

		//update z array
		z_arr[z_cnt] = cnt;
		z_cnt++;
		//save full pattern match locations
		if (cnt == pat_sz)
		{
			max_id[max_cnt] = (j - (pat_sz + 1)); //subtract pattern size to get right index
			max_cnt++;
		}

		if (cnt == 0)
		{
			//no match
		}
		else
		{
			//use previously computed z array values to reduce search's
			cnt = 1;
			for (k = left; k < right; k++)
			{
				//use z-arr values from the start
				len = z_arr[cnt];
				cnt++;

				//check if length below right bound
				if ((k + len) < right)
				{
					//within right bound, so copy length from start position
					z_arr[z_cnt] = len;
					z_cnt++;

					len = 0; //clear for next comparison
					i++;
					j = i; //for next compare
				}
				else
				{
					//length exceed right bound, so further comparisons are needed
					j = right;
					break;
				}
			}
		}
	}
}

int main()
{
	int t, t_cnt;
	int i, size;

#ifdef WINDOWS_TEST
	scanf("%d", &t);
	for (t_cnt = 1; t_cnt <= t; t_cnt++)
#endif	
	{
		scanf("%s", pat);
		scanf("%s", txt);
		pat_sz = strlen(pat);
		txt_sz = strlen(txt);

		//add special character end of pattern (to limit length of match)
		pat[pat_sz] = '$';
		pat[pat_sz + 1] = '\0';
		//conact txt string end of pat string
		strcat(pat, txt);

		//z algo
		max_cnt = 0;
		z_algo(pat);

		//print total matches
		printf("%d\n", max_cnt);
#if 0
		if (max_cnt == 0)
		{
			//no full match
		}
		else
		{
			for (i = 0; i < max_cnt; i++)
			{
				printf("%d\n", max_id[i]);
			}
		}
#endif
	}

	return 0;
}
