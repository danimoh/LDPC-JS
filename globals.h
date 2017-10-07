/* Based on Code by Radford M. Neal, see LICENSE_LDPC.
This file is an adaption of rcode.h */

#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdio.h>
#include <stdlib.h>

#include "mod2sparse_struct.h"
#include "mod2dense_struct.h"
#include "mod2sparse.h"
#include "mod2dense.h"

// Global variables as in rcode.h. Global variables are not neccessarily nice, but that's how the original LDPC code was designed.
extern mod2sparse *H;   /* Parity check matrix */

extern int M;       /* Number of rows in parity check matrix */
extern int N;       /* Number of columns in parity check matrix */

extern char type;   /* Type of generator matrix representation. We always use sparse matrices. */
extern int *cols;   /* Ordering of columns in generator matrix */

extern mod2sparse *L, *U; /* Sparse LU decomposition, if type=='s' */
extern int *rows;     /* Ordering of rows in generator matrix (type 's') */

extern mod2dense *G;    /* Dense or mixed representation of generator matrix,
               if type=='d' or type=='m' */

void free_globals();

// Use this method to free global variables before program termination.
// This is required as the wasm / asm memory doesn't get cleaned up at
// program termination which leads to a memory leak on repeated calls.
void free_and_exit(int exit_code);

#endif