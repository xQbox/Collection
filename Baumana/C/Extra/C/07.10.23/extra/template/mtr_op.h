#ifndef MTR_OP_H__

#define MTR_OP_H__


#include <stdlib.h>
#include "mtr_errors.h"


int matrix_mul(double **a, size_t a_n, size_t a_m, double **b, size_t b_n, size_t b_m,
								double ***c, size_t *c_n, size_t *c_m);

#endif

