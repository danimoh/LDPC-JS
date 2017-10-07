/* ALLOC.C - Routine to allocate memory and complain if it doesn't work. */

/* Based on Code by Radford M. Neal, see LICENSE_LDPC. */

#include "alloc.h"


/* ALLOCATE SPACE AND CHECK FOR ERROR.  Calls 'calloc' to allocate space,
   and then displays an error message and exits if the space couldn't be
   found. */

void *chk_alloc
( unsigned n,		/* Number of elements */
  unsigned size		/* Size of each element */
)
{ 
  void *p;

  p = calloc(n,size);

  if (p==0)
  { fprintf(stderr,"LDPC: Ran out of memory (while trying to allocate %d bytes)\n",
      n*size);
    free_and_exit(1);
  }

  return p;
}
