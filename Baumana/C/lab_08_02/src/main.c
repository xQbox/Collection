#include "libmy.h"

int main(void)
{
    int rc = ERR_OK;
    size_t a_row, a_col, b_row, b_col, expected_size_a, expected_size_b, exp_size_social, a_p, b_y;
    int **matrix_b = NULL;
    int **matrix_a = NULL;
    if ((((rc = number_check(&a_row)) == ERR_OK) && (rc = number_check(&a_col)) == ERR_OK))
    {
        if ((matrix_a = matrix_input(a_row, a_col)) != NULL) 
        {
            if ((rc = matrix_data(matrix_a, a_row, a_col)) == ERR_OK)
            {     
                if (((rc = number_check(&b_row)) == ERR_OK) && ((rc = number_check(&b_col)) == ERR_OK))
                {
                    if (((matrix_b = matrix_input(b_row, b_col)) != NULL))
                    {
                        if (((rc = matrix_data(matrix_b, b_row, b_col)) == ERR_OK))
                        {
                            expected_size_a = MIN(a_row, a_col);
                                // matrix_print(matrix_a, a_row, a_col);
                                // matrix_print(matrix_b, b_row, b_col);
                            if ((matrix_a = matrix_resize(matrix_a, &a_row, &a_col, expected_size_a)) != NULL)
                            {
                                expected_size_b = MIN(b_row, b_col);
                                if ((matrix_b = matrix_resize(matrix_b, &b_row, &b_col, expected_size_b)) != NULL)
                                {
                                    exp_size_social = MAX(expected_size_a, expected_size_b);    
                                    // printf("\n%ld\n", exp_size_social);
                                    // matrix_print(matrix_a, a_row, a_col);
                                    // matrix_print(matrix_b, b_row, b_col);
                                    if (exp_size_social == expected_size_a)
                                    {
                                        if ((matrix_b = matrix_add(matrix_b, &b_row, &b_col, exp_size_social)) == NULL)
                                        {
                                            matrix_free(matrix_b, b_row);
                                            matrix_free(matrix_a, a_row);
                                            rc = ERR_STAGEELEVEN;
                                        }
                                    }
                                    else
                                    {
                                        if ((matrix_a = matrix_add(matrix_a, &a_row, &a_col, exp_size_social)) == NULL)
                                        {
                                            matrix_free(matrix_b, b_row);
                                            matrix_free(matrix_a, a_row);
                                            rc = ERR_STAGETEN;
                                        }
                                    }
                                    if ((matrix_a != NULL) && (matrix_b != NULL))
                                    {
                                        // matrix_print(matrix_a, a_row, a_col);
                                        // matrix_print(matrix_b, b_row, b_col);
                                        if (((rc = input_size(&a_p)) == ERR_OK) && ((rc = input_size(&b_y)) == ERR_OK))
                                        {
                                            int **tmp_a = NULL;
                                            int **tmp_b = NULL;
                                            if ((tmp_a = create_matrix(matrix_a, exp_size_social)) != NULL)
                                            {   
                                                if ((tmp_b = create_matrix(matrix_b, exp_size_social)) != NULL)
                                                {    
                                                    if (((matrix_a = multiply(matrix_a, tmp_a, exp_size_social, a_p)) != NULL) && ((matrix_b = multiply(matrix_b, tmp_b, exp_size_social, b_y)) != NULL))
                                                    {
                                                        // matrix_print(matrix_a, a_row, a_col);
                                                        // matrix_print(matrix_b, b_row, b_col);
                                                        int **res = NULL;
                                                        if ((res = matrix_multi(matrix_a, matrix_b, exp_size_social)) != NULL)
                                                        {
                                                            matrix_print(res, exp_size_social, exp_size_social);                                                    
                                                            matrix_free(matrix_b, b_row);
                                                            matrix_free(tmp_a, a_row);
                                                            matrix_free(tmp_b, b_row);
                                                            matrix_free(res, exp_size_social);
                                                        }
                                                        else 
                                                        {
                                                            matrix_free(tmp_a, a_row);
                                                            matrix_free(tmp_b, b_row);
                                                            matrix_free(matrix_b, b_row);
                                                            matrix_free(matrix_a, a_row);
                                                            rc = ERR_STAGENINE;
                                                        }
                                                    }
                                                    else 
                                                    {
                                                        matrix_free(tmp_a, a_row);
                                                        matrix_free(tmp_b, a_row);
                                                        matrix_free(matrix_b, b_row);
                                                        matrix_free(matrix_a, a_row);
                                                        rc = ERR_STAGEEIGH;
                                                    }
                                                }
                                                else 
                                                {
                                                    matrix_free(matrix_b, b_row);
                                                    matrix_free(matrix_a, a_row);
                                                    matrix_free(tmp_a, a_row);
                                                    rc = ERR_STAGESEVEN;
                                                }
                                            }
                                            else
                                            {
                                                matrix_free(matrix_b, b_row);
                                                matrix_free(matrix_a, a_row);
                                                rc = ERR_STAGESIX;
                                            }
                                        }
                                        else 
                                        {
                                            matrix_free(matrix_b, b_row);
                                            matrix_free(matrix_a, a_row);
                                            rc = ERR_STAGEFI;
                                        }
                                    }
                                }
                                else 
                                {
                                    matrix_free(matrix_b, b_row);
                                    matrix_free(matrix_a, a_row);
                                    rc = ERR_STAGEF;
                                }
                            }
                            else
                            {  
                                matrix_free(matrix_b, b_row);
                                matrix_free(matrix_a, a_row);
                                rc = ERR_STAGETH;
                            }
                        }
                        else 
                        {
                            matrix_free(matrix_b, b_row);
                            matrix_free(matrix_a, a_row);
                            rc = ERR_STAGET;
                        }
                    }
                    else 
                    {
                        matrix_free(matrix_a, a_row);
                        rc = ERR_STAGEO;
                    }
                }
                else 
                {
                    matrix_free(matrix_a, a_row);
                }
            }
            else 
            {
                matrix_free(matrix_a, a_row);
            }
        }
    }

    return rc;    
}