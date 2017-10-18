/* CHECK.H - Interface to procedure for computing parity checks, etc. */

/* Based on Code by Radford M. Neal, see LICENSE_LDPC. */

#ifndef CHECK_H
#define CHECK_H

#include <stdlib.h>
#include <math.h>

#ifndef RELEASE
#include <stdio.h>
#endif

#include "mod2sparse.h"

int check (mod2sparse *, char *, char *);


#ifndef RELEASE

double changed (double *, char *, int);

double expected_parity_errors (mod2sparse *, double *);

double loglikelihood (double *, char *, int);
double expected_loglikelihood (double *, double *, int);

double entropy (double *, int);

#endif

#endif