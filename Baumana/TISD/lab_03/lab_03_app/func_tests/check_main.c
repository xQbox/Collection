#include "libmy.h"
int main(void)
{
	// {
	// 	size_t row , col, index = 0, index_c = 0, index_p = 1;
	// 	int rc = ERR_OK;
	// 	if ((rc = matrix_size_input(&row, &col)) != ERR_OK)
	// 		return rc;
	// 	printf("\n%ld||%ld\n", row , col);
	// 	int **matrix = matrix_alloc(row, col);
	// 	int *ptrv = malloc(30 * sizeof(int));
	// 	int *ptr_c = malloc(30 * sizeof(int));
	// 	size_t percent;
	// 	if (row + col <= 10)
	// 	{
	// 		rc  = matrix_five_input(matrix, row, col, ptrv, &index, ptr_c, &index_c);
	// 	}
	// 	else 
	// 	{
	// 		rc = matrix_ten_input(matrix, row, col, ptrv, &index, ptr_c, &index_c);
	// 	}
	// 	int *ptrd = malloc(sizeof(int) * 30);
	// 	ptrd[0] = 0;
	// 	matrix_p_init(matrix, row, col, ptrd, &index_p);
	// 	matrix_print(matrix, row, col);
	// 	printf("\n");
	// 	for(size_t i = 0; i < index; ++i)
	// 	{
	// 		printf("%3d", ptrv[i]);
	// 	}
	// 	printf("\nindex-> %ld \n", index);
	// 	for(size_t i = 0; i < index_c; ++i)
	// 	{
	// 		printf("%3d", ptr_c[i]);
	// 	}
	// 	printf("\nindex_c-> %ld,\n", index_c);
	// 	for(size_t i = 0; i < index_p; ++i)
	// 	{
	// 		printf("%3d", ptrd[i]);
	// 	}
	// 	printf("\nindex_p-> %ld,\n", index_p);
	// 	percent_read(&percent);
	// 	size_t res = percent_count(percent, row, col);
	// 	printf("\n Res %ld\n", res);
	// 	int *tmp = pointer_init(ptrd, index_p);
	// 	for(size_t i = 0; i < 3; ++i)
	// 	{
	// 		printf("%3d", tmp[i]);
	// 	}
	// 	free(ptrd);
	// 	matrix_free(matrix);
	// 	free(ptr_c);
	// 	free(ptrv);
	// 	free(tmp);
	// }
	// {
	// 	int rc = ERR_OK;
	// 	size_t row, col, index = 0, index_c = 0;
	// 	fscanf(stdin, "%lu%lu", &row, &col);
	// 	int **matrix = NULL;
	// 	matrix = matrix_alloc(row, col);
	// 	int *ptrd = malloc(30 * sizeof(int));
	// 	int *ptr_c = malloc(30 * sizeof(int));
	// 	rc = matrix_ten_input(matrix, row, col, ptrd, &index, ptr_c, &index_c);
	// 	matrix_print(matrix, row, col);
	// 	for(size_t i = 0; i < index; ++i)
	// 	{
	// 		printf("%d", ptrd[i]);
	// 	}
	// 	printf("\nindex ->%ld\n", index);
	// 	matrix_free(matrix);
	// 	free(ptrd);
	// 	free(ptr_c);
	// 	return rc;
	// }
	// {
	// 	size_t size = 10;
	// 	int *tmp = malloc(size * sizeof(int));
	// 	tmp[0] = 2;
	// 	tmp[1] = 3;
	// 	tmp[2] = 1;
	// 	tmp[3] = 4;
	// 	int *a = pointer_init(tmp, 4, 10); 
	// 	printf("start-> main array\n");
	// 	for (size_t i = 0; i < 4; ++i)
	// 	{
	// 		printf("%3d", tmp[i]);
	// 	}
	// 	printf("\nstart-> pointer array\n");
	// 	for (size_t i = 0; i < size; ++i)
	// 	{
	// 		printf("%3d", a[i]);
	// 	}
	// 	free(tmp);
	// 	free(a);
	// }
	// {
	// 	// size_t col = 9;
	// 	size_t row = 5;
	// 	int A[16] = {1,2,3,1,4,1,1,1,1,3,2,1,1,1,1,2};
	// 	int JA[16] = {1,3,4,7,9,2,4,6,8,1,2,6,7,8,9,1};
	// 	int IA[6] = {0,5,9,12,15,16};
	// 	int B[4] = {1,1,1,1};
	// 	// int JB[4] = {1,4,6,7};
	// 	int IB[9] = {1,0,0,2,0,3,4,0,0};
	// 	int *m = multiply_matrix_and_column_vector(A, JA, IA, row, 16, B, IB);
	// 	free(m);
	// }	
}
