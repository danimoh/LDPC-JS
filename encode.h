/* Based on Code by Radford M. Neal, see LICENSE_LDPC.
This file is an adaption of encode.c */

#ifndef ENCODE_H
#define ENCODE_H

#ifndef RELEASE
#include <stdio.h>
#endif

#include "alloc.h"
#include "mod2sparse.h"
#include "enc.h"
#include "globals.h"
#include "parity-matrix-creation.h"
#include "generator-matrix-creation.h"


void encode(
  char* message, // each char represents one bit
  int message_length, // number of message bits (K)
  int parity_length, // number of parity bits (M = N-K)
  // parameters for parity matrix creation:
  int parity_matrix_creation_method,
  int checks_per_col,
  int seed,
  int avoid4cycle,
  // parameters for generator matrix creation:
  int generator_matrix_sparse_lu_strategy,
  char* out_encoded_message // each char represents one bit. Length N.
);

#endif