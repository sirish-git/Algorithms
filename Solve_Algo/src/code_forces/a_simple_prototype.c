
#include <stdio.h>
#include <string.h>

#define INT_MAX				 99999999
#define INT_MIN				-99999999
#define SUCCESS				0
#define MAX_DIM				20001

static signed long long input[MAX_DIM];
static signed long long N;
static signed long long g_max_scr;


/* Actual algo funciton */
static void core_fn()
{
	signed long long i, j;
	signed long long max;
}

void main()
{
	signed long long i, j;
	
#ifdef WINDOWS_TEST
	while(1) 
	{
#endif
	/* Read Inputs */
	scanf("%I64d", &N);

	/* algo function call */
	core_fn();

	printf("%I64d\n", g_max_scr);
#ifdef WINDOWS_TEST
	}
#endif
}