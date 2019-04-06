
#include <stdio.h>
#include "algo_defines.h"

void print_input_config()
{
	printf("++++++++ Input Configuration Info ++++++++\n");
	printf(" #Input Files			: %d\n", NUM_INP_FILES);
	printf(" #QP Levels			: %d\n", NUM_QP_VALUES);
	printf(" Target File size		: %d Bytes\n", TARGET_FILE_SIZE);
	printf(" QP Start Value			: %d\n", QP_START_VAL);
	printf("\n");
}

int main()
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

	find_opt_size_adaptive(&buf_info);

END:
	de_init(&buf_info);
}