#include <strings.h>
#include <math.h>
#include <stdio.h>
#include "Common.h"
#include "ForestTypes.h"

#ifndef UnionFind_Has_Been_Defined

//uses the Forrest ADT to implement the UnionFind ADT
typedef struct unionfind {
  Forest partition; //
} UnionFind;

#define UnionFind_Has_Been_Defined
#endif

