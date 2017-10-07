/* Based on Code by Radford M. Neal, see LICENSE_LDPC.
This file is an adaption of rcode.c */

#include "globals.h"

mod2sparse *H;   /* Parity check matrix */

int M;       /* Number of rows in parity check matrix */
int N;       /* Number of columns in parity check matrix */

char type = 's';   /* Type of generator matrix representation. We always use sparse matrices. */
int *cols;   /* Ordering of columns in generator matrix */

mod2sparse *L, *U; /* Sparse LU decomposition, if type=='s' */
int *rows;     /* Ordering of rows in generator matrix (type 's') */

void free_globals() {
    if (H) {
        mod2sparse_free(H);
    }
    if (cols) {
        free(cols);
    }
    if (L) {
        mod2sparse_free(L);
    }
    if (U) {
        mod2sparse_free(U);
    }
    if (rows) {
        free(rows);
    }
}


void free_and_exit(exit_code) {
    free_globals();
    exit(exit_code);
}