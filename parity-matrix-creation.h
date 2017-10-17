/* Based on Code by Radford M. Neal, see LICENSE_LDPC.
This file is an adaption of make-ldpc.c 
For the description of the original code see http://radfordneal.github.io/LDPC-codes/pchk.html */

#ifndef PARITY_MATRIX_CREATION_H
#define PARITY_MATRIX_CREATION_H

#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifndef RELEASE
#include <stdio.h>
#endif

#include "rand.h"
#include "alloc.h"
#include "distrib.h"
#include "mod2sparse.h"
#include "globals.h"


/* Uniform number of bits per column, with number specified */
#define PARITY_MATRIX_CREATION_EVENCOL 0
/* Uniform (as possible) over both columns and rows */
#define PARITY_MATRIX_CREATION_EVENBOTH 1 

/* CREATE A PARITY MATRIX */

void create_parity_matrix
( int creation_method,
  int checks_per_col,
  int seed,
  int avoid4cycle
);

void make_ldpc
( int seed,     /* Random number seed */
  int creation_method,   /* How to make it */
  distrib *d,       /* Distribution list specified */
  int no4cycle      /* Eliminate cycles of length four? */
);


/* PARTITION THE COLUMNS ACCORDING TO THE SPECIFIED PROPORTIONS.  It
   may not be possible to do this exactly.  Returns a pointer to an
   array of integers containing the numbers of columns corresponding 
   to the entries in the distribution passed. */

int *column_partition
( distrib *d,       /* List of proportions and number of check-bits */
  int n         /* Total number of columns to partition */
);

#endif