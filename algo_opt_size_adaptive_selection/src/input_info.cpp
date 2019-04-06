#include "algo_defines.h"

/* Input info */
/* Files size for each QP (flattened buffer) */
int inp_size_per_qp[NUM_INP_FILES * NUM_QP_VALUES] = {
	10, 20, 30, 10, 20, 30,
};

/* Error value for each QP (flattened buffer) */
float inp_val_per_qp[NUM_INP_FILES * NUM_QP_VALUES] = {
	8, 5, 4, 7, 6, 5,
};