#include "mtr_alloc.h"
#include "mtr_io.h"
#include "mtr_op.h"
#include "mtr_errors.h"

int main(int argc, char **argv)
{
	FILE *f;
	size_t a_n, a_m;
	int rc = ERR_OK;
	double **a = NULL;
	if (argc != 2)
	{
		fprintf(stderr, "app.exe file_name\n");
		return ERR_ARGS;
	}
	f = fopen(argv[1], "r+");
	if (f)
	{
		rc = matrix_create(f, &a, &a_n, &a_m);
		if (rc == ERR_OK)
		{
			matrix_print(a, a_n, a_m);
			matrix_free(a, a_n);
		}
		fclose(f);
	}
	else
		rc = ERR_IO;   
	
	
	return rc;
}
