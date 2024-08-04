#ifndef _LIBMY_H_
#define _LIBMY_H_
#define SIZE 257
#define MAX_LEN_WORD 17
/*
* Funcion init Array of 2 strings
*/
void ask_stroka(char *line, int N, int M);

/*
* Funcion is checking alphabets symbols in string
* Return 1 - YES ; 
* Return 0 - No ;
*/
int check_smb(char N);

/*
* Funcion check same words in Array
* Return 1 - YES;
* Return 0 - NO;
*/
int check_line(char *exp, char S[SIZE/2][MAX_LEN_WORD], int top);

/*
* Funcion take string and
* Return length of string;
*/
int len(char *line);

#endif // _LIBMY_H_
