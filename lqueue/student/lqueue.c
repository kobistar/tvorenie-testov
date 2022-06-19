#include "stdio.h"
    #include "lqueue.h"
    #include "err.h"
    #include <stdlib.h>

    struct Node
    {
        PNode	Next;
        TElem	Elem;
    };
    
    struct LnkQueue
    {
        PNode	Front;
        PNode	Rear;
    };

    int IsEmptyQueue( LQueue Q )
    {
        if(Q == NULL) Error("IsEmptyQueue: incorrect queue!");
        return Q->Front == NULL;
    }

    LQueue CreateQueue( void )
    {
        LQueue Q;
        Q = malloc(sizeof(struct LnkQueue));
        if(Q == NULL)Error("CreateQueue: out of memory!");
        Q->Front = NULL;
        Q->Rear = NULL;
        return Q;
    }

    // Removes a queue
    // Receives a pointer to LQueue, not LQueue itself
    void RemoveQueue( LQueue *PQ )
    {
        if(PQ == NULL) Error("RemoveQueue: incorrect pointer!");
        if(*PQ == NULL) return;
        LQueue Q = *PQ;
        MakeEmptyQueue(Q);
        free(Q);
        *PQ = NULL;
    }

    // Removes elements from a queue
    void MakeEmptyQueue( LQueue Q )
    {
        if(Q == NULL) Error("MakeEmptyQueue: incorrect queue!");
        PNode PFirst;
        while(!IsEmptyQueue(Q)){
            PFirst = Q->Front;
            if(Q->Front == Q->Rear) Q->Rear = NULL;         // the only element in queue
            Q->Front = Q->Front->Next;
            free(PFirst);
        }
    }

    // Inserts element to the end of a list
    void Enqueue( TElem X, LQueue Q )
    {
        PNode PNew;
        if(Q == NULL) Error("Enqueue: incorrect queue!");
        PNew = malloc(sizeof(struct Node));
        if(PNew == NULL) Error("Enqueue: out of memory!");
        PNew->Elem = X;
        PNew->Next = NULL;
        if(IsEmptyQueue(Q)) Q->Front = PNew;
        else Q->Rear->Next = PNew;
        Q->Rear = PNew;
    }

    void PrintQueue( LQueue Q )
    {
        if(Q == NULL) Error("PrintQueue: incorrect queue!");
        if(IsEmptyQueue(Q)) printf("Empty queue");
        else{
            PNode PTmp = Q->Front;
            while(PTmp != NULL){
                printf("%d ", PTmp->Elem);
                PTmp = PTmp->Next;
            }
        }
    }

    TElem Front (LQueue Q)
    {
        if(Q == NULL) Error("Front: incorrect queue!");
        else{
            if(!IsEmptyQueue(Q)) return Q->Front->Elem;
            Error("Front: queue empty!");
        }
        return 0;
    }

    void Dequeue(LQueue Q)
    {
    if(Q==NULL)Error("Dequeue: incorrect queue!");
    else{
        if(IsEmptyQueue(Q)) Error("\nDequeue: empty queue");
        else{
            PNode PT = Q->Front;
            if( Q->Front == Q->Rear) Q->Rear = NULL;
            Q->Front = Q->Front->Next;
            free(PT);
        }
    }
    }

    
    TElem FrontAndDequeue( LQueue Q )
    {
    if(Q==NULL)Error("FrontAndDequeue: incorrect queue!");
    else{
        if(IsEmptyQueue(Q)) Error("\nFrontAndDequeue: empty queue");
        else{
        TElem n=Front(Q);
        Dequeue(Q);
        return n;
        }
    }
    return 0;
    }
