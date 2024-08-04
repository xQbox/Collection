#include "io.h"

int main(int argc, char **argv)
{
    size_t lines = 0;
    count_lines_1(argv[1], &lines);
    printf("%ld\n", lines);
}