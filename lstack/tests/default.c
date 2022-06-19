#include <stdio.h>
#include <stdlib.h>
#include "lstack.h"

extern TElem Top( LStack S ) __attribute__((weak));
extern void Pop( LStack S ) __attribute__((weak));
extern TElem TopAndPop(LStack S) __attribute__((weak));

static void not_implemented(const char* func) {
    fprintf(stderr, "Function '%s()' is not yet implemented.\n", func);
}

TElem Top( LStack S ){
    not_implemented(__func__);
    exit(EXIT_FAILURE);
}

void Pop( LStack S ){
    not_implemented(__func__);
    exit(EXIT_FAILURE);
}

TElem TopAndPop(LStack S){
    not_implemented(__func__);
    exit(EXIT_FAILURE);
}