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
	  SetParent(3,6,F) ;
	  SetParent(6,3,F) ;
	  
    	  printf("Checking Errors if Initializing with value less than zero\n");
return 0;

}
