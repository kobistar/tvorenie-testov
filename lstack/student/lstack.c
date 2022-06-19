#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include "lstack.h"
#include "err.h"

struct Node
{
    PNode	Next;
    TElem	Elem;
};

struct LnkStack
{
    PNode	First;
    PNode	Last;
};

int IsEmptyStack( LStack S )
{
    if(S == NULL) Error("IsEmptyStack: incorrect stack!");
    return S->First == NULL;
}

LStack CreateStack( void )
{
    LStack S;
    S = malloc(sizeof(struct LnkStack));
    if(S == NULL)Error("CreateStack: out of memory!");
    S->First = NULL;
    S->Last = NULL;
    return S;
}

// Removes a stack
// Receives a pointer to LStack, not LStack itself
void RemoveStack( LStack *PS )
{
    if(PS == NULL) Error("RemoveStack: incorrect pointer!");
    if(*PS == NULL) return;
    LStack S = *PS;
    MakeEmptyStack(S);
    free(S);
    *PS = NULL;
}

void MakeEmptyStack( LStack S )
{
    if(S == NULL) Error("MakeEmptyStack: incorrect stack!");
    PNode PTop;
    while(!IsEmptyStack(S)){
        PTop = S->First;
        if(S->First == S->Last) S->Last = NULL;
        S->First = S->First->Next;
        free(PTop);
    }
}

// Inserting element to the beginning of a list
void Push( TElem X, LStack S )
{
    PNode PNew;
    if(S == NULL) Error("Push: incorrect stack!");
    PNew = malloc(sizeof(struct Node));
    if(PNew == NULL) Error("Push: out of memory!");
    PNew->Elem = X;
    PNew->Next = S->First;
    if(IsEmptyStack(S)) S->Last = PNew;
    S->First = PNew;
}

// Prints elements in the tack S
void PrintStack( LStack S )
{
    if(S == NULL) Error("PrintStack: incorrect stack!");
    if(IsEmptyStack(S)) printf("Empty stack");
    else{
        PNode PTmp = S->First;
        printf("Top> ");
        while(PTmp != NULL){
            printf("%d ", PTmp->Elem);
            PTmp = PTmp->Next;
        }
    }
}


void Pop( LStack S ){
    if(S==NULL)Error("Pop: incorrect list!");
    else{
        if(IsEmptyStack(S)) Error("\nPop: empty stack\n");
        else{
            PNode PT = S->First;
                if( S->First == S->Last) S->Last = NULL;
            S->First = S->First->Next;
            free(PT);
        }
    }
}
TElem Top( LStack S )
{   if(S==NULL) Error("Top: incorrect list!");
        
    else{ 
        if(IsEmptyStack(S)) Error("\nTop: empty stack");
        else return S->First->Elem;
    }
    return 0;
}

TElem TopAndPop(LStack S)
{
    if(S==NULL) Error("TopAndPop: incorrect list!");
    else{
        if(IsEmptyStack(S)) Error("\nTopAndPop: empty stack");
        else{
            TElem n=Top(S);
            Pop(S);
            return n;
        }
    }
    return 0;
}
