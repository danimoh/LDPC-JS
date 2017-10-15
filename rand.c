/* RAND.C - Random number generation module. */

/* Based on Code by Radford M. Neal, see LICENSE_LDPC. */


#include "rand.h"

uint64_t rand_state = 42; /* The state must be seeded with a nonzero value. */

/* SET CURRENT STATE ACCORDING TO SEED. */

void rand_seed
( uint64_t seed
)
{ 
  rand_state = seed;
}

/* See https://en.wikipedia.org/wiki/Xorshift#xorshift.2A */

uint64_t xorshift64star() {
    rand_state ^= rand_state >> 12; // a
    rand_state ^= rand_state << 25; // b
    rand_state ^= rand_state >> 27; // c
    return rand_state * 0x2545F4914F6CDD1D;
}


/* GENERATE UNIFORMLY FROM [0,1). */

double rand_uniform (void)
{
  return (double)xorshift64star() / (double)((uint64_t)-1LL);
}


/* GENERATE RANDOM INTEGER FROM 0, 1, ..., (n-1). */

int rand_int
( int n
)
{ 
  return (int) (n * rand_uniform());
}


