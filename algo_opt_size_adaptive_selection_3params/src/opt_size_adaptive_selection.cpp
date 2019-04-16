#include <stdio.h>
#include <malloc.h>
#include "algo_defines.h"


int create_bufs(struct _buf_info *buf_info)
{
	char *ptr;
	long long size, total_size = 0;

	/* Clear buffers */
	buf_info->ping_buf = NULL;
	buf_info->pong_buf = NULL;
	buf_info->parent_id_buf = NULL;
	buf_info->qp_buf = NULL;

	/* Allocate value buffer */
	size = TARGET_FILE_SIZE * sizeof(struct _val_info);
	ptr = (char *)malloc(size);
	if (ptr == NULL)
	{
		return FAILURE;
	}
	total_size += size;
	buf_info->ping_buf = (struct _val_info *)ptr;

	/* Allocate value buffer */
	size = TARGET_FILE_SIZE * sizeof(struct _val_info);
	ptr = (char *)malloc(size);
	if (ptr == NULL)
	{
		return FAILURE;
	}
	total_size += size;
	buf_info->pong_buf = (struct _val_info *)ptr;

	/* Allocate id buffer (all rows) */
	size = (long long)TARGET_FILE_SIZE * NUM_INP_FILES * sizeof(int);
	ptr = (char *)malloc(size);
	if (ptr == NULL)
	{
		return FAILURE;
	}
	total_size += size;
	buf_info->parent_id_buf = (int *)ptr;

	/* Allocate qp buffer (all rows) */
	size = (long long)TARGET_FILE_SIZE * NUM_INP_FILES * sizeof(char);
	ptr = (char *)malloc(size);
	if (ptr == NULL)
	{
		return FAILURE;
	}
	total_size += size;
	buf_info->qp_buf = (char *)ptr;

	printf(" Total memory allocated		: %lld Bytes\n", total_size);

	return SUCCESS;
}

void de_init(struct _buf_info *buf_info)
{
	if (buf_info->ping_buf != NULL)
	{
		free(buf_info->ping_buf);
	}
	if (buf_info->pong_buf != NULL)
	{
		free(buf_info->pong_buf);
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

void init_buf(struct _val_info *ptr, int min_id, int max_id)
{
	int cnt;

	for (cnt = min_id; cnt < max_id; cnt++)
	{
		ptr[cnt].mse = LONG_MAX;
		ptr[cnt].mssim = 0;
	}
}

int find_opt_size_adaptive(struct _buf_info *buf_info)
{
	struct _val_info	*rbufs_val[2];	/* row value buffers */
	struct _val_info	*rbuf_val_curr, *rbuf_val_prev;	/* current, parent row value buffers */
	int		*id_buf_parent, *id_ptr_parent;	/* store parent id info */
	char	*qp_buf_cur, *qp_ptr_cur; /* store current qp info */
	double  parent_mse, parent_mssim;
	double  cur_mse, cur_mssim;
	int		cur_size;
	int		idx_flag;
	int		idx_img, idx_qp, idx_nz_par, file_size;
	int		idx_min_par, idx_max_par;	/* to optimize search range */
	int		idx_min_cur, idx_max_cur;	/* to optimize search range */
	int		idx_inp = 0, idx_inp_cur;
	int		idx, min_size;
	double	min_mse, min_mssim;
	int		flag_bound;

	/* Indexes to optimize search range, clearing */
	idx_min_par = TARGET_FILE_SIZE;
	idx_max_par = 0;

	/* Assign buffers to array for ping-pong indexing */
	idx_flag = 0;
	rbufs_val[0] = buf_info->ping_buf;
	rbufs_val[1] = buf_info->pong_buf;
	/* Assign row buffers */
	rbuf_val_curr = rbufs_val[idx_flag];
	rbuf_val_prev = rbufs_val[idx_flag ^ 1];
	/* Assign buffer pointers */
	id_buf_parent = buf_info->parent_id_buf;
	qp_buf_cur = buf_info->qp_buf;

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
		file_size = size_per_qp[idx_inp];
		/* store mse info */
		rbuf_val_prev[file_size].mse = mse_per_qp[idx_inp];
		/* store mssim info */
		rbuf_val_prev[file_size].mssim = mssim_per_qp[idx_inp];
		/* store qp info */
		qp_ptr_cur[file_size] = QP_START_VAL + idx_qp;

		/* find min, max indexes of updates */
		if (file_size <= idx_min_par)
		{
			idx_min_par = file_size;
		}
		if (file_size >= idx_max_par)
		{
			idx_max_par = file_size;
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
			/* Indexes to optimize search range, clearing */
		idx_min_cur = TARGET_FILE_SIZE;
		idx_max_cur = 0;
		flag_bound = 0;
		for (idx_nz_par = idx_min_par; idx_nz_par <= idx_max_par; idx_nz_par++)
		{
			//can check msssim also, but one is enough
			parent_mse = rbuf_val_prev[idx_nz_par].mse;
			parent_mssim = rbuf_val_prev[idx_nz_par].mssim;
			//if parent is non zero, fill dp table
			if (parent_mse != LONG_MAX)
			{
				idx_inp = idx_inp_cur;
				/* Iterate for all QP ranges */
				for (idx_qp = 0; idx_qp < NUM_QP_VALUES; idx_qp++)
				{
					/* get size index */
					file_size = size_per_qp[idx_inp];
					cur_size = idx_nz_par + file_size;
					/* Check size bounds within target */
					if (cur_size < TARGET_FILE_SIZE)
					{
						flag_bound = 1;
						/* store val info: parent + current */
						cur_mse = parent_mse + mse_per_qp[idx_inp];
						cur_mssim = parent_mssim + mssim_per_qp[idx_inp];
						/* check if running avg new mse/mssim is min/max than existing */
						/* todo: divide mse with cumulative pixel count for accurate results ? */
						if ((cur_mse/ (idx_img + 1)) < (rbuf_val_curr[cur_size].mse/ idx_img) ||
							(cur_mssim/(idx_img + 1)) > (rbuf_val_curr[cur_size].mssim/ idx_img))
						{
							/* store maximum value at this file size */
							rbuf_val_curr[cur_size].mse = cur_mse;
							rbuf_val_curr[cur_size].mssim = cur_mssim;
							/* store current qp info */
							qp_ptr_cur[cur_size] = QP_START_VAL + idx_qp;
							/* store parent id info */
							id_ptr_parent[cur_size] = idx_nz_par;
						}

						/* find min, max indexes of updates */
						if (cur_size <= idx_min_cur)
						{
							idx_min_cur = cur_size;
						}
						if (cur_size >= idx_max_cur)
						{
							idx_max_cur = cur_size;
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
			printf("!! Solution may not exist for given input config\n");
			printf(" Try have range of mse/mssim values for few inputs\n");
			return FAILURE;
		}

		/* update flag for ping pong idex */
		idx_flag = (idx_flag ^ 1);
		/* Assign row buffers */
		rbuf_val_curr = rbufs_val[idx_flag];
		rbuf_val_prev = rbufs_val[idx_flag ^ 1];
		/* Init total value buffer with max, optimize clear with [idx_min, idx_max] */
		init_buf(rbuf_val_curr, idx_min_par, idx_max_par);
		/* Assign cur as parent */
		idx_min_par = idx_min_cur;
		idx_max_par = idx_max_cur;
	}

	/* Find optimal total file size */
	double mse, mssim;
	flag_bound = 0;
	for (idx = 0; idx < TARGET_FILE_SIZE; idx++)
	{
		mse = (rbuf_val_prev[idx].mse / NUM_INP_FILES);
		mssim = (rbuf_val_prev[idx].mssim / NUM_INP_FILES);
		/* Find the first location/size where it meets target avg.mssim and mse */
		if (mssim >= TARGET_MS_SSIM && mse <= TARGET_MSE)
		{
			flag_bound = 1;
			min_size = idx;
			min_mse = mse;
			min_mssim = mssim;
			break;
		}
	}
	/* Check whether it is possible to make a selection in current */
	if (flag_bound == 0)
	{
		printf("\n");
		printf("!! Solution does not exist for given input config\n");
		printf(" Try have range of mse/mssim values for few inputs\n");
		return FAILURE;
	}

	printf("\n");
	printf("++++++++ Output Optimal Solution Info ++++++++\n");
	printf(" Optimal total file size	: %d\n", min_size);
	printf(" Optimal total ms-ssim val	: %f\n", min_mssim);
	printf(" Optimal total mse val		: %f\n", min_mse);
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