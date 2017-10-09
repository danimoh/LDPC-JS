/* DEC.H - Interface to decoding procedures. */

/* Based on Code by Radford M. Neal, see LICENSE_LDPC. */


#ifndef DEC_H
#define DEC_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "alloc.h"
#include "mod2sparse.h"
#include "rand.h"
#include "globals.h"
#include "check.h"
#include "enc.h"

unsigned prprp_decode 
(mod2sparse *, double *, int, char *, char *, double *);

void initprp (mod2sparse *, double *, char *, double *);
void iterprp (mod2sparse *, double *, char *, double *);

#endif