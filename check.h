/* CHECK.H - Interface to procedure for computing parity checks, etc. */

/* Based on Code by Radford M. Neal, see LICENSE_LDPC. */

#ifndef CHECK_H
#define CHECK_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "mod2sparse.h"

int check (mod2sparse *, char *, char *);


// TODO all these can be removed in release
double changed (double *, char *, int);

double expected_parity_errors (mod2sparse *, double *);

double loglikelihood (double *, char *, int);
double expected_loglikelihood (double *, double *, int);

double entropy (double *, int);

#endif