#include <stdio.h>

typedef int (*comparator_t)(const int *l, const int *r);
typedef int (*uni_comparator_t)(const void *, const void *);
void print(const int *pbeg, const int *pend);
void sort_0(int *a, size_t a_len);
int comp_1(const int *l, const int *r);
void sort_1(int *arr, size_t a_len, comparator_t cmp);
void sort_2(int *pbeg, int *pend, comparator_t cmp);
void sort_3(int *pbeg, int *pend, comparator_t cmp);
void sort_4( void * pdata, size_t n_membs, size_t elem_size, uni_comparator_t cmp);
int uni_cmp(const void *l, const void *r)
{
    const int *pl = l;
    const int *pr = r;
    return *pl - *pr;
}
void swap( void *l,  void *r, size_t elem_size);
void swap( void *l,  void *r, size_t elem_size)
{
    char tmp;
    char *pl = l;
    char *pr = r;
    for (size_t i = 0; i < elem_size; i++, pl++, pr++)
    {
        tmp = *pl;
        *pl = *pr;
        *pr = tmp;
    }
}


void sort_4( void *pdata, size_t n_membs, size_t elem_size, uni_comparator_t cmp)
{
    if (n_membs == 0)
        return;
    char *pbeg = pdata;
    char *pend = pbeg + n_membs * elem_size;
    for (char *ptop = pend; ptop > pbeg + elem_size; ptop -= elem_size)
    {
        for (char *pcur = pbeg + elem_size; pcur < ptop; pcur += elem_size)
        {
            if (cmp(pcur-elem_size, pcur) > 0)
            {
                swap(pcur - elem_size, pcur, elem_size);
            }
        }
    } 
}






void sort_3(int *pbeg, int *pend, comparator_t cmp)
{

}



int comp_1(const int *l, const int *r)
{
    return *l - *r;
}

int comp_2(const int *l, const int *r)
{
    return *r - *l;
}

void sort_2(int *pbeg, int *pend, comparator_t cmp)
{
    if (pbeg == pend)
        return;
    for (int *ptop = pend; ptop > pbeg + 1; ptop--)
    {
        for (int *pcur = pbeg + 1; pcur < ptop; pcur++)
        {
            if (cmp(pcur - 1, pcur) > 0)
            {

                int tmp = *(pcur - 1);
                *(pcur - 1) = *pcur;
                *pcur = tmp;
            
            }
        }
    }
}

void sort_1(int *arr, size_t a_len, comparator_t cmp)
{
    if (a_len == 0)
        return;
    for (size_t i = a_len; i > 1; i--)
    {
        for (size_t k = 1; k < i; k++)
        {
            if (cmp(&arr[k - 1], &arr[k]) > 0)
            {
                int tmp = arr[k - 1];
                arr[k - 1] = arr[k];
                arr[k] = tmp;
            }
        }
    }
} 


void print(const int *pbeg, const int *pend)
{
    const int *pcur = pbeg;
    printf("Array:\n");
    while ( pcur < pend )
    {
        printf("%d", *pcur);
        pcur ++;
    }
    printf("\n");
}

void sort_0(int *a, size_t a_len)
{
    if (a_len == 0)
        return;
    for (size_t i = a_len; i > 1; i--)
    {
        for (size_t k = 1; k < i; k++)
        {
            if (a[k - 1] > a[k])
            {
                int tmp = a[k - 1];
                a[k - 1] = a[k];
                a[k] = tmp;
            }
        }
    }
}


int main(void)
{
    // массив из одного элемента
    {
        int a[] = {1};
        size_t a_n = sizeof(a) / sizeof(a[0]);
        // sort_0(a, a_n);
        // sort_1(a, a_n, comp_1);
        sort_2(a, a+a_n, comp_1);
        print(a, a+a_n);
    }

    // массив из двух элементов по убыванию
    {
        int a[] = {2, 1};
        size_t a_n = sizeof(a) / sizeof(a[0]);
        // sort_0(a, a_n);
        // sort_1(a, a_n, comp_2);
        // sort_2(a, a+a_n, comp_2);
        sort_4(a, a_n, sizeof(int) , uni_cmp);
       
        print(a, a+a_n);
    }
    // массив из двух элементов по возрастанию
    {
        int a[] = {1, 2};
        size_t a_n = sizeof(a) / sizeof(a[0]);
        // sort_0(a, a_n);
        // sort_1(a, a_n, comp_1);
        // sort_2(a, a+a_n, comp_2);
         sort_4(a, a_n, sizeof(int) , uni_cmp);
        print(a, a+a_n);
    }
    // упорядоченный по убыванию массив
    {
        int a[] = {5, 4, 3, 2, 1};
        size_t a_n = sizeof(a) / sizeof(a[0]);
        // sort_0(a, a_n);
        // sort_1(a, a_n, comp_1);
        // sort_2(a, a+a_n, comp_2);
         sort_4(a, a_n, sizeof(int) , uni_cmp);
        
        print(a, a+a_n);
    }
    // упорядоченный по возрастанию массив
    {
        int a[] = {1, 2, 3, 4, 5};
        size_t a_n = sizeof(a) / sizeof(a[0]);
        // sort_0(a, a_n);
        //  sort_1(a, a_n, comp_1);
        // sort_2(a, a+a_n, comp_2);
         sort_4(a, a_n, sizeof(int) , uni_cmp);
        
        print(a, a+a_n);
    }
    // случайный массив
    {
        int a[] = {2, 4, 5, 2, 1};
        size_t a_n = sizeof(a) / sizeof(a[0]);
        // sort_0(a, a_n);
        //  sort_1(a, a_n, comp_2);
        // sort_2(a, a+a_n, comp_2);
         sort_4(a, a_n, sizeof(int) , uni_cmp);
        
        print(a, a+a_n);
    }
    // случайный массив с повторяющихся элементами
    {
        int a[] = {5, 3, 3, 2, 4, 1};
        size_t a_n = sizeof(a) / sizeof(a[0]);
        // sort_0(a, a_n, comp_1);
        // sort_1(a , a_n, comp_2);
        sort_2(a, a+a_n, comp_2);
        
        print(a, a+a_n);
    }
    // пустой массив
    {
        int a[] = {1};
        // size_t a_n = sizeof(a) / sizeof(a[0]);
        size_t a_n = 0;
        // sort_1(a, a_n, comp_2);
        sort_2(a, a+a_n, comp_2);
        
        print(a, a+a_n);
    }

    return 0;
}
