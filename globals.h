/* Based on Code by Radford M. Neal, see LICENSE_LDPC.
This file is an adaption of rcode.h */

#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdlib.h>

#ifndef RELEASE
#include <stdio.h>
#endif

// disable printf on release
#ifdef RELEASE
#define printf(fmt, ...) (0)
#endif

#include "mod2sparse_struct.h"
#include "mod2sparse.h"

// Global variables as in rcode.h. Global variables are not neccessarily nice, but that's how the original LDPC code was designed.
extern mod2sparse *H;   /* Parity check matrix */

extern int M;       /* Number of rows in parity check matrix */
extern int N;       /* Number of columns in parity check matrix */

extern int *cols;   /* Ordering of columns in generator matrix */

extern mod2sparse *L, *U; /* Sparse LU decomposition, if type=='s' */
extern int *rows;     /* Ordering of rows in generator matrix (type 's') */

void free_globals();

// Use this method to free global variables before program termination.
// This is required as the wasm / asm memory doesn't get cleaned up at
// program termination which leads to a memory leak on repeated calls.
void free_and_exit(int exit_code);

#endif