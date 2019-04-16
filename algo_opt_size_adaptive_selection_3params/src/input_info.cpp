#include "algo_defines.h"

/* Input info */
/* Files size for each QP (flattened buffer) */
int size_per_qp[NUM_INP_FILES * NUM_QP_VALUES] = {
	20, 10, 20, 30,
};

/* Error value for each QP (flattened buffer) */
double mse_per_qp[NUM_INP_FILES * NUM_QP_VALUES] = {
	7.6, 8.3, 7.9, 5.6,
};

/* Error value for each QP (flattened buffer) */
double mssim_per_qp[NUM_INP_FILES * NUM_QP_VALUES] = {
	.9921, .989, .994, .996,
};