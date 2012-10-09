#include <strings.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "ForestInterface.h"
#include "ForestTypes.h"

int main()
{

  Forest *F = malloc(sizeof(Forest)) ;
  if(F == NULL)
    {
      fprintf(stderr,"Forest not allocated\n") ;
    }

  Initialize(18,F) ;

  SetChild(3,6,F) ;
  SetChild(0,3,F) ;
  SetChild(8,6,F) ;
  SetChild(7,8,F) ;
  SetChild(2,8,F) ;
  SetChild(4,8,F) ;
  SetChild(1,7,F) ;
  SetChild(5,7,F) ;
  
  SetChild(9,11,F) ;
  SetChild(10,9,F) ;
  SetChild(14,9,F) ;
  SetChild(12,14,F) ;
  SetChild(13,14,F) ;

  int i ;
  for(i=0;i<18;i++)
    {
      fprintf(stderr,"%d ",F->Nodes[i]) ;
    }
  fprintf(stderr,"\n") ;

  for(i=0;i<18;i++)
    {
      if(F->Nodes[i] != -2)
	{
	  fprintf(stderr,"Size of subtree %d = %d\n",i,GetSizeTree(i,F)) ;
	}
    }

  int r,flag ;
  for(i=0;i<18;i++)
    {
      flag=GetRoot(i,&r,F) ;
      if(flag)
	{
	  fprintf(stderr,"Root of subtree %d = %d\n",i,r) ;
	}
      else
	{
	  fprintf(stderr,"%d is not a node\n",i) ;
	}
    }
}

