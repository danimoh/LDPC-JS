/* DISTRIB.C - Procedures for handling distributions over numbers. */

/* Based on Code by Radford M. Neal, see LICENSE_LDPC. */

#include "distrib.h"


/* CREATE A DISTRIBUTION AS SPECIFIED IN A STRING.  Space for the distribution
   is allocated; the string is not freed. 

   The string must consist either of a single positive integer, representing
   the distribution over just that number, or have a form such as the
   following:

      5x2/3.5x1/1.5x4

   This specifies a distribution over 3 numbers, 2, 1, and 4, specified by
   the second number in each pair, with proportions of 0.5, 0.35, and 0.15, 
   respectively, specified by the first number in each pair.  The actual
   proportions are found by dividing the first number in each pair by the sum 
   of these numbers.

   The distrib type represents the distribution list.  It stores a pointer to 
   an array of distrib_entry elements along with the length of this array.
   Each distrib_entry contains a (number,proportion) pair.
*/

distrib *distrib_create
( char *c		/* String describing distribution over numbers */
)
{
  distrib *d;
  char *str, *tstr;
  int i, n, scan_num, size;
  double prop, sum;
  char junk;

  /* Check for special case of a single number. */

  if (sscanf(c,"%d%c",&n,&junk)==1 && n>0)
  { tstr = chk_alloc ( (int)(4.1+log10(n)), sizeof(*tstr));
    sprintf(tstr,"1x%d",n);
    d = distrib_create(tstr);
    free(tstr);
    return d;
  }

  /* Initial scan of string for size and proper usage. */
  
  str = c;
  size = 0;
  sum = 0;

  d = chk_alloc(1, sizeof *d);

  for (;;)
  { 
    scan_num = sscanf(str, "%lgx%d%c", &prop, &n, &junk);

    if ((scan_num!=2 && scan_num!=3) || prop<=0 || n<=0)
    { return 0;
    }
    if (scan_num==3 && junk!='/')
    { return 0;
    }

    size += 1;
    sum += prop;

    if (scan_num==2)
    { break;
    }
    else
    { str = (char*)strchr(str, '/') + 1;
    }
  }

  /* Allocate memory for the list and fill it in */

  d->size = size;
  d->list = chk_alloc (size, sizeof(distrib_entry));

  i = 0;
  str = c;

  for (;;)
  { 
    scan_num = sscanf(str, "%lgx%d%c", &prop, &n, &junk);

    d->list[i].prop = prop/sum;
    d->list[i].num = n;
    i += 1;

    if (scan_num==2)
    { break;
    }
    else if (scan_num==3)
    { str = (char*)strchr(str, '/') + 1;
    }
    else
    { distrib_free(d);
      free_and_exit(1);
    }
  }

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