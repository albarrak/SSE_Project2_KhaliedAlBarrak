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
	  Initialize(-6,F) ;
	  SetChild(3,6,F) ;
	  SetChild(3,6,F) ; 
    	  printf("Checking Errors if SetChild set twice with same value\n");
return 0;

}
