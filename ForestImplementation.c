#include <strings.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "ForestTypes.h"

int Bounds(int node, Forest *F) ;

/*----------------------------------------------------------*/

int Initialize(int size, Forest *F)
{
  // Allocate memory for the nodes of the tree, return error
  // if allocation fails
  F->Nodes = malloc(size*sizeof(int)) ;
  if(F->Nodes == NULL)
    {
      return 0 ;
    }

  // Initialize all nodes to -2 (node does not exist)
  int i ;
  for(i=0;i<size;i++)
    {
      F->Nodes[i]=-2 ;
    }

  // Set the size of the forest
  F->Size = size ;

  return 1 ;
}

/*----------------------------------------------------------*/

int GetRoot(int node, int *root, Forest *F) 
{
  // If the node is in Bounds and in use, then sets the root
  // equal to the root of the node. 
  if(!Bounds(node,F))
    {
      // Out of bounds
      return 0 ;
    }
  if(F->Nodes[node] == -2)
    {
      // Node does not exist
      return 0 ;
    }

  while(F->Nodes[node] != -1)
    {
      node=F->Nodes[node] ;
    }
  *root = node ;
  return 1 ;
}

/*----------------------------------------------------------*/

int SetParent(int parent, int node, Forest *F) 
{
  if(!(Bounds(node,F)))
    {
      // the node needs to be in bounds
      return 0 ;
    }
  if(F->Nodes[parent]==-2) F->Nodes[parent]=-1 ;
  F->Nodes[node] = parent ;
}

/*----------------------------------------------------------*/

int GetSizeTree(int node, Forest *F) 
{
  if(Bounds(node,F))
    {
      int size = 1 ;
      int i ;
      for(i=0;i<F->Size;i++)
	{
	  if(F->Nodes[i] == node)
	    {
	      size += GetSizeTree(i,F) ;
	    }
	}
      return(size) ;
    }
  else
    {
      return(0) ;
    }
}

/*----------------------------------------------------------*/

int SetChild(int child, int node, Forest *F) 
{
  if(!(Bounds(node,F)*Bounds(child,F)))
    {
      // both the child and the node need to be in bounds
      return 0 ;
    }
  
  if(F->Nodes[node]==-2) F->Nodes[node]=-1 ;   
  F->Nodes[child] = node ;
     
}

/*----------------------------------------------------------*/

int Bounds(int node, Forest *F)
{
  if(node < 0 && node >= F->Size)
    {
      // Out of bounds
      return 0 ;
    }
  else
    {
      return 1 ;
    }
}

/*----------------------------------------------------------*/
