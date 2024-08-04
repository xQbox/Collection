#include "libmy.h"

int **matrix_alloc(size_t row, size_t col)
{
	int **tmp = calloc(row, sizeof(int *));
	if (!tmp)
		return NULL;
	for (size_t i = 0; i < row; ++i)
	{
		tmp[i] = calloc(col, sizeof(int));
		if (!tmp[i])
		{
			printf("Ошибка выделения памяти\n");
			matrix_free(tmp, row);
			return NULL;
		}
	}
	return tmp;
}

void matrix_free(int **ptr, size_t size)
{
	for (size_t i = 0; i < size; ++i)
	{
		free(ptr[i]);
	}
	free(ptr);
}

