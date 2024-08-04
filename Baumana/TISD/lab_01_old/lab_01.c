#include "libmy.h"

int main(void) 
{
    int rc;
    char M[ARR_LEN - 9];
    int mantissa_arr[ARR_LEN];
    int input_number_arr[ARR_LEN];
    struct long_number_t mantissa;
    size_t man_arr_len, number_arr_len;
    printf(">+---------1---------2---------3---------4---------5");
    rc = struct_input(&mantissa);
    if (rc == ERR_OK)
        rc = number_input(M);
    else
        return rc;

    from_char_to_int(mantissa.mantissa, strlen(mantissa.mantissa), mantissa_arr, &man_arr_len);
    from_char_to_int(M, strlen(M), input_number_arr, &number_arr_len);
    
    printf("strlen(mantissa)->%ld, strlen(M) -> %ld\n", strlen(mantissa.mantissa), strlen(M));
    multiply(mantissa_arr, (strlen(mantissa.mantissa) - 1), input_number_arr, (strlen(M) - 1));
    return rc;
}