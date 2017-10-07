/* Based on Code by Radford M. Neal, see LICENSE_LDPC.
This file is an adaption of encode.c */

#ifndef ENCODE_H
#define ENCODE_H

#include "alloc.h"
#include "mod2dense.h"
#include "mod2sparse.h"
#include "enc.h"
#include "globals.h"
#include "parity-matrix-creation.h"
#include "generator-matrix-creation.h"


char* encode(
  char* message, // each char represents one bit
  int message_length, // number of message bits (K)
  int parity_length, // number of parity bits (M = N-K)
  // parameters for parity matrix creation:
  int parity_matrix_creation_method,
  char* checks_per_col_or_check_distribution, // e.g. "3" or "0.3x2/0.6x3/0.1x7"
  int seed,
  int avoid4cycle,
  // parameters for generator matrix creation:
  int generator_matrix_creation_method,
  int generator_matrix_sparse_lu_strategy // only used when using sparse matrices
);

#endif