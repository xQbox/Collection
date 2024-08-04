#ifndef LAB_07_BASIC_H_
#define LAB_07_BASIC_H_

void buble_sort(int *arr, int n);

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);

void show_err_message(int rc);

// block of new array
int funcion(const int *ptrs, const int *ptrend, size_t *size);


// block of sorting funcion
int comp(const void *left, const void *right);

void swap(void *left, void *right, size_t elem_size);

void mysort(void *data, size_t num, size_t elem_size, int(*comp) (const void *, const void *));



#endif // LAB_07_BASIC_H_