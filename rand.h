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

int rand_word (void);       /* Generate random 31-bit positive integer */
int rand_int (int);		/* Uniform from 0, 1, ... (n-1) */

#endif