#ifndef _LIBMY_H_
#define _LIBMY_H_
#define SIZE 257
#define MAX_LEN_WORD 17
/*
* Funcion checking symbols in order (find '+' - element)
* 
*/
void check_the_line(char *line, int top);

/*
* Funcion checking symbols of string (find '(' - element)
*/
void check_the_number(char *line, int top);

/*
* Funcion checking symbols of string (find ')' - element and 3 digits )
*/
void sep_test(char *line, int i, int top);

/*
* Funcion checking symbols of string (find '-' -element and 3 digits )
*/
void digit_test(char *line, int i, int top);

/*
* Funcion checking symbols of string (find '-' - element and 3 digits)
*/
void digit_test_two(char *line, int i, int top);

/*
* Funcion checking symbols of string (find '-' - element and 3 digits)
*/
void digit_last(char *line, int i, int top);


#endif // _LIBMY_H_
