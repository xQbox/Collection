#include "mtr_alloc.h"
#include "mtr_io.h"


int matrix_read(FILE *f, double **data, size_t n, size_t m)
{
	if (f == NULL)
		return ERR_ARGS;
	for (size_t i = 0; i < n; i++)
	{
		for(size_t k = 0; k < m; k++)
		{
			if ((fscanf(f,"%lf", &data[i][k])) != 1)
				return ERR_IO;
		}
	}
	return ERR_OK;
}


int matrix_create(FILE *f, double ***data, size_t *n, size_t *m)
{
	double **tmp;
	int rc = ERR_OK;
	*data = NULL; /// propose that we cant create the matrix
	if ((fscanf(f, "%zu %zu", n,m)) != 2)
		return ERR_IO;
	if ((*n == 0) || (m == 0))
		return ERR_RANGE;
	tmp = matrix_alloc(*n, *m);
	if (!(tmp))
		return ERR_MEM;
	rc = matrix_read(f, tmp, *n, *m);
	if (rc != ERR_OK)
	{
		matrix_free(tmp, *n);
		return rc;
	}
	*data = tmp;
	return ERR_OK;
}


int matrix_create_ex(const char *fname, double ***data, size_t *n, size_t *m)
{
	FILE *f;
	int rc = ERR_OK;
	if ((f = fopen(fname, "r+")) != NULL)
		return ERR_ARGS;
	rc = matrix_create(f, data, n, m);		
	fclose(f);
	return rc;
}


int matrix_print(double **a, size_t n, size_t m)
{
	printf("MATRIX\n");
	for(size_t i = 0 ; i < n; i++)
	{
		for(size_t k = 0; k < m; k++)
		{
			printf("%.3f ", a[i][k]);
		}
		printf("\n");
	}
	printf("\n");
	return ERR_OK;
}
