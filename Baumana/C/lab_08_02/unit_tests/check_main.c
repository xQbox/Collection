#include <check.h>
#include "./../inc/libmy.h"

#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define MAX(a,b) (((a) > (b)) ? (a) : (b))


// void matrix_free(int **ptr, size_t row)
// {
//     for (size_t i = 0; i < row; ++i)
//     {
//         free(ptr[i]);
//     }
//     free(ptr);
// }


// int **matrix_input(size_t row, size_t col)
// {
//     int **tmp_ptr = NULL;
//     tmp_ptr = calloc(row, sizeof(int *));
//     if (!tmp_ptr)
//         return NULL;
    
//     for (size_t i = 0; i < row; ++i)
//     {
//         tmp_ptr[i] = malloc(col * sizeof(int));
//         if (!tmp_ptr[i])
//         {
//             matrix_free(tmp_ptr, row);
//             return NULL;
//         }
//     }

//     return tmp_ptr;
// }

START_TEST(matrix_input_1_pos)
{
/// Позитивный тест 1 для функции выделения памяти (все цифры отрицательные)
int IDOL [3][3] = {{-1, -2, -3},{-4, -5, -6}, {-7, -8, -9}};
size_t row = 3, col = 3; 
int **ptr = matrix_input(row, col); 
size_t count = -1;
for (size_t i = 0 ; i < row; ++i)
{
    for (size_t l  = 0; l < col; ++l)
    {
        ptr[i][l] = count;
        count -= 1; 
    }
}
int rc = ERR_OK, rc_fin = ERR_OK;
for (size_t i = 0 ; i < row; ++i)
{
    for (size_t l  = 0; l < col; ++l)
    {
       if (ptr[i][l] != IDOL[i][l])
            rc = 1; 
    }
}
matrix_free(ptr, row);
ck_assert_int_eq(rc, rc_fin);
}
END_TEST

/// -----------------------------
/// Proverka colonok

START_TEST(matrix_resize_1)
{
/// Позитивный тест 1 для функции изменения размеров матрицы(уменьшения)
int IDOL [1][1] = {{-5}};
size_t row = 1, col = 5, expected_size;
expected_size = MIN(row, col); 
int **ptr = matrix_input(row, col); 
int first[5] = {-5,-4,-3,-2,-1};
for (size_t i = 0 ; i < row; ++i)
{
    for (size_t l  = 0; l < col; ++l)
    {
        ptr[i][l] = first[l];
    }
}
int **ptra = matrix_resize(ptr, &row, &col, expected_size);
int rc = ERR_OK, rc_fin = ERR_OK;
for (size_t i = 0 ; i < row; ++i)
{
    for (size_t l  = 0; l < col; ++l)
    {
       if (ptra[i][l] != IDOL[i][l])
            rc = 1; 
    }
}
matrix_free(ptra, row);
ck_assert_int_eq(rc, rc_fin);
}
END_TEST


START_TEST(matrix_resize_2)
{
/// Позитивный тест 2 для функции изменения размеров матрицы(уменьшения) 
/// - удаление столбцов. элементы под удаления (1 и 4 и 3)
int IDOL [2][2] = {{3, 1},{3, 2}};
size_t row = 2, col = 5, expected_size;
expected_size = MIN(row, col); 
int **ptr = matrix_input(row, col); 
int first[5] = {2,3,4,7,1};
int second[5] = {7,3,4,7,2};
for (size_t i = 0 ; i < row; ++i)
{
    for (size_t l = 0; l < col; ++l)
    {
        if (i == 0)
        {
            ptr[i][l] = first[l];
        }
        else if (i == 1)
        {
            ptr[i][l] = second[l];
        }
    }
}
int **ptra = matrix_resize(ptr, &row, &col, expected_size);
int rc = ERR_OK, rc_fin = ERR_OK;
for (size_t i = 0 ; i < row; ++i)
{
    for (size_t l  = 0; l < col; ++l)
    {
       if (ptra[i][l] != IDOL[i][l])
            rc = 1; 
    }
}
matrix_free(ptra, row);
ck_assert_int_eq(rc, rc_fin);
}
END_TEST


START_TEST(matrix_resize_3)
{
/// Позитивный тест 1 для функции изменения размеров матрицы(уменьшения)
/// удаление столбцов элементы под удаление 1 и 5 и 3
int IDOL [2][2] = {{3, 1},{3, 2}};
size_t row = 2, col = 5, expected_size;
expected_size = MIN(row, col); 
int **ptr = matrix_input(row, col); 
int first[5] = {2,3,4,1,7};
int second[5] = {7,3,4,2,7};
for (size_t i = 0 ; i < row; ++i)
{
    for (size_t l = 0; l < col; ++l)
    {
        if (i == 0)
        {
            ptr[i][l] = first[l];
        }
        else if (i == 1)
        {
            ptr[i][l] = second[l];
        }
    }
}
int **ptra = matrix_resize(ptr, &row, &col, expected_size);
int rc = ERR_OK, rc_fin = ERR_OK;
for (size_t i = 0 ; i < row; ++i)
{
    for (size_t l  = 0; l < col; ++l)
    {
       if (ptra[i][l] != IDOL[i][l])
            rc = 1; 
    }
}
matrix_free(ptra, row);
ck_assert_int_eq(rc, rc_fin);
}
END_TEST


START_TEST(matrix_resize_4)
{
/// Позитивный тест 1 для функции изменения размеров матрицы(уменьшения)
/// удаление столбцов элементы под удаление 1 и 4 
int IDOL [3][3] = {{3, 4, 3},{3, 4, 3},{3, 4, 3}};
size_t row = 3, col = 5, expected_size;
expected_size = MIN(row, col); 
int **ptr = matrix_input(row, col); 
int first[5] = {2, 3, 4, 1, 3};
int second[5] = {7, 3, 4, 2, 3};
int third[5] = {8, 3, 4, 4, 3};
for (size_t i = 0 ; i < row; ++i)
{
    for (size_t l = 0; l < col; ++l)
    {
        if (i == 0)
        {
            ptr[i][l] = first[l];
        }
        else if (i == 1)
        {
            ptr[i][l] = second[l];
        }
        else if (i == 2)
        {
            ptr[i][l] = third[l];
        }
    }
}
int **ptra = matrix_resize(ptr, &row, &col, expected_size);
int rc = ERR_OK, rc_fin = ERR_OK;
for (size_t i = 0 ; i < row; ++i)
{
    for (size_t l  = 0; l < col; ++l)
    {
       if (ptra[i][l] != IDOL[i][l])
            rc = 1; 
    }
}
matrix_free(ptra, row);
ck_assert_int_eq(rc, rc_fin);
}
END_TEST

START_TEST(matrix_resize_5)
{
/// Позитивный тест 1 для функции изменения размеров матрицы(уменьшения)
/// удаление строк элементы под удаление 1 и 4 
int IDOL [2][2] = {{2, 3},{3, 3}};
size_t row = 4, col = 2, expected_size;
expected_size = MIN(row, col); 
int **ptr = matrix_input(row, col); 
int first[2] = {2, 3};
int second[2] = {3, 3};
int third[2] = {8, 3};
int forth[2] = {2, 3};
int fifth[2] = {7, 3};

for (size_t i = 0 ; i < row; ++i)
{
    for (size_t l = 0; l < col; ++l)
    {
        if (i == 0)
        {
            ptr[i][l] = first[l];
        }
        else if (i == 1)
        {
            ptr[i][l] = second[l];
        }
        else if (i == 2)
        {
            ptr[i][l] = third[l];
        }
        else if (i == 3)
        {
            ptr[i][l] = forth[l];
        }
        else if (i == 4)
        {
            ptr[i][l] = fifth[l];
        }
    }
}
int **ptra = matrix_resize(ptr, &row, &col, expected_size);
int rc = ERR_OK, rc_fin = ERR_OK;
for (size_t i = 0 ; i < row; ++i)
{
    for (size_t l  = 0; l < col; ++l)
    {
       if (ptra[i][l] != IDOL[i][l])
            rc = 1; 
    }
}
matrix_free(ptra, row);
ck_assert_int_eq(rc, rc_fin);
}
END_TEST

START_TEST(matrix_resize_6)
{
/// Позитивный тест 1 для функции изменения размеров матрицы(уменьшения)
/// удаление строк элементы под удаление 1 и 4 
int IDOL [2][2] = {{2, 3},{3, 3}};
size_t row = 4, col = 2, expected_size;
expected_size = MIN(row, col); 
int **ptr = matrix_input(row, col); 
int first[2] = {2, 3};
int second[2] = {3, 3};
int third[2] = {8, 3};
int forth[2] = {2, 3};
int fifth[2] = {7, 3};

for (size_t i = 0 ; i < row; ++i)
{
    for (size_t l = 0; l < col; ++l)
    {
        if (i == 0)
        {
            ptr[i][l] = first[l];
        }
        else if (i == 1)
        {
            ptr[i][l] = second[l];
        }
        else if (i == 2)
        {
            ptr[i][l] = third[l];
        }
        else if (i == 3)
        {
            ptr[i][l] = forth[l];
        }
        else if (i == 4)
        {
            ptr[i][l] = fifth[l];
        }
    }
}
int **ptra = matrix_resize(ptr, &row, &col, expected_size);
int rc = ERR_OK, rc_fin = ERR_OK;
for (size_t i = 0 ; i < row; ++i)
{
    for (size_t l  = 0; l < col; ++l)
    {
       if (ptra[i][l] != IDOL[i][l])
            rc = 1; 
    }
}
matrix_free(ptra, row);
ck_assert_int_eq(rc, rc_fin);
}
END_TEST

START_TEST(matrix_resize_7)
{
/// Позитивный тест 1 для функции изменения размеров матрицы(уменьшения)
/// удаление строк элементы под удаление 1 и 4 
int IDOL [2][2] = {{1, 2}, {3, 3}};
size_t row = 5, col = 2, expected_size;
expected_size = MIN(row, col); 
int **ptr = matrix_input(row, col); 
int first[2] = {1, 2};
int second[2] = {4, 3};
int third[2] = {7, 3};
int forth[2] = {3, 3};
int fifth[2] = {7, 3};

for (size_t i = 0 ; i < row; ++i)
{
    for (size_t l = 0; l < col; ++l)
    {
        if (i == 0)
        {
            ptr[i][l] = first[l];
        }
        else if (i == 1)
        {
            ptr[i][l] = second[l];
        }
        else if (i == 2)
        {
            ptr[i][l] = third[l];
        }
        else if (i == 3)
        {
            ptr[i][l] = forth[l];
        }
        else if (i == 4)
        {
            ptr[i][l] = fifth[l];
        }
    }
}
int **ptra = matrix_resize(ptr, &row, &col, expected_size);
int rc = ERR_OK, rc_fin = ERR_OK;
for (size_t i = 0 ; i < row; ++i)
{
    for (size_t l  = 0; l < col; ++l)
    {
       if (ptra[i][l] != IDOL[i][l])
            rc = 1; 
    }
}
matrix_free(ptra, row);
ck_assert_int_eq(rc, rc_fin);
}
END_TEST

START_TEST(matrix_resize_8)
{
/// Позитивный тест 1 для функции изменения размеров матрицы(уменьшения)
/// удаление строк элементы под удаление 1 и 4 
int IDOL [1][1] = {{1}};
size_t row = 5, col = 1, expected_size;
expected_size = MIN(row, col); 
int **ptr = matrix_input(row, col); 
int first[1] = {2};
int second[1] = {4};
int third[1] = {7};
int forth[1] = {3};
int fifth[1] = {1};

for (size_t i = 0 ; i < row; ++i)
{
    for (size_t l = 0; l < col; ++l)
    {
        if (i == 0)
        {
            ptr[i][l] = first[l];
        }
        else if (i == 1)
        {
            ptr[i][l] = second[l];
        }
        else if (i == 2)
        {
            ptr[i][l] = third[l];
        }
        else if (i == 3)
        {
            ptr[i][l] = forth[l];
        }
        else if (i == 4)
        {
            ptr[i][l] = fifth[l];
        }
    }
}
int **ptra = matrix_resize(ptr, &row, &col, expected_size);
int rc = ERR_OK, rc_fin = ERR_OK;
for (size_t i = 0 ; i < row; ++i)
{
    for (size_t l  = 0; l < col; ++l)
    {
       if (ptra[i][l] != IDOL[i][l])
            rc = 1; 
    }
}
matrix_free(ptra, row);
ck_assert_int_eq(rc, rc_fin);
}
END_TEST



START_TEST(matrix_resize_9)
{
/// Позитивный тест 1 для функции изменения размеров матрицы(уменьшения)
/// удаление строк элементы под удаление все кроме последнего
int IDOL [1][1] = {{1}};
size_t row = 5, col = 1, expected_size;
expected_size = MIN(row, col); 
int **ptr = matrix_input(row, col); 
int first[1] = {2};
int second[1] = {4};
int third[1] = {7};
int forth[1] = {3};
int fifth[1] = {1};

for (size_t i = 0 ; i < row; ++i)
{
    for (size_t l = 0; l < col; ++l)
    {
        if (i == 0)
        {
            ptr[i][l] = first[l];
        }
        else if (i == 1)
        {
            ptr[i][l] = second[l];
        }
        else if (i == 2)
        {
            ptr[i][l] = third[l];
        }
        else if (i == 3)
        {
            ptr[i][l] = forth[l];
        }
        else if (i == 4)
        {
            ptr[i][l] = fifth[l];
        }
    }
}
int **ptra = matrix_resize(ptr, &row, &col, expected_size);
int rc = ERR_OK, rc_fin = ERR_OK;
for (size_t i = 0 ; i < row; ++i)
{
    for (size_t l  = 0; l < col; ++l)
    {
       if (ptra[i][l] != IDOL[i][l])
            rc = 1; 
    }
}
matrix_free(ptra, row);
ck_assert_int_eq(rc, rc_fin);
}
END_TEST

///----------------------------------------
///----------------------------------------
///--------------MATRIX_ADD----------------
///----------------------------------------
///----------------------------------------
START_TEST(matrix_add_1)
{
/// Позитивный тест 1 для функции изменения размеров матрицы(увеличения)
/// размер 2 х 2 до 3 х 3
int IDOL [3][3] = {{1,2,1},{3,4,3},{2,3,2}};
size_t row = 2, col = 2, expected_size = 3;
int **ptr = matrix_input(row, col); 
int first[2] = {1,2};
int second[2] = {3,4};
for (size_t i = 0 ; i < row; ++i)
{
    for (size_t l = 0; l < col; ++l)
    {
        if (i == 0)
        {
            ptr[i][l] = first[l];
        }
        else if (i == 1)
        {
            ptr[i][l] = second[l];
        }
    }
}
int **ptra = matrix_add(ptr, &row, &col, expected_size);
int rc = ERR_OK, rc_fin = ERR_OK;
for (size_t i = 0 ; i < row; ++i)
{
    for (size_t l  = 0; l < col; ++l)
    {
       if (ptra[i][l] != IDOL[i][l])
            rc = 1; 
    }
}
matrix_free(ptra, row);
ck_assert_int_eq(rc, rc_fin);
}
END_TEST

START_TEST(matrix_add_2)
{
/// Позитивный тест 2 для функции изменения размеров матрицы(увеличения)
/// размер 1 х 1 до 3 х 3
int IDOL [3][3] = {{1,1,1},{1,1,1},{1,1,1}};
size_t row = 1, col = 1, expected_size = 3;
int **ptr = matrix_input(row, col); 
int first[1] = {1};

for (size_t i = 0 ; i < row; ++i)
{
    for (size_t l = 0; l < col; ++l)
    {
        if (i == 0)
        {
            ptr[i][l] = first[l];
        }
    }
}
int **ptra = matrix_add(ptr, &row, &col, expected_size);
int rc = ERR_OK, rc_fin = ERR_OK;
for (size_t i = 0 ; i < row; ++i)
{
    for (size_t l  = 0; l < col; ++l)
    {
       if (ptra[i][l] != IDOL[i][l])
            rc = 1; 
    }
}
matrix_free(ptra, row);
ck_assert_int_eq(rc, rc_fin);
}
END_TEST

START_TEST(matrix_add_3)
{
/// Позитивный тест 1 для функции изменения размеров матрицы(увеличения)
/// размер 3x3 до 5 х 5
int IDOL [5][5] = {{1,2,3,1,1},{4,5,6,4,4},{7,8,0,0,0},{4,5,3,3,3},{4,5,3,3,3}};
size_t row = 3, col = 3, expected_size = 5;
int **ptr = matrix_input(row, col); 
int first[3] = {1,2,3};
int second[3] = {4,5,6};
int third[3] = {7,8,0};

for (size_t i = 0 ; i < row; ++i)
{
    for (size_t l = 0; l < col; ++l)
    {
        if (i == 0)
        {
            ptr[i][l] = first[l];
        }
        else if (i == 1)
        {
            ptr[i][l] = second[l];
        }
        else if (i == 2)
        {
            ptr[i][l] = third[l];
        }
    }
}
int **ptra = matrix_add(ptr, &row, &col, expected_size);
int rc = ERR_OK, rc_fin = ERR_OK;
for (size_t i = 0 ; i < row; ++i)
{
    for (size_t l  = 0; l < col; ++l)
    {
       if (ptra[i][l] != IDOL[i][l])
            rc = 1; 
    }
}
matrix_free(ptra, row);
ck_assert_int_eq(rc, rc_fin);
}
END_TEST


START_TEST(matrix_add_4)
{
/// Позитивный тест 1 для функции изменения размеров матрицы(увеличения)
/// размер 1x1 до 2 х 2
int IDOL [2][2] = {{1,1}, {1,1}};
size_t row = 1, col = 1, expected_size = 2;
int **ptr = matrix_input(row, col); 
int first[1] = {1};

for (size_t i = 0 ; i < row; ++i)
{
    for (size_t l = 0; l < col; ++l)
    {
        if (i == 0)
        {
            ptr[i][l] = first[l];
        }
    }
}
int **ptra = matrix_add(ptr, &row, &col, expected_size);
int rc = ERR_OK, rc_fin = ERR_OK;
for (size_t i = 0 ; i < row; ++i)
{
    for (size_t l  = 0; l < col; ++l)
    {
       if (ptra[i][l] != IDOL[i][l])
            rc = 1; 
    }
}
matrix_free(ptra, row);
ck_assert_int_eq(rc, rc_fin);
}
END_TEST

/// -------------MATRIX-ONE-------------
/// ------------------------------------
START_TEST(matrix_one_1)
{
/// Позитивный тест 1 для функции изменения размеров матрицы(увеличения)
/// размер 1x1 до 2 х 2
int IDOL [2][2] = {{1,0}, {0,1}};
size_t row = 2;
int **ptra = matrix_one(row);
int rc = ERR_OK, rc_fin = ERR_OK;
for (size_t i = 0 ; i < row; ++i)
{
    for (size_t l  = 0; l < row; ++l)
    {
       if (ptra[i][l] != IDOL[i][l])
            rc = 1; 
    }
}
matrix_free(ptra, row);
ck_assert_int_eq(rc, rc_fin);
}
END_TEST

START_TEST(matrix_one_2)
{
/// Позитивный тест 1 для функции изменения размеров матрицы(увеличения)
/// размер 1x1 до 2 х 2
int IDOL [1][1] = {{1}};
size_t row = 1;
int **ptra = matrix_one(row);
int rc = ERR_OK, rc_fin = ERR_OK;
for (size_t i = 0 ; i < row; ++i)
{
    for (size_t l  = 0; l < row; ++l)
    {
       if (ptra[i][l] != IDOL[i][l])
            rc = 1; 
    }
}
matrix_free(ptra, row);
ck_assert_int_eq(rc, rc_fin);
}
END_TEST


START_TEST(matrix_one_3)
{
/// Позитивный тест 1 для функции изменения размеров матрицы(увеличения)
/// размер 1x1 до 2 х 2
int IDOL [3][3] = {{1,0,0},{0,1,0},{0,0,1}};
size_t row = 3;
int **ptra = matrix_one(row);
int rc = ERR_OK, rc_fin = ERR_OK;
for (size_t i = 0 ; i < row; ++i)
{
    for (size_t l  = 0; l < row; ++l)
    {
       if (ptra[i][l] != IDOL[i][l])
            rc = 1; 
    }
}
matrix_free(ptra, row);
ck_assert_int_eq(rc, rc_fin);
}
END_TEST

//--------------MULTIPLY-------------
//-----------------------------------

START_TEST(matrix_multiply_1)
{
/// Позитивный тест 1 для функции изменения размеров матрицы(увеличения)
/// размер 1x1 до 2 х 2
int IDOL [2][2] = {{8,8}, {8,8}};
size_t row = 2, col = 2, expected_size = 2;
int **ptr = matrix_input(row, col); 
int first[2] = {2,2};
int second[2] = {2,2};

for (size_t i = 0 ; i < row; ++i)
{
    for (size_t l = 0; l < col; ++l)
    {
        if (i == 0)
        {
            ptr[i][l] = first[l];
        }
        else if (i == 1)
        {
            ptr[i][l] = second[l];
        }
    }
}
int **ptrb = matrix_input(row, col); 

for (size_t i = 0 ; i < row; ++i)
{
    for (size_t l = 0; l < col; ++l)
    {
        if (i == 0)
        {
            ptrb[i][l] = first[l];
        }
        else if (i == 1)
        {
            ptrb[i][l] = second[l];
        }
    }
}

int **ptra = multiply(ptr, ptrb, row, expected_size);
int rc = ERR_OK, rc_fin = ERR_OK;
for (size_t i = 0 ; i < row; ++i)
{
    for (size_t l  = 0; l < col; ++l)
    {
       if (ptra[i][l] != IDOL[i][l])
            rc = 1; 
    }
}
matrix_free(ptra, row);
matrix_free(ptrb, row);
ck_assert_int_eq(rc, rc_fin);
}
END_TEST


START_TEST(matrix_multiply_2)
{
/// Позитивный тест 1 для функции изменения размеров матрицы(увеличения)
/// размер 1x1 до 2 х 2
int IDOL [3][3] = {{12,12,12}, {12,12,12}, {12,12,12}};
size_t row = 3, col = 3, expected_size = 2;
int **ptr = matrix_input(row, col); 
int first[3] = {2,2,2};
int second[3] = {2,2,2};
int third[3] = {2,2,2};

for (size_t i = 0 ; i < row; ++i)
{
    for (size_t l = 0; l < col; ++l)
    {
        if (i == 0)
        {
            ptr[i][l] = first[l];
        }
        else if (i == 1)
        {
            ptr[i][l] = second[l];
        }
        else if (i == 2)
        {
            ptr[i][l] = third[l];
        }
    }
}
int **ptrb = matrix_input(row, col); 

for (size_t i = 0 ; i < row; ++i)
{
    for (size_t l = 0; l < col; ++l)
    {
        if (i == 0)
        {
            ptrb[i][l] = first[l];
        }
        else if (i == 1)
        {
            ptrb[i][l] = second[l];
        }
        else if (i == 2)
        {
            ptrb[i][l] = third[l];
        }
    }
}
int **ptra = multiply(ptr, ptrb, row, expected_size);
int rc = ERR_OK, rc_fin = ERR_OK;
for (size_t i = 0 ; i < row; ++i)
{
    for (size_t l  = 0; l < col; ++l)
    {
       if (ptra[i][l] != IDOL[i][l])
            rc = 1; 
    }
}
matrix_free(ptra, row);
matrix_free(ptrb, row);
ck_assert_int_eq(rc, rc_fin);
}
END_TEST


START_TEST(matrix_multiply_3)
{
/// Позитивный тест 1 для функции изменения размеров матрицы(увеличения)
/// размер 1x1 до 2 х 2
int IDOL [4][4] = {{230,292,354,628}, {166,212,258,464}, {150,192,234,423}, {161,202,243,444}};
size_t row = 4, col = 4, expected_size = 3;
int **ptr = matrix_input(row, col); 
int first[4] = {2,2,2,8};
int second[4] = {2,2,2,4};
int third[4] = {2,2,2,3};
int forth[4] = {1,2,3,4};
for (size_t i = 0 ; i < row; ++i)
{
    for (size_t l = 0; l < col; ++l)
    {
        if (i == 0)
        {
            ptr[i][l] = first[l];
        }
        else if (i == 1)
        {
            ptr[i][l] = second[l];
        }
        else if (i == 2)
        {
            ptr[i][l] = third[l];
        }
        else if (i == 3)
        {
            ptr[i][l] = forth[l];
        }
    }
}
int **ptrb = matrix_input(row, col); 
for (size_t i = 0 ; i < row; ++i)
{
    for (size_t l = 0; l < col; ++l)
    {
        if (i == 0)
        {
            ptrb[i][l] = first[l];
        }
        else if (i == 1)
        {
            ptrb[i][l] = second[l];
        }
        else if (i == 2)
        {
            ptrb[i][l] = third[l];
        }
        else if (i == 3)
        {
            ptrb[i][l] = forth[l];
        }
    }
}
int **ptra = multiply(ptr, ptrb, row, expected_size);
int rc = ERR_OK, rc_fin = ERR_OK;
for (size_t i = 0 ; i < row; ++i)
{
    for (size_t l  = 0; l < col; ++l)
    {
       if (ptra[i][l] != IDOL[i][l])
            rc = 1; 
    }
}
matrix_free(ptra, row);
matrix_free(ptrb, row);
ck_assert_int_eq(rc, rc_fin);
}
END_TEST


START_TEST(matrix_multiply_4)
{
/// Позитивный тест 1 для функции изменения размеров матрицы(увеличения)
/// размер 1x1 до 2 х 2
int IDOL [4][4] = {{2,2,2,8}, {2,2,2,4}, {2,2,2,3}, {1,2,3,4}};
size_t row = 4, col = 4, expected_size = 1;
int **ptr = matrix_input(row, col); 
int first[4] = {2,2,2,8};
int second[4] = {2,2,2,4};
int third[4] = {2,2,2,3};
int forth[4] = {1,2,3,4};
for (size_t i = 0 ; i < row; ++i)
{
    for (size_t l = 0; l < col; ++l)
    {
        if (i == 0)
        {
            ptr[i][l] = first[l];
        }
        else if (i == 1)
        {
            ptr[i][l] = second[l];
        }
        else if (i == 2)
        {
            ptr[i][l] = third[l];
        }
        else if (i == 3)
        {
            ptr[i][l] = forth[l];
        }
    }
}
int **ptrb = matrix_input(row, col); 
for (size_t i = 0 ; i < row; ++i)
{
    for (size_t l = 0; l < col; ++l)
    {
        if (i == 0)
        {
            ptrb[i][l] = first[l];
        }
        else if (i == 1)
        {
            ptrb[i][l] = second[l];
        }
        else if (i == 2)
        {
            ptrb[i][l] = third[l];
        }
        else if (i == 3)
        {
            ptrb[i][l] = forth[l];
        }
    }
}
int **ptra = multiply(ptr, ptrb, row, expected_size);
int rc = ERR_OK, rc_fin = ERR_OK;
for (size_t i = 0 ; i < row; ++i)
{
    for (size_t l  = 0; l < col; ++l)
    {
       if (ptra[i][l] != IDOL[i][l])
            rc = 1; 
    }
}
matrix_free(ptra, row);
matrix_free(ptrb, row);
ck_assert_int_eq(rc, rc_fin);
}
END_TEST



START_TEST(matrix_multiply_5)
{
/// Позитивный тест 1 для функции изменения размеров матрицы(увеличения)
/// размер 1x1 до 2 х 2
int IDOL [4][4] = {{1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1}};
size_t row = 4, col = 4, expected_size = 0;
int **ptr = matrix_input(row, col); 
int first[4] = {2,2,2,8};
int second[4] = {2,2,2,4};
int third[4] = {2,2,2,3};
int forth[4] = {1,2,3,4};
for (size_t i = 0 ; i < row; ++i)
{
    for (size_t l = 0; l < col; ++l)
    {
        if (i == 0)
        {
            ptr[i][l] = first[l];
        }
        else if (i == 1)
        {
            ptr[i][l] = second[l];
        }
        else if (i == 2)
        {
            ptr[i][l] = third[l];
        }
        else if (i == 3)
        {
            ptr[i][l] = forth[l];
        }
    }
}
int **ptrb = matrix_input(row, col); 
for (size_t i = 0 ; i < row; ++i)
{
    for (size_t l = 0; l < col; ++l)
    {
        if (i == 0)
        {
            ptrb[i][l] = first[l];
        }
        else if (i == 1)
        {
            ptrb[i][l] = second[l];
        }
        else if (i == 2)
        {
            ptrb[i][l] = third[l];
        }
        else if (i == 3)
        {
            ptrb[i][l] = forth[l];
        }
    }
}
int **ptra = multiply(ptr, ptrb, row, expected_size);
int rc = ERR_OK, rc_fin = ERR_OK;
for (size_t i = 0 ; i < row; ++i)
{
    for (size_t l  = 0; l < col; ++l)
    {
       if (ptra[i][l] != IDOL[i][l])
            rc = 1; 
    }
}
matrix_free(ptra, row);
matrix_free(ptrb, row);
ck_assert_int_eq(rc, rc_fin);
}
END_TEST


int main(void)
{
    Suite *s1 = suite_create("Core");
    TCase *tc1_1 = tcase_create("Core");
    SRunner *sr = srunner_create(s1);
    int nf;

    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, matrix_input_1_pos);
    tcase_add_test(tc1_1, matrix_resize_1);
    tcase_add_test(tc1_1, matrix_resize_2);
    tcase_add_test(tc1_1, matrix_resize_3);
    tcase_add_test(tc1_1, matrix_resize_4);
    tcase_add_test(tc1_1, matrix_resize_5);
    tcase_add_test(tc1_1, matrix_resize_6);
    tcase_add_test(tc1_1, matrix_resize_7);
    tcase_add_test(tc1_1, matrix_resize_8);
    tcase_add_test(tc1_1, matrix_resize_9);
    tcase_add_test(tc1_1, matrix_add_1);
    tcase_add_test(tc1_1, matrix_add_2);
    tcase_add_test(tc1_1, matrix_add_3);
    tcase_add_test(tc1_1, matrix_add_4);
    tcase_add_test(tc1_1, matrix_one_1);
    tcase_add_test(tc1_1, matrix_one_2);
    tcase_add_test(tc1_1, matrix_one_3);
    tcase_add_test(tc1_1,matrix_multiply_1);
    tcase_add_test(tc1_1,matrix_multiply_2);
    tcase_add_test(tc1_1,matrix_multiply_3);
    tcase_add_test(tc1_1,matrix_multiply_4);
    tcase_add_test(tc1_1,matrix_multiply_5);
    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}