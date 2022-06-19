#include <stdio.h>
#include <stdlib.h>

#define Error(errmsg)       do { \
    FILE* file = fopen("file.txt", "w"); \
    fprintf(file, "\nError - %s\n", errmsg ); \
    fclose(file); \
} while (0)
