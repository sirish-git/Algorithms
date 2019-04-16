
#include <stdio.h>
#include "algo_defines.h"

void print_input_config()
{
	printf("++++++++ Input Configuration Info ++++++++\n");
	printf(" #Input Files			: %d\n", NUM_INP_FILES);
	printf(" #QP Levels			: %d\n", NUM_QP_VALUES);
	printf(" Target MSE			: %f Bytes\n", TARGET_MSE);
	printf(" Target MS-SSIM			: %f Bytes\n", TARGET_MS_SSIM);
	printf(" Target File size		: %d Bytes\n", TARGET_FILE_SIZE);
	printf(" QP Start Value			: %d\n", QP_START_VAL);
	printf("\n");
}


int main(char arg_c, char **arg_v)
{
	struct _buf_info buf_info;
	int status;

	print_input_config();

	/* create value, parent idx, qp buffers */
	status = create_bufs(&buf_info);
	if (status != SUCCESS)
	{
		printf(" !! Memory allocation failed\n");
		goto END;
	}

	/* Find optimal solution */
	find_opt_size_adaptive(&buf_info);

END:
	de_init(&buf_info);

	return 0;
}