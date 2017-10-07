/* Based on Code by Radford M. Neal, see LICENSE_LDPC.
This file is an adaption of make-gen.c
For the description of the original code see http://radfordneal.github.io/LDPC-codes/encoding.html.
Note that while computing the generator matrix is still in order of O(N^3), if the sparse method
is chosen, it makes the computation much faster. */

#ifndef GENERATOR_MATRIX_CREATION_H
#define GENERATOR_MATRIX_CREATION_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "alloc.h"
#include "mod2sparse.h"
#include "mod2dense.h"
#include "mod2convert.h"
#include "globals.h"


// see http://radfordneal.github.io/LDPC-codes/encoding.html
#define GENERATOR_MATRIX_CREATION_SPARSE 0
#define GENERATOR_MATRIX_CREATION_DENSE 1
#define GENERATOR_MATRIX_CREATION_MIXED 2

// see http://radfordneal.github.io/LDPC-codes/sparse-LU.html
#define GENERATOR_MATRIX_CREATION_LU_STRATEGY_FIRST 0
#define GENERATOR_MATRIX_CREATION_LU_STRATEGY_MINCOL 1
#define GENERATOR_MATRIX_CREATION_LU_STRATEGY_MINPROD 2


void create_generator_matrix(
  int creation_method,
  int lu_strategy // only used if creation_method == GENERATOR_MATRIX_CREATION_SPARSE.
);
void make_dense_mixed (int creation_method);     /* Procs to make it */
void make_sparse (mod2sparse_strategy);

void print_generator_matrix(int print_dense);

#endif