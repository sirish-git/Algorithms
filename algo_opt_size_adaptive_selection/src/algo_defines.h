#pragma once

/* input info macros */
#define NUM_INP_FILES		3
#define NUM_QP_VALUES		2
#define TARGET_FILE_SIZE	81
#define QP_START_VAL		0

/* Algo Macros */
#define LONG_MAX			1099511627776 /* 2^40 */

/* Error status */
#define	SUCCESS				0
#define FAILURE				-1

/* Structure for buffers */
struct _buf_info
{
	/* Input buffers */
	int		*inp_size_per_qp;
	float	*inp_val_per_qp;

	/* Processing buffers */
	float	*val_buf1;
	float	*val_buf2;
	int		*parent_id_buf;
	char	*qp_buf;
};


/* API headers */
int create_bufs(struct _buf_info *buf_info);
void de_init(struct _buf_info *buf_info);
int find_opt_size_adaptive(struct _buf_info *buf_info);