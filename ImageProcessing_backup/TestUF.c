#include <strings.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "UnionFindInterface.h"
#include "UnionFindTypes.h"

void printUF(UnionFind *P) ;

int main()
{
  UnionFind *P = malloc(sizeof(UnionFind)) ;
  UFCreate(10,P) ;
  printUF(P) ;

  UFUnion(1,2,P) ;
  printUF(P) ;
  UFUnion(1,3,P) ;
  printUF(P) ;
  UFUnion(6,7,P) ;
  printUF(P) ;
  UFUnion(6,8,P) ;
  printUF(P) ;
  UFUnion(8,3,P) ;
  printUF(P) ;

}

void printUF(UnionFind *P)
{
  int i ;
  fprintf(stderr,"\n") ;
  for(i=0;i<10;i++)
    {
      if(P->partition.Nodes[i] == -1)
	{
	  fprintf(stderr,"  ",P->partition.Nodes[i]) ;
	}
      else
	{
	  fprintf(stderr,"%d ",P->partition.Nodes[i]) ;
	}
    }
  fprintf(stderr,"\n") ;
  for(i=0;i<10;i++)
    {
      fprintf(stderr,"%d ",i) ;
    }
  fprintf(stderr,"\n") ;

}
