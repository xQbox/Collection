#include "libmy.h"

int main(int argc, char**argv)
{
    int rc = ERR_OK; 
    
    if ((argc != 3) && (argc != 4))
        return ERR_ARG_BAD;
    size_t size = 0;
    int *ptrs = NULL;
    int *ptrs_n = NULL;
    int *ptrend_n = NULL;
    if ((rc = file_check(argv[1], &size)) == ERR_OK)
    {
        
        ptrs = create_array(size);
        if (ptrs)
        {
            
            if ((rc = arr_create(argv[1], ptrs)) == ERR_OK)
            {
                int *pend = ptrs + size;
                print_arr(ptrs, pend);

                if (argc == 3)
                {
                    print_arr(ptrs, pend);
                    mysort(ptrs, size, sizeof(int), comp);
                    print_arr(ptrs, pend);
                    rc = file_write(argv[2], ptrs, pend);
                }
                else
                {
                    if ((strcmp(argv[3], "f")) == 0)
                    {          
                        if ((rc = key(ptrs, pend, &ptrs_n, &ptrend_n)) == ERR_OK)
                        {
                            size_t size_n = ptrend_n - ptrs_n;
                            print_arr(ptrs_n, ptrend_n);
                            mysort(ptrs_n, size_n, sizeof(int), comp);
                            print_arr(ptrs_n, ptrend_n);
                            rc = file_write(argv[2], ptrs_n, ptrend_n);
                        }
                    }
                    else
                        rc = ERR_ARG_BAD;
                } 
            }
            else 
            {

            }
        }
        else
            rc = ERR_MEM;
    }
    clear_array(ptrs_n);
    clear_array(ptrs);
    show_err_message(rc);
    return rc;
}