#include "libmy.h"

int check_line(std::string &input_string)
{
    const char *ptr = input_string.c_str();
    for (size_t i = 0; i < input_string.length(); ++i)
    {
        if (((ptr[i] > '9') || (ptr[i] < '0')) \
            && (ptr[i] != '+') && (ptr[i] != '-')  
            && (ptr[i] != '/') && (ptr[i] != '*') \
            && (ptr[i] != '(') && (ptr[i] != ')') \
            && (ptr[i] != '!') && (ptr[i] != '%') )
        {
            std::cout << "the string must contain only numbers and characters + - * / ! %  \n";
            std::cout << "Try again...\n>>";
            return 1;
        }
    }
    return 0;
}


int input_string(std::string &input_string)
{
    std::string tmp;
    size_t count = 0;
    std::cout << ">>";
    while ((std::getline(std::cin, tmp)) && count < 6)
    {
        if (!(check_line(tmp)))
            break;
    
        count++;    
    }
    if (count == 5)
        return ERR_TIMES;

    input_string = tmp;
    return 0;
}

