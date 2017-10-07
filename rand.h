/* RAND.H - Interface to random number generation procedures. */

/* Based on Code by Radford M. Neal, see LICENSE_LDPC. */

/* Random generation routines at the end of this file are taken from the
   GNU C library, see LICENSE_RAND. */


#ifndef RAND_H
#define RAND_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "globals.h"


/* STATE OF RANDOM NUMBER GENERATOR. */

#define N_tables 5		/* Number of tables of real random numbers */

typedef struct
{ int seed;			/* Seed state derives from */
  int ptr[N_tables];		/* Pointers for tables of real random numbers */
  unsigned short state48[3];	/* State of 'rand48' pseudo-random generator */
} rand_state;


/* BASIC PSEUDO-RANDOM GENERATION PROCEDURES. */

void rand_seed (int);		/* Initialize current state structure by seed */

void rand_use_state (rand_state *); /* Start using given state structure */
rand_state *rand_get_state (void);  /* Return pointer to current state */

int rand_word (void);		/* Generate random 31-bit positive integer */


/* GENERATORS FOR VARIOUS DISTRIBUTIONS. */

double rand_uniform (void);	/* Uniform from [0,1) */
double rand_uniopen (void);	/* Uniform from (0,1) */

int rand_int (int);		/* Uniform from 0, 1, ... (n-1) */
int rand_pickd (double *, int);	/* From 0 ... (n-1), with given distribution */
int rand_pickf (float *, int);	/* Same as above, but with floats */
void rand_permutation (int *, int); /* Random permutation */

int rand_poisson (double);	/* Poisson with given mean */
double rand_gaussian (void);	/* Gaussian with mean zero and unit variance */
double rand_logistic (void);	/* Logistic centred at zero with unit width */
double rand_cauchy (void);	/* Cauchy centred at zero with unit width */
double rand_gamma (double);	/* Gamma with given shape parameter */
double rand_exp (void);		/* Exponential with mean one */
double rand_beta (double, double); /* Beta with given parameters */

#endif