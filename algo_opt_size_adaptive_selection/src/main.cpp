
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

int read_input(struct _buf_info *buf_info, FILE *fp_inp_size, FILE *fp_inp_val)
{
	int idx;
	/* Files size for each QP (flattened buffer) */
	int		*inp_size_per_qp;
	/* Error value for each QP (flattened buffer) */
	float	*inp_val_per_qp;

	/* Assign buffer pointers */
	inp_size_per_qp = buf_info->inp_size_per_qp;
	inp_val_per_qp = buf_info->inp_val_per_qp;

	/* read size file */
	idx = 0;
	while (!feof(fp_inp_size))
	{
		if (idx >= (NUM_INP_FILES * NUM_QP_VALUES))
		{
			printf(" Error: Input buffer is not of expected size\n");
			return FAILURE;
		}
		fscanf(fp_inp_size, "%d, ", &inp_size_per_qp[idx]);
		idx++;
	}
	if (idx != (NUM_INP_FILES * NUM_QP_VALUES))
	{
		printf(" Error: Input file is not of expected size\n");
		return FAILURE;
	}

	/* read size file */
	idx = 0;
	while (!feof(fp_inp_val))
	{
		if (idx >= (NUM_INP_FILES * NUM_QP_VALUES))
		{
			printf(" Error: Input buffer is not of expected size\n");
			return FAILURE;
		}
		fscanf(fp_inp_val, "%f, ", &inp_val_per_qp[idx]);
		idx++;
	}
	if (idx != (NUM_INP_FILES * NUM_QP_VALUES))
	{
		printf(" Error: Input is not of expected size\n");
		return FAILURE;
	}

	return SUCCESS;
}

int main(char arg_c, char **arg_v)
{
	FILE *fp_inp_size, *fp_inp_val;
	struct _buf_info buf_info;
	int status;

	if (arg_c < 3)
	{
		printf(" Incorrect input arguments\n");
		printf(" Usage of the solution\n");
		printf("	<.exe> <input size file> <input val file>\n");
		return -1;
	}

	/* Open input size file */
	fp_inp_size = fopen(arg_v[1], "r");
	if (fp_inp_size == NULL)
	{
		printf(" Error: Input file open error\n");
		return -1;
	}
	/* Open input value file */
	fp_inp_val = fopen(arg_v[2], "r");
	if (fp_inp_val == NULL)
	{
		printf(" Error: Input file open error\n");
		fclose(fp_inp_size);
		return -1;
	}

	print_input_config();

	/* create value, parent idx, qp buffers */
	status = create_bufs(&buf_info);
	if (status != SUCCESS)
	{
		printf(" !! Memory allocation failed\n");
		goto END;
	}

	/* Read input files */
	status = read_input(&buf_info, fp_inp_size, fp_inp_val);
	if (status != SUCCESS)
	{
		printf(" !! Input file reading failed\n");
		goto END;
	}

	/* Find optimal solution */
	find_opt_size_adaptive(&buf_info);

END:
	de_init(&buf_info);

	if (fp_inp_size != NULL)
	{
		fclose(fp_inp_size);
	}
	if (fp_inp_val != NULL)
	{
		fclose(fp_inp_val);
	}

	return 0;
}