#ifndef DEBUG
  #define DEBUG fprintf (stderr, "\n Here at line %d in file %s", __LINE__, __FILE__);
#endif

#ifndef Types_Has_Been_Defined

  typedef int ElementType;
  typedef  int  ItemType;  

#define Types_Has_Been_Defined
#endif
