#include "libmy.h"

int number_check(int *number)
{
	int tmp;
	printf(">>");
	if ((fscanf(stdin, "%d", &tmp)) != 1)
		return ERR_NUM_INPUT; 
	*number = tmp;
	return ERR_OK;
}

int number_sec_check(size_t *number, size_t param)
{
	int tmp;
	printf(">>");
	if ((fscanf(stdin, "%d", &tmp)) != 1)
		return  ERR_NUM_INPUT;
	if (tmp >= 0)
	{
		size_t check = tmp;
		if ((check <= param - 1) )
		{		
			*number = tmp;
			return ERR_OK;
		}
	}
	return ERR_RANGE;
}

int matrix_less_input(int **ptr, size_t row, size_t col, size_t sparse_percantage, size_t *count_of_values)
{
	for (size_t i = 0; i < row; ++i)
	{
		for (size_t k = 0; k < col; ++k)
		{
			if (*count_of_values > sparse_percantage)
			{
				printf("Вы ввели максимальное кол-во[%ld] элементов для заданной разреженности\n", sparse_percantage);
				return ERR_OK;
			}
			printf("Введите элемент [%ld][%ld]: ", i + 1, k + 1);
			if ((number_check(&ptr[i][k])) != ERR_OK)
			{
				printf("Ошибка ввода данных\n");
				return ERR_NUM_INPUT;
			}
			if (ptr[i][k] != 0)
				(*count_of_values)++;
		}
	}
	return ERR_OK;
}


int matrix_more_input(int **ptr, size_t row, size_t col, size_t sparse_percentage, size_t *count_of_values)
{
	char flag;
	size_t tmp_row, tmp_col;
	do 
	{
		printf("Введите адрес строки\n");
		if (number_sec_check(&tmp_row, row))
		{
			printf("Ошибка ввода строки\n");
			return ERR_NUMSEC_INPUT;
		}
		printf("Введите адрес столбца\n");
		if (number_sec_check(&tmp_col, col))
		{
			printf("Ошибка ввода столбца\n");
			return ERR_NUMSEC_INPUT;
		}
		printf("Введите число[%ld][%ld]\n", tmp_row, tmp_col);
		if ((number_check(&ptr[tmp_row][tmp_col])) != ERR_OK)
		{
			printf("Ошибка ввода числа\n");
			return ERR_NUM_INPUT;
		}
		if (ptr[tmp_row][tmp_col] != 0)
			(*count_of_values)++;
		printf("Ввод числа прошел успешно\nВведите:\n\te - для завершения ввода\n\tсимвол - для продолжения\n\t");
		fscanf(stdin, " %c", &flag);
		scanf("%*[^\n]");
	}while ((flag != 'e') && (*count_of_values < sparse_percentage));
	return ERR_OK;
}

void matrix_print(int **ptr, size_t row, size_t col)
{
	for (size_t i = 0; i < row; ++i)
	{
		for (size_t k = 0; k < col; ++k)
		{
			printf("%4d", ptr[i][k]);
		}
		printf("\n");
	}
}

int matrix_size_input(size_t *row, size_t *col)
{
	int r , c;
	printf("Введите количество строк:\n");
	if ((fscanf(stdin, "%d", &r)) != 1)
		return ERR_ARGS;
	if (r < 0)
	{
		return ERR_RANGE;
	}
	*row = r;
	printf("Введите количество столбцов:\n");
	if ((fscanf(stdin, "%d", &c)) != 1)
		return ERR_ARGS;
	if (c < 0)
	{
		return ERR_RANGE;
	}
	*col = c;
	return ERR_OK;
}

void array_print(int *ptr, size_t size)
{
	printf("Массив->\n");
	for (size_t i = 0; i < size; ++i)
	{
		printf("%5d", ptr[i]);
	}
	printf("\n");
}


int vector_input(int *ptr, size_t size, size_t *counter, size_t percentage)
{
	char flag;
	size_t tmp_pos;
	do
	{
		if (*counter > percentage)
		{
			printf("Вы ввели максимальное кол-во[%ld] элементов для заданной разреженности\n", percentage);
			return ERR_OK;
		}
		printf("Введи строку позицию строки\n");
		if (number_sec_check(&tmp_pos, size))
		{
			printf("Ошибка ввод числа\n");
			return ERR_NUMSEC_INPUT;
		}
		printf("Введите [%ld] элемент вектора", tmp_pos + 1);
		if (number_check(&ptr[tmp_pos]))
		{
			printf("Ошибка ввода числа\n");
			return ERR_NUM_INPUT;
		}
		if (ptr[tmp_pos] != 0)
			(*counter)++;
		printf("Ввод числа прошел успешно\nВведите:\n\te - для завершения ввода\n\tсимвол - для продолжения\n\t");
		fscanf(stdin, " %c", &flag);
		scanf("%*[^\n]");
	}while((flag != 'e') && (*counter < percentage));
	return ERR_OK;
}


void structur_vector_input(int *ptr_vector, size_t vector_size, int *vector_values, int *vector_position, int *pointer_vector)
{	
	size_t counter = 0;
	for (size_t i = 0; i < vector_size; ++i)
	{
		if (ptr_vector[i] != 0)
		{
			vector_values[counter] = ptr_vector[i];
			vector_position[counter] = i + 1;
			counter++;
		}
	}

	for (size_t i = 0; i < counter; ++i)
	{
		pointer_vector[vector_position[i] - 1] = i + 1;
	}

}

void random_vector_input(int *ptr, size_t size, size_t *counter, size_t percentage)
{
	while (percentage > *counter)
	{
		int tmp_size = rand() % size;
		if (ptr[tmp_size] == 0)
		{
			int time_s;
			time_s = time(NULL);
			srand(time_s);
			int tmp_value = rand() % 1000; 
		 	// значение выше иcправлено (5 ---> 1000) для замеров
			if (tmp_value != 0)
			{
				ptr[tmp_size] = tmp_value;
				(*counter)++;
			}
		}
	}
}
