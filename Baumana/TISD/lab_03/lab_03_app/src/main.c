#include "libmy.h"
int main(void)
{
	int rc = ERR_OK;
	
	size_t row = 0, col = 0;
	printf("Программа умножает матрицу на вектор столбец\n\n");
	printf("Введите количество строк в матрице \n");
	if (((rc = number_sec_check(&row, 30000)) != ERR_OK))
	{
		printf("Ошибка ввода размера матрицы(строки)\n");
		return rc;
	}

	if (row == 0)
	{
		printf("Размер не может быть нулевым\n");
		return ERR_ARR_SIZE;
	}
	printf("\n\tКоличество строк в матрице -> %ld\n\n", row);
	
	printf("Введите количество столбцов в матрице \n");
	if (((rc = number_sec_check(&col, 30000)) != ERR_OK) && (col == 0))
	{
		printf("Ошибка ввода размера матрицы(столбцы)\n");
		return rc;
	}
	if (col == 0)
	{
		printf("Размер не может быть нулевым\n");
		return ERR_ARR_SIZE;
	}
	printf("\n\tКоличество столбцов в матрице -> %ld\n\n", col);
	
	size_t spar_percentage;
	if ((rc = percent_read(&spar_percentage, row, col)) != ERR_OK)
	{
		printf("Ошибка ввода процента разреженности\n");
		return rc;
	}
	
	if (spar_percentage == 0)
	{
		printf("Матрица заполнена только 0\n");
		return ERR_IO;
	}

	printf("\nКоличество элементов для насыщения разреженности матрицы -> %ld\n", spar_percentage);
	

	int **matrix = matrix_alloc(row, col);
	if (!matrix)
	{
		printf("Ошибка выделения памяти\n");
		return ERR_MEM;
	}
	

	size_t count_of_values = 0;
	char choose;
	printf("Хотите ввести матрицу самостоятельно?\n\t1 - да\n\tДругое - нет\n>>");
	fscanf(stdin, " %c", &choose);
	scanf("%*[^\n]");
	if (choose == '1')
	{
		if ((row + col) < 14)
		{
			rc = matrix_less_input(matrix, row, col, spar_percentage, &count_of_values);
			if (rc != ERR_OK)
			{
				printf("Ошибка ввода матрицы\n");
				matrix_free(matrix, row);
				return rc;
			}
		}
		else
		{
			rc = matrix_more_input(matrix, row, col, spar_percentage, &count_of_values);
			if (rc != ERR_OK)
			{
				printf("Ошибка ввода матрицы\n");
				matrix_free(matrix, row);
				return rc;
			}
		}
	}
	else
	{
		random_input(matrix, row, col, spar_percentage, &count_of_values);
	}
	//Вывод матрицы
	if (row < 20 && col < 20)
	{
		for (size_t i = 0; i < row; ++i)
		{
			for (size_t k = 0; k < col; ++k)
			{
				printf("%10d", matrix[i][k]);
			}
			printf("\n");
		}
	}


	int *array_values = malloc(sizeof(int) * count_of_values); 

	if (!array_values)
	{
		printf("Ошибка выделения памяти\n");
		matrix_free(matrix, row);
		return ERR_MEM;
	}

	int *array_position_columns = malloc(sizeof(int) * count_of_values);
	
	if (!array_position_columns)
	{
		printf("Ошибка выделения памяти\n");
		matrix_free(matrix, row);
		free(array_values);
		return ERR_MEM;
	}

	int *array_position_row = calloc((row + 1), sizeof(row));
	
	if (!array_position_row)
	{
		printf("Ошибка выделения памяти\n");
		matrix_free(matrix, row);
		free(array_values);
		free(array_position_columns);
		return ERR_MEM;
	}
	
	structur_init(matrix, row, col, array_values, array_position_columns, array_position_row);
	if (row < 20 && col < 20)
	{
		printf("Массив значений(A):\n");
		array_print(array_values, count_of_values);
		
		printf("Массив позиций столбцов(AJ):\n");
		array_print(array_position_columns, count_of_values);	

		printf("Массив позиций строк(IA):\n");
		array_print(array_position_row, row + 1);
	}
	int *vector = calloc(col, sizeof(int));

	if (!vector)
	{
		printf("Ошибка выделения памяти\n");
		matrix_free(matrix, row);
		free(array_values);
		free(array_position_columns);
		free(array_position_row);
		return ERR_MEM;
	}

	size_t vector_percentage;
	if ((rc = percent_read(&vector_percentage, col, 1)) != ERR_OK)
	{
		printf("Ошибка ввода процента разреженности\n");
		return rc;
	}
	if (vector_percentage == 0)
	{
		printf("--------------------------------------------------------------------------------");
		printf("--------------------------------------------------------------------------------");
		printf("\n ВНИМАНИЕ: Ваш вектор имеет 0 процент разреженности. Результат будет нулевая Матрица\n");
		printf("Желаете продолжить\n\t1 - да\n\tДругое - нет\n>>");
		fscanf(stdin, " %c" , &choose);
		scanf("%*[^\n]");
		if (choose != '1')
		{
			printf("Выход....\n");
			matrix_free(matrix, row);
			free(array_values);
			free(array_position_columns);
			free(array_position_row);
			return ERR_OK;
		}
	}
	printf("\nКоличество элементов для насыщения разреженности вектора -> %ld\n", vector_percentage);
	
	size_t count_vector_elem = 0;
	printf("Хотите заполнить вектор самостоятельное\n\t1 - да\n\tДругое - нет\n>>");
	fscanf(stdin," %c", &choose);
	scanf("%*[^\n]");
	if (choose == 1)
	{	
		if ((rc = vector_input(vector, col, &count_vector_elem, vector_percentage)))
		{
			printf("Ошибка ввода вектора \n");
			matrix_free(matrix, row);
			free(array_values);
			free(array_position_columns);
			free(array_position_row);
			free(vector);
			return rc;
		}
	}
	else 
	{
		random_vector_input(vector, col, &count_vector_elem, vector_percentage);
	}
	/// Вывод вектора
	printf("Вектор имеет вид:\n");
	if (row < 20)
	{
		for (size_t i = 0; i < col; ++i)
		{
			printf("%d\n", vector[i]);
		}
	}
	else if (row >= 20)
		array_print(vector, col);
	// printf("%ld\n", count_vector_elem);
	int *vector_values = calloc(count_vector_elem, sizeof(int));
	if (!vector_values) 
	{
		printf("Ошибка ввода выделения памяти\n");
		matrix_free(matrix, row);
		free(array_values);
		free(array_position_columns);
		free(array_position_row);
		free(vector);
		return ERR_MEM;
	}

	int *vector_pos_col = calloc(count_vector_elem, sizeof(int));
	if (!vector_pos_col) 
	{
		printf("Ошибка ввода выделения памяти\n");
		matrix_free(matrix, row);
		free(array_values);
		free(array_position_columns);
		free(array_position_row);
		free(vector);
		free(vector_values);
		return ERR_MEM;
	}
	
	int *vector_pointer = calloc(col + 1, sizeof(int));
	if (!vector_pointer) 
	{
		printf("Ошибка ввода выделения памяти\n");
		matrix_free(matrix, row);
		free(array_values);
		free(array_position_columns);
		free(array_position_row);
		free(vector);
		free(vector_values);
		free(vector_pos_col);
		return ERR_MEM;
	}

	structur_vector_input(vector, col, vector_values, vector_pos_col, vector_pointer);
	
	// printf("Массив значений вектора\n");
	// array_print(vector_values, count_vector_elem);
	// printf("Массив позиций вектора\n");
	// array_print(vector_pos_col, count_vector_elem);
	// printf("Массив указатeлей на значений вектора\n");
	// array_print(vector_pointer, col);
	
	int *result = calloc(row, sizeof(int));
	if (!result)
	{
		printf("Ошибка ввода выделения памяти\n");
		matrix_free(matrix, row);
		free(array_values);
		free(array_position_columns);
		free(array_position_row);
		free(vector);
		free(vector_values);
		free(vector_pos_col);
		free(vector_pointer);
		return ERR_MEM;
	}

	clock_t start, stop;
	long double rr;
	start = clock();
	// sleep(1);
	result = multiply_matrix_and_column_vector(array_values, array_position_columns, array_position_row, count_of_values, vector_values, vector_pointer, result);
	stop = clock();
	rr = (stop - start) / CLOCKS_PER_SEC;
	printf("Результат за раз умножение (три массива) %Lf \n", rr); 

	int *res = calloc(row, sizeof(int));
	if (!res)
	{
		printf("Ошибка ввода выделения памяти\n");
		matrix_free(matrix, row);
		free(array_values);
		free(array_position_columns);
		free(array_position_row);
		free(vector);
		free(vector_values);
		free(vector_pos_col);
		free(vector_pointer);
		free(result);
		return ERR_MEM;
	}

	clock_t start_a, stop_a;
	long double rr_a;
	start_a = clock();
	// sleep(1); 
	res = multiply_matrix(matrix, row, col, vector, res);
	stop_a = clock();
	rr_a = (stop_a - start_a) / CLOCKS_PER_SEC;
	printf("Результат за раз стандартное умножение %Lf \n", rr_a);
	
	// Вывод результатов
	printf("Вектор - столбец (умножение по векторам) ->\n");
	array_print(result, row);
	printf("\n");
	printf("Вектор - столбец (стандартное умножение)->\n");
	array_print(res, row);
	printf("\n");


	clock_t time_a, time_a_end, time_a_fir, time_a_end_fir;
    long double time_a_fin = 0, time_a_fin_fir = 0; 
	int k = 0;
	
	while (k < 100)
	{
		time_a_fir = clock();
		multiply_matrix_and_column_vector(array_values, array_position_columns, array_position_row, count_of_values, vector_values, vector_pointer, result);
		time_a_end_fir = clock();
		time_a_fin_fir += (long double) (time_a_end_fir - time_a_fir) / CLOCKS_PER_SEC;
		k++;
	}
	time_a_fin_fir /= 99;
	k = 0;	
	while (k < 100)
	{
		time_a = clock();
		multiply_matrix(matrix, row, col, vector, res);
		time_a_end = clock();
		time_a_fin += (long double) (time_a_end - time_a) / CLOCKS_PER_SEC;
		k++;
	}
	time_a_fin /= 99;

	matrix_free(matrix, row);
	free(array_values);
	free(array_position_columns);
	free(array_position_row);
	free(vector);
	free(vector_values);
	free(vector_pos_col);
	free(vector_pointer);
	free(result);
	free(res);
	printf("Значение умножение по векторам \n\t>>%Lf\nЗначение стандартным способом\n\t>>%Lf\n", time_a_fin_fir, time_a_fin);

	return rc;
}
