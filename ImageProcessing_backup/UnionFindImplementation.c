#include <strings.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "ForestInterface.h"
#include "UnionFindInterface.h"

// The following implementation of UnionFinds uses General Trees

int Equals(ItemType x, ItemType y) ;

//----------------------------------------------------------------

int UFCreate (int N, UnionFind *P)
{
  // Initialize the Forest
  Initialize(N,&P->partition) ;

  // Set all nodes' parents to be -1 (each node is a root)
  int i ;
  for(i=0;i<N;i++)
    {     
      SetParent(-1,i,&P->partition) ;
    }

  return(1) ;
}

//----------------------------------------------------------------

int UFFind (ElementType X, UnionFind *P)
{
  ElementType ToReturn ;
  int flag = GetRoot(X,&ToReturn,(&(P->partition))) ;

  if(flag == 0) 
    {
      return(-1) ;
    }
  else
    {
      return(ToReturn) ;
    }

}

//----------------------------------------------------------------

int UFUnion (ElementType X, ElementType Y, UnionFind *P)
{
  int ix = UFFind(X,P) ;
  int iy = UFFind(Y,P) ;

  // If X and Y are in the UnionFind and not part of the same list...
  if(ix >= 0 && iy >= 0 && ix != iy)
    {

      int sizex = GetSizeTree(ix,(&(P->partition))) ;
      int sizey = GetSizeTree(iy,(&(P->partition))) ;

      if(sizex > sizey)
	{
	  SetParent(ix,iy,(&(P->partition))) ;
	}
      else
	{
	  SetParent(iy,ix,(&(P->partition))) ;
	}
      return(1) ;
    }
  return(0) ;
}

//----------------------------------------------------------------

int Equals(ItemType x, ItemType y)
{
  // Written assuming ItemTypes are integers. Would need to be 
  // rewritten for different ItemTypes. Search requires this
  // function.
  if(x==y)
    {
      return(1) ;
    }
  else
    {
      return(0) ;
    }
}








