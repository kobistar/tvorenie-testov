#include <stdio.h>
#include <stdlib.h>
#include "tree_arr.h"

extern void PrintRow ( Tree T, int Level ) __attribute__((weak));
extern void PrintSubtree( Tree T, int Index ) __attribute__((weak));


static void not_implemented(const char* func) {
    fprintf(stderr, "Function '%s()' is not yet implemented.\n", func);
}

void PrintRow ( Tree T, int Level ){
    not_implemented(__func__);
    exit(EXIT_FAILURE);
}

void PrintSubtree( Tree T, int Index ){
    not_implemented(__func__);
    exit(EXIT_FAILURE);
}
