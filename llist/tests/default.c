#include <stdio.h>
#include <stdlib.h>
#include "llist.h"

extern void FastCat(LList L1,LList L2) __attribute__((weak));
extern LList FreshCat(LList L1, LList L2) __attribute__((weak));
extern LList Cut(LList L, PNode P) __attribute__((weak));

static void not_implemented(const char* func) {
    fprintf(stderr, "Function '%s()' is not yet implemented.\n", func);
}

void FastCat(LList L1,LList L2){
    not_implemented(__func__);
    exit(EXIT_FAILURE);
}

LList FreshCat(LList L1, LList L2){
    not_implemented(__func__);
    exit(EXIT_FAILURE);
}

LList Cut(LList L, PNode P){
    not_implemented(__func__);
    exit(EXIT_FAILURE);
}