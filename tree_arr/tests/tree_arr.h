// typedef int Element;
#include <math.h>
#ifndef _Tree_h
#define _Tree_h

struct TreeRecord;
typedef struct TreeRecord *Tree;

Tree CreateTree( int MaxLevel );
void DisposeTree( Tree T );
void MakeEmpty( Tree T );
void Insert( Tree T, int Index, int Elem );
void PrintTree( Tree T );
void PrintSpaces(int Count);

void PrintRow ( Tree T, int Level );
void PrintSubtree( Tree T, int Index );

void MyPrintf(const char *format, ...);

#endif  /* _Tree_h */
