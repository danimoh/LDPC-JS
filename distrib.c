/* DISTRIB.C - Procedures for handling distributions over numbers. */

/* Based on Code by Radford M. Neal, see LICENSE_LDPC. */

#include "distrib.h"


/* The distrib type represents the distribution list.  It stores a pointer to 
   an array of distrib_entry elements along with the length of this array.
   Each distrib_entry contains a (number,proportion) pair.

   The code by Neal supported defining more complicated distributions
   (see http://radfordneal.github.io/LDPC-codes/pchk.html#make-ldpc).
   However, I removed that feature and only support a single column weight.
   Note that the actual column wight in the matrix can still vary due to 4cycle
   removal.
*/

distrib *distrib_create
( int	column_weight
)
{
  distrib *d = chk_alloc(1, sizeof *d);
  d->size = 1;
  d->list = chk_alloc (1, sizeof(distrib_entry));
  d->list[0].prop = 1;
  d->list[0].num = column_weight;
  return d;
}


/* FREE SPACE OCCUPIED A DISTRIBUTION LIST. */

void distrib_free
( distrib *d 	/* List to free */
)
{ free(d->list);
  free(d);
}


/* RETURN THE MAXIMUM NUMBER IN A DISTRIBUTION LIST.  Returns 0 if the list 
   pointer is 0. */

int distrib_max 
( distrib *d	/* List to examine */
)
{ 
  int i;
  int cur;

  if (d==0) return 0;

  cur = 0;

  for (i = 1; i<d->size; i++)
  { if (d->list[i].num > d->list[cur].num)
    { cur = i;
    }
  }

  return d->list[cur].num;
}