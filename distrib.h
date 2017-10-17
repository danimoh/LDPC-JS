/* DISTRIB.H - Interface to module for handling distributions over numbers. */

/* Based on Code by Radford M. Neal, see LICENSE_LDPC. */


#ifndef DISTRIB_H
#define DISTRIB_H

#include <stdlib.h>
#include <math.h>
#include <string.h>

#ifndef RELEASE
#include <stdio.h>
#endif

#include "alloc.h"

/* DATA STRUCTURES USED TO STORE A DISTRIBUTION LIST.  Entries in the list 
 * (distrib_entry) are stored in an array (distrib->list[]). */

typedef struct distrib_entry
{ int num;			/* A positive number */
  double prop;			/* Proportion for this number */
} distrib_entry;

typedef struct distrib
{ struct distrib_entry *list;	/* The list of numbers and proportions */
  int size;			/* Number of entries in the list */
} distrib;


/* MACROS TO ACCESS ELEMENTS OF A DISTRIBUTION LIST.  Note that indexes for
   entries start at 0. */

#define distrib_num(d,i) \
  ((d)->list[i].num)		/* The number for the i'th entry */

#define distrib_prop(d,i) \
  ((d)->list[i].prop)		/* The i'th entry's proportion [probability] */

#define distrib_size(d) \
  ((d)->size)			/* The length of the list (integer) */


/* PROCEDURES FOR DISTRIBUTION LISTS. */

distrib *distrib_create	(int);
void distrib_free (distrib *);

int distrib_max(distrib *);

#endif