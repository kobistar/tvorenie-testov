#include <stdio.h>
#include <stdlib.h>
#include "lqueue.h"

extern TElem Front (LQueue Q) __attribute__((weak));
extern void Dequeue(LQueue Q) __attribute__((weak));
extern TElem FrontAndDequeue(LQueue Q)  __attribute__((weak));

static void not_implemented(const char* func){
    fprintf(stderr, "Function '%s()' is not yet implemented.\n", func);
}

TElem Front (LQueue Q){
    not_implemented(__func__);
    exit(EXIT_FAILURE);
}

void Dequeue(LQueue Q){
    not_implemented(__func__);
    exit(EXIT_FAILURE);
}

TElem FrontAndDequeue(LQueue Q){
    not_implemented(__func__);
    exit(EXIT_FAILURE);
}