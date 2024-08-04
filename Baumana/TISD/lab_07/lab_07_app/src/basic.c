#include "libmy.h"

void buble_sort(void *ptr, size_t amount, size_t size_elem, int (*comp) (const void *left, const void *right))
{
    char *ptrs = ptr;
    char *ptre = size_elem * amount + ptrs;
    size_t k = 0;
    for (char *ptr_s = ptrs; ptr_s < ptre; ptr_s+= size_elem)
    {
        for (char *ptrs_n = ptr_s; ptrs_n < ptre - size_elem -  (size_elem * k); ptrs_n += size_elem)
        {
            if (comp(ptrs_n, ptrs_n+size_elem) > 0)
            {
                swap(ptrs_n, ptrs_n+size_elem, size_elem);
            }
        }
        k++;
    }
}

int comp(const void *left, const void *right)
{
    return (const int *) left - (const int *) right;
}

void swap (void *left, void *right, size_t size_elem)
{
    char tmp;
    char *pl = left;
    char *pr = right;
    for (size_t i = 0; i < size_elem; ++i)
    {
        tmp = *pl;
        *pl = *pr;
        *pr = tmp; 
    }
}

int binar_search(int *arr, size_t k, int value, int *flag)
{
    int search = -1;
    int left = 0;
    int right = k;
    int mid = 0;
    while (left  <= right)
    {
        mid = (left + right) / 2; 
        if (arr[mid] == value)
        {
            search = mid;
            *flag = 1;
            return search;
        }
        if (value > arr[mid])
        {
            left = mid + 1;
        }
        else 
        {
            right = mid - 1;
        }
        
    }
    *flag = 0;
    search = mid - 1;
    return search;
}

void treeprint(tree_t *tree) 
{
  if (tree!=NULL) 
    { //Пока не встретится пустой узел
    printf("%s ", tree->word); //Отображаем корень дерева
   
    treeprint(tree->left); //Рекурсивная функция для левого поддерева
    
    
    treeprint(tree->right); //Рекурсивная функция для правого поддерева
    
  }
}

// void change(char *symbol)
// {
//     if (*symbol == 'А') 
//     {
//         *symbol = 'a';
//     } 
//     else if (*symbol == 'Б')
//     {
//         *symbol = 'б';
//     } 
//     else if (*symbol == 'В') 
//     {
//         *symbol = 'в';
//     }
//     else if (*symbol == 'Г') {

//         *symbol = 'г';
//     }
//     else if (*symbol == 'Д') {

//         *symbol = 'д';

//     }
//     else if (*symbol == 'Е') {

//         *symbol = 'е';

//     }
//     else if (*symbol == 'Ё') {

//         *symbol = 'ё';

//     }
//     else if (*symbol == 'Ж') {

//         *symbol = 'ж';

//     }
//     else if (*symbol == 'З') {

//         *symbol = 'з';

//     }
//     else if (*symbol == 'И') {

//         *symbol = 'и';

//     }
//     else if (*symbol == 'Й') {

//         *symbol = 'й';

//     }
//     else if (*symbol == 'К') {

//         *symbol = 'к';

//     }
//     else if (*symbol == 'Л') {

//         *symbol = 'л';

//     }
//     else if (*symbol == 'М') {

//         *symbol = 'м';

//     }
//     else if (*symbol == 'Н') {

//         *symbol = 'н';

//     }
//     else if (*symbol == 'О') {

//         *symbol = 'о';

//     }
//     else if (*symbol == 'П') {

//         *symbol = 'п';

//     }
//     else if (*symbol == 'Р') {

//         *symbol = 'р';

//     }
//     else if (*symbol == 'С') {

//         *symbol = 'с';

//     }
//     else if (*symbol == 'Т') {

//         *symbol = 'т';

//     }
//     else if (*symbol == 'У') {

//         *symbol = 'у';

//     }
//     else if (*symbol == 'Ф') {

//         *symbol = 'ф';

//     }
//     else if (*symbol == 'Х') {

//         *symbol = 'х';

//     }
//     else if (*symbol == 'Ц') {

//         *symbol = 'ц';

//     }
//     else if (*symbol == 'Ч') {

//         *symbol = 'ч';

//     }
//     else if (*symbol == 'Ш') {

//         *symbol = 'ш';

//     }
//     else if (*symbol == 'Щ') {

//         *symbol = 'щ';

//     }
//     else if (*symbol == 'Ъ') {

//         *symbol = 'ъ';

//     }
//     else if (*symbol == 'Ы') {

//         *symbol = 'ы';

//     }
//     else if (*symbol == 'Ь') {

//         *symbol = 'ь';

//     }
//     else if (*symbol == 'Э') {

//         *symbol = 'э';

//     }
//     else if (*symbol == 'Ю') {

//         *symbol = 'ю';

//     }
//     else if (*symbol == 'Я') 
//     {

//         *symbol = 'я';

//     }
// }
