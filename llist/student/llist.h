    typedef int TElem;

    #ifndef _llist_h
    #define _llist_h

    struct Node;
    struct LnkList;
    typedef struct Node *PtrToNode;
    typedef struct LnkList *PtrToList;
    typedef PtrToNode PNode;
    typedef PtrToList LList;    

    LList MakeEmpty( LList L );
    int IsEmpty( LList L );
    int IsLast( PNode P );
    PNode Member( TElem X, LList L );
    void InsertBeg( TElem X, LList L );
    void InsertEnd( TElem X, LList L );
    void InsertPos( TElem X, PNode P, LList L );
    void Delete( TElem X, LList L );
    void RemoveList( LList *L );
    PNode First( LList L );
    LList Head( LList L );
    PNode Next( PNode P );
    TElem Get( PNode P );
    void PrintList( const LList L );

    void FastCat( LList L1, LList L2 );
    LList FreshCat( LList L1, LList L2 );
    LList Cut( LList L, PNode P );
    int ListSize( LList L );

    void MyPrintf(const char *format, ...);
    #endif