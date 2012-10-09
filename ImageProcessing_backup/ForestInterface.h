#include "ForestTypes.h"

extern void Initialize(int size, Forest *F) ;
/* Given a Forest Pointer and a size, create the forest. Returns
   a forrest where none of the nodes exist (data is -2). */
extern int GetRoot(int node, int *root, Forest *F) ;
/* Given a node and a Forest, return the value of the root of that
   node in the variablle root. Returns 0 for error. */
extern int SetParent(int parent, int node, Forest *F) ;
/* Sets the parent of a node. Note that if the parent to be set is an
   unused node (i.e. it's data is -2) then the parent becomes a
   root. Returns 0 for error. */
extern int GetSizeTree(int node, Forest *F) ;
/* Returns the size of the subtree beginning with the node
   specified. This count includes the node itself. */
extern int SetChild(int child, int node, Forest *F) ;
/* Functions almost exactly as SetParent, this time setting a node to
   be the child of a particular node. */


