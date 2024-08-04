#include "libmy.h"

int16_t sum(stack_t &stack, stackint_t &stackint)
{
    char action = get_stackdata(&stack);
    
    if (action == '0')
        return 1;
    pop(&stack);
    int64_t summ = get_stackintdata(&stackint);
    if (summ == -1)
        return 1;
    popint(&stackint);
    int64_t addend =  get_stackintdata(&stackint);
    if (addend == -1)
        return 1;
    popint(&stackint);
    if (action == '*')
    {
        // printf("%ld\n", summ *addend);
        pushint(&stackint, (summ * addend));
        
        // print_stackint(&stackint);
        return 0;
    }
    else if (action == '/')
    {
        pushint(&stackint, (summ / addend));
        // print_stackint(&stackint);
    
        return 0;
    }
    else if (action == '-')
    {
        pushint(&stackint, (summ - addend));
        // print_stackint(&stackint);
    
        return 0;
    }
    else if (action == '+')
    {
        pushint(&stackint, (summ + addend));
        // print_stackint(&stackint);
    
        return 0;
    }
    else 
    {
        std:: cout << "Unknown command\n";
        return 1;
    }

} 

int64_t char_to_string(const char *start, const char *end)
{
    int64_t result = 0;
    int64_t dif = end - start; 
    for (size_t i = 0; start + i != end; ++i)
    {
        int64_t tmp = 1;
        for (size_t k = 0; k < dif - i - 1; ++k)
        {
            tmp *= 10;   
        } 
        result += ((*(start + i) - '0') * tmp);
    }
    return result;
}

int parse_string(std::string &str)
{
    stack_t *stack = NULL;
    stackint_t *stackint = NULL;
    size_t start = str.size();
    bool flag =  false;

    for (int64_t i = str.size(); i >= 0; --i)
    {
        if (str[i] == '/' || str[i] == '*' || str[i] == '+' || str[i] == '-')
        {
            
            stackint = pushint(stackint, char_to_string(&str[i+1], &str[start]));
            
            if (flag == true)
            {
                sum(*stack, *stackint);
                flag = false;
            }
            
            stack = push(stack, str[i]);
            start = i;
            
            if (str[i] == '*' || str[i] == '/')
                flag = true;
        }
    }
    stackint = pushint(stackint, char_to_string(&str[0], &str[start]));
    
    while (sum(*stack, *stackint) != 1);
    print_stackint(stackint);

    return 0;
}