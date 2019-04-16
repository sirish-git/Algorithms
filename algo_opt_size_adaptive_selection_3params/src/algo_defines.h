#pragma once

/* input info macros */
#define NUM_INP_FILES		2
#define NUM_QP_VALUES		2
#define TARGET_FILE_SIZE	41 /* add +1 */
#define TARGET_MSE			(7.9845f)
#define TARGET_MS_SSIM		(0.9930001f)
#define QP_START_VAL		0

/* Algo Macros */
#define LONG_MAX			1099511627776 /* 2^40 */

/* Error status */
#define	SUCCESS				0
#define FAILURE				-1

struct _val_info
{
	double mse;
	double mssim;
};

/* Structure for buffers */
struct _buf_info
{
	/* Input buffers */
	int		*size_per_qp;
	float	*mse_per_qp;
	float	*mssim_per_qp;

	/* Processing buffers */
	struct _val_info	*ping_buf;
	struct _val_info	*pong_buf;
	int		*parent_id_buf;
	char	*qp_buf;
};


/* API headers */
int create_bufs(struct _buf_info *buf_info);
void de_init(struct _buf_info *buf_info);
int find_opt_size_adaptive(struct _buf_info *buf_info);


/* Input info */
/* Files size for each QP (flattened buffer) */
extern int size_per_qp[NUM_INP_FILES * NUM_QP_VALUES];
/* Error value for each QP (flattened buffer) */
extern double mse_per_qp[NUM_INP_FILES * NUM_QP_VALUES];
/* Error value for each QP (flattened buffer) */
extern double mssim_per_qp[NUM_INP_FILES * NUM_QP_VALUES];