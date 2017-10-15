/* RAND.H - Interface to random number generation procedures. */

/* Based on Code by Radford M. Neal, see LICENSE_LDPC. */

/* Random generation routines at the end of this file are taken from the
   GNU C library, see LICENSE_RAND. */


#ifndef RAND_H
#define RAND_H

#include <stdint.h>
#include "globals.h"


extern uint64_t rand_state; /* The state must be seeded with a nonzero value. */

uint64_t xorshift64star();

/* BASIC PSEUDO-RANDOM GENERATION PROCEDURES. */

void rand_seed (uint64_t);		/* Initialize current state structure by seed */

int rand_int (int);		/* Uniform from 0, 1, ... (n-1) */

#endif