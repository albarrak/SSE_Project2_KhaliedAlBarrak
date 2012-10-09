#include "UnionFindTypes.h"

extern int UFCreate (int N, UnionFind *P);
// Universe consists of all positive integers from 1 to N
// Initial partition is: {{1},{2},{3},{4},....,{N}};
// return 0 to indicate error condition
//----------------------------------------------------------------

extern int UFFind (ElementType X, UnionFind *P);
// returns the number of the subset in the UF partition P 
// containing the element X. The subsets are numbered in the
// order they are stored in the UF partition. The numbering
// starts from 0 onwards. If the element does not exist in any
// set, it returns -1

//----------------------------------------------------------------
extern int UFUnion (ElementType X, ElementType Y, UnionFind *P);
// Changes the parition P, such the subsets containing X and Y
// are replaced by the union of these subsets.
// It returns 0 to indicate error condition.
//----------------------------------------------------------------


