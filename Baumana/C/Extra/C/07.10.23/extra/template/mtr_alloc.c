#include "mtr_alloc.h"

// free memory
void matrix_free(double **data, size_t n)
{
	for (size_t i = 0; i < n; i++)
		free(data[i]);
	free(data);
}


double** matrix_alloc(size_t n, size_t m)
{
	double **ptrs;
	ptrs = malloc(n * sizeof(double *));
	if (!ptrs)
		return NULL;
	for(size_t i = 0 ; i < n; i++)
	{
		ptrs[i] = malloc(m * sizeof(double));
		if(!ptrs[i])
		{
			matrix_free(ptrs, i);
			return NULL;
		}
	}
	return ptrs;
}


int matrix_del_column(double **data, size_t n, size_t *m, size_t j)
{
	return ERR_RANGE;
}


int matrix_del_row(double ***data, size_t *n, size_t m, size_t i)
{
	return ERR_RANGE;
}

