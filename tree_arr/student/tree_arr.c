#include "err.h"
#include "tree_arr.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
struct TreeRecord
       {
            int MaxLevel;
            int *Array;
       };

Tree CreateTree( int MaxLevel )
{
       Tree T;

       T = malloc( sizeof( struct TreeRecord ) );
       if( T == NULL ) Error( "Out of space!!!" );
       T->Array = malloc(pow(2,MaxLevel+1)*sizeof(int));
       if(T->Array == NULL) Error( "Out of space!!!" );
       T->MaxLevel = MaxLevel;
       MakeEmpty( T );

       return T;
}

void MakeEmpty( Tree T )
{
      int i;
      if(T == NULL) Error("No tree!");
      for(i = 0; i<pow(2,T->MaxLevel+1);i++)
            T->Array[i] = 0;
}

void Insert( Tree T, int Index, int Elem )
{
      if(T == NULL) Error("No tree!");
      if(Index < 1 || Index > pow(2,T->MaxLevel+1)-1)
               Error("Bad index!");
      else T->Array[Index] = Elem;
}

void DisposeTree( Tree T )
{
      if( T != NULL )
      {
          free( T->Array );
          free( T );
      }
}

void PrintTree( Tree T )
{
     int i, j, k = 1, l, m = 4*pow(2,T->MaxLevel), n;

     if(T == NULL) Error("No tree!");

     for(i = 1; i<=T->MaxLevel+1; i++)
     {
         n = pow(2,i-1);
         for(j=0;j<pow(2,i-1);j++)
             {
                 l = (m-2*n)/n;
                 if(j==0) PrintSpaces(l-(l/2)); else PrintSpaces(l);
                 printf("%02d", T->Array[k++]);
             }
         putchar('\n');
     }
}

void PrintSpaces(int Count)
{
    while(Count-- > 0) putchar(' ');
}

void PrintRow ( Tree T, int Level )
{
    if(T == NULL) Error("PrintRow: No tree!");
    else{

        if(Level < 0 || Level > T->MaxLevel) Error("PrintRow: Invalid level");
        else for(int i = pow(2,Level);i<pow(2,Level+1);i++) printf("%02d ",T->Array[i]);
    }
}

void PrintSubtree( Tree T, int Index )
{
    if(T == NULL) Error("PrintRow: No tree!");
    else{
        if(Index <= 0 || Index > pow(2,T->MaxLevel+1)) Error("PrintRow: Invalid level");
        else{
            int i = Index;
            int level=0;
            while(1>i/pow(2,T->MaxLevel+1))
            {   int j ;
                for(j = i; j < i+(int)pow(2,level);j++)
                
                printf("%02d ",T->Array[j]);
                i=i*2;
                level++;
            }
        }
    }

}
