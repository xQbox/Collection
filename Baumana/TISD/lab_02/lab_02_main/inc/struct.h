#ifndef STRUCT_H_
#define STRUCT_H_

#include "libmy.h"

// enum lolType {
//     PLAY = 1, DRAMA = 2
// };

struct tale_t
{
    size_t age;
};

struct music_t

{
    char singer[STRING_SIZE];
    char country[STRING_SIZE];
    char music_type[STRING_SIZE];
    size_t age;
    size_t duration;
    
};

union choose_t
{
    struct tale_t tale;
    struct music_t music;  
};

struct data_t
{
    char name[STRING_SIZE];
    char perfomance[STRING_SIZE];
    char price_range[STRING_SIZE];
    char perfomance_type[STRING_SIZE];
    union choose_t choose;
};

struct keys_t
{
    int index;
    char perfomance_type[STRING_SIZE];
    union choose_t choose;
};

#endif // STRUCT_H_