#include "libmy.h"


int main()
{
    int16_t rc = 0;
    std::string str;
    rc = input_string(str);
    if (rc)
    {
        printf("TOO MANY TRIES\n");
        return ERR_TIMES;
    }
    rc = parse_string(str);

    
    return 0;  
}