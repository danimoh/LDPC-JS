/* ALLOC.H - Interface to memory allocation procedure. */

/* Based on Code by Radford M. Neal, see LICENSE_LDPC. */

#ifndef alloc_h
#define alloc_h

#include <stdlib.h>
#include <stdio.h>

#include "globals.h"

void *chk_alloc (unsigned, unsigned);	/* Calls 'calloc' and exits with error
                                           if it fails */
#endif