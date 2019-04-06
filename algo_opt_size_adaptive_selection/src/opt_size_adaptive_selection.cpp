#include <stdio.h>
#include <malloc.h>
#include "algo_defines.h"


int create_bufs(struct _buf_info *buf_info)
{
	char *ptr;
	int size, total_size = 0;

	/* Clear buffers */
	buf_info->inp_size_per_qp = NULL;
	buf_info->inp_val_per_qp = NULL;
	buf_info->val_buf1 = NULL;
	buf_info->val_buf2 = NULL;
	buf_info->parent_id_buf = NULL;
	buf_info->qp_buf = NULL;

	/* Allocate input size buffer */
	size = NUM_INP_FILES * NUM_QP_VALUES * sizeof(int);
	ptr = (char *)malloc(size);
	if (ptr == NULL)
	{
		return FAILURE;
	}
	total_size += size;
	buf_info->inp_size_per_qp = (int *)ptr;

	/* Allocate input value buffer */
	size = NUM_INP_FILES * NUM_QP_VALUES * sizeof(float);
	ptr = (char *)malloc(size);
	if (ptr == NULL)
	{
		return FAILURE;
	}
	total_size += size;
	buf_info->inp_val_per_qp = (float *)ptr;

	/* Allocate value buffer */
	size = TARGET_FILE_SIZE * sizeof(float);
	ptr = (char *)malloc(size);
	if (ptr == NULL)
	{
		return FAILURE;
	}
	total_size += size;
	buf_info->val_buf1 = (float *)ptr;	

	/* Allocate value buffer */
	size = TARGET_FILE_SIZE * sizeof(float);
	ptr = (char *)malloc(size);
	if (ptr == NULL)
	{
		return FAILURE;
	}
	total_size += size;
	buf_info->val_buf2 = (float *)ptr;

	/* Allocate id buffer (all rows) */
	size = TARGET_FILE_SIZE * NUM_INP_FILES * sizeof(int);
	ptr = (char *)malloc(size);
	if (ptr == NULL)
	{
		return FAILURE;
	}
	total_size += size;
	buf_info->parent_id_buf = (int *)ptr;

	/* Allocate qp buffer (all rows) */
	size = TARGET_FILE_SIZE * NUM_INP_FILES * sizeof(char);
	ptr = (char *)malloc(size);
	if (ptr == NULL)
	{
		return FAILURE;
	}
	total_size += size;
	buf_info->qp_buf = (char *)ptr;

	printf(" Total memory allocated		: %d Bytes\n", total_size);

	return SUCCESS;
}

void de_init(struct _buf_info *buf_info)
{
	if (buf_info->inp_size_per_qp != NULL)
	{
		free(buf_info->inp_size_per_qp);
	}
	if (buf_info->inp_val_per_qp != NULL)
	{
		free(buf_info->inp_val_per_qp);
	}
	if (buf_info->val_buf1 != NULL)
	{
		free(buf_info->val_buf1);
	}
	if (buf_info->val_buf2 != NULL)
	{
		free(buf_info->val_buf2);
	}
	if (buf_info->parent_id_buf != NULL)
	{
		free(buf_info->parent_id_buf);
	}
	if (buf_info->qp_buf != NULL)
	{
		free(buf_info->qp_buf);
	}
}

void init_buf(float *ptr, int min_id, int max_id)
{
	int cnt;

	for (cnt = min_id; cnt < max_id; cnt++)
	{
		ptr[cnt] = LONG_MAX;
	}
}

int find_opt_size_adaptive(struct _buf_info *buf_info)
{
	/* Files size for each QP (flattened buffer) */
	int		*inp_size_per_qp;
	/* Error value for each QP (flattened buffer) */
	float	*inp_val_per_qp;
	float	*rbufs_val[2];	/* row value buffers */
	float	*rbuf_val_curr, *rbuf_val_prev;	/* current, parent row value buffers */
	int		*id_buf_parent, *id_ptr_parent;	/* store parent id info */
	char	*qp_buf_cur, *qp_ptr_cur; /* store current qp info */
	float	parent_val, cur_val;
	int		cur_size;
	int		idx_flag;
	int		idx_img, idx_qp, idx_nz_par, file_size;
	int		idx_min, idx_max;	/* to optimize search range */
	int		start, end;
	int		idx_inp = 0, idx_inp_cur;
	int		idx, min_size;
	float	min_val;
	int		flag_bound;

	/* Indexes to optimize search range, clearing */
	idx_min = TARGET_FILE_SIZE;
	idx_max = 0;

	/* Assign buffers to array for ping-pong indexing */
	idx_flag = 0;
	rbufs_val[0] = buf_info->val_buf1;
	rbufs_val[1] = buf_info->val_buf2;
	/* Assign buffer pointers */
	inp_size_per_qp = buf_info->inp_size_per_qp;
	inp_val_per_qp = buf_info->inp_val_per_qp;
	id_buf_parent = buf_info->parent_id_buf;
	qp_buf_cur = buf_info->qp_buf;

	/* Assign row buffers */
	rbuf_val_curr = rbufs_val[idx_flag];
	rbuf_val_prev = rbufs_val[idx_flag ^ 1];

	/* Init total value buffer with max */
	init_buf(rbuf_val_curr, 0, TARGET_FILE_SIZE);
	init_buf(rbuf_val_prev, 0, TARGET_FILE_SIZE);

	/* First row: Assign values directly */
	idx_inp = 0;
	idx_img = 0;
	/* row pointers */
	id_ptr_parent = id_buf_parent + idx_img * TARGET_FILE_SIZE;
	qp_ptr_cur = qp_buf_cur + idx_img * TARGET_FILE_SIZE;
	for (idx_qp = 0; idx_qp < NUM_QP_VALUES; idx_qp++)
	{
		/* get size index */
		file_size = inp_size_per_qp[idx_inp];
		/* store val info */
		rbuf_val_prev[file_size] = inp_val_per_qp[idx_inp];
		/* store qp info */
		qp_ptr_cur[file_size] = QP_START_VAL + idx_qp;

		/* find min, max indexes of updates */
		if (file_size <= idx_min)
		{
			idx_min = file_size;
		}
		if (file_size >= idx_max)
		{
			idx_max = file_size;
		}

		idx_inp++;
	}

	idx_inp_cur = idx_inp;
	/* Algorithm to find optimal size using DP */
	/* Iterate for image index (from 1) to find optimal size */
	for (idx_img = 1; idx_img < NUM_INP_FILES; idx_img++)
	{
		/* row pointers */
		id_ptr_parent = id_buf_parent + idx_img * TARGET_FILE_SIZE;
		qp_ptr_cur = qp_buf_cur + idx_img * TARGET_FILE_SIZE;

		/* Find non-zero values in top DP row 
			(Optimal search in [idx_min, idx_max]) */
		/* Assign values to different variables,
			as the min, max indexes gets update inside loop */
		start = idx_min;
		end = idx_max;
		flag_bound = 0;
		for (idx_nz_par = start; idx_nz_par <= end; idx_nz_par++)
		{
			parent_val = rbuf_val_prev[idx_nz_par];
			if (parent_val != LONG_MAX)
			{
				idx_inp = idx_inp_cur;
				/* Iterate for all QP ranges */
				for (idx_qp = 0; idx_qp < NUM_QP_VALUES; idx_qp++)
				{
					/* get size index */
					file_size = inp_size_per_qp[idx_inp];
					cur_size = idx_nz_par + file_size;
					/* Check size bounds within target */
					if (cur_size < TARGET_FILE_SIZE)
					{
						flag_bound = 1;
						/* store val info: parent + current */
						cur_val = parent_val + inp_val_per_qp[idx_inp];
						/* check if new val is min than existing */
						if (cur_val < rbuf_val_curr[cur_size])
						{
							/* store minimum value */
							rbuf_val_curr[cur_size] = cur_val;
							/* store current qp info */
							qp_ptr_cur[cur_size] = QP_START_VAL + idx_qp;
							/* store parent id info */
							id_ptr_parent[cur_size] = idx_nz_par;
						}

						/* find min, max indexes of updates */
						if (cur_size <= idx_min)
						{
							idx_min = cur_size;
						}
						if (cur_size >= idx_max)
						{
							idx_max = cur_size;
						}
					}

					idx_inp++;
				}
			}
		}
		/* update the input index */
		idx_inp_cur += NUM_QP_VALUES;
		/* Check whether it is possible to make a selection in current */
		if (flag_bound == 0)
		{
			printf("\n");
			printf("!! Solution does not exist for given input config\n");
			printf(" Try increasing the target file size or have small sizes for few inputs\n");
			return FAILURE;
		}

		/* update flag for ping pong idex */
		idx_flag = (idx_flag ^ 1);
		/* Assign row buffers */
		rbuf_val_curr = rbufs_val[idx_flag];
		rbuf_val_prev = rbufs_val[idx_flag ^ 1];
		/* Init total value buffer with max, optimize clear with [idx_min, idx_max] */
		init_buf(rbuf_val_curr, idx_min, idx_max);
	}

	/* Find optimal total file size */
	min_size = TARGET_FILE_SIZE;
	min_val = LONG_MAX;
	for (idx = 0; idx < TARGET_FILE_SIZE; idx++)
	{
		if (rbuf_val_prev[idx] < min_val)
		{
			min_val = rbuf_val_prev[idx];
			min_size = idx;
		}
	}

	printf("\n");
	printf("++++++++ Output Optimal Solution Info ++++++++\n");
	printf(" Optimal total file size	: %d\n", min_size);
	printf(" Optimal total min val		: %f\n", min_val);
	printf("\n");

	printf("++++++++ Output Optimal QP Selection Info ++++++++\n");
	/* Back-trace to find QP/size assignment for each image */
	idx_nz_par = min_size;
	for (idx_img = NUM_INP_FILES - 1; idx_img >= 0; idx_img--)
	{
		/* row pointers */
		id_ptr_parent = id_buf_parent + idx_img * TARGET_FILE_SIZE;
		qp_ptr_cur = qp_buf_cur + idx_img * TARGET_FILE_SIZE;

		printf("img id: %d, QP selected: %d\n", idx_img, qp_ptr_cur[idx_nz_par]);

		/* Get parent id */
		idx_nz_par = id_ptr_parent[idx_nz_par];
	}

	return SUCCESS;
}