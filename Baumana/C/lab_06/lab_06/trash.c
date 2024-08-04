// #define NAME_LEN 25 
// struct subject
// {
//     char name[NAME_LEN + 1];
//     double mass;
//     double amount;
// };


// int substring_search(char *tag, char *name)
// { 
//     size_t count = 0;
//     for(size_t i = 0; i < strlen(name); ++i)
//     {
//         if(tag[i] != name[i])
//         {
//             count = 0;
//         }
//         count += 1;
//     }
//     if(count != strlen(tag))
//     {
//         return 1;
//     }
//     return 0;
// }



// int read_struct(FILE *fp, char *name, double *mass, double *amount)
// {
//     struct subject temp ;
    
// }

// // Считывание структуры из файла
// int read_struct(FILE *fp, char *name, double *mass, double *amount);



    // Хороший вариант с структурой
    // while((fscanf(fp, "%25s", items[index].name)) == 1)
    // {
    //     if (index > QUANT)
    //         return ERR_STRUCT_OVERFLOW;

    //     if ((fscanf(fp, "%lf", &items[index].mass)) != 1)
    //         return ERR_STR_OVERFLOW;
        
    //     if ((fscanf(fp, "%lf", &items[index].amount)) != 1)
    //         return ERR_NUM_OVERFLOW;
        
    //     index += 1; 
     
    // }

    // Проверка корректного названия файла , недопущение употребления (/)    
    // if ( check_the_par(argv[1]) )
    // {
    //     return ERR_BADPAR ;
    // }