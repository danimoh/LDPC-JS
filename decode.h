/* Based on Code by Radford M. Neal, see LICENSE_LDPC.
This file is an adaption of decode.c */

#ifndef DECODE_H
#define DECODE_H

#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifndef RELEASE
#include <stdio.h>
#endif

#include "rand.h"
#include "alloc.h"
#include "mod2sparse.h"
#include "globals.h"
#include "parity-matrix-creation.h"
#include "generator-matrix-creation.h"
#include "check.h"
#include "dec.h"


#define CHANNEL_BINARY_SYMMETRIC 0
#define CHANNEL_ADDITIVE_WHITE_GAUSSIAN_NOISE 1
#define CHANNEL_ADDITIVE_WHITE_LOGISTIC_NOISE 2

void decode
( double* received_data, // each double represents one bit. 0 means pretty sure that it's a 0, 255 pretty sure it's a 1, 240 rather sure it's a 1, etc. Length N.
  int message_length, // number of message bits (K)
  int parity_length, // number of parity bits (M = N-K)
  int channel_type, // binary symmetric (BSC), additive white gaussian (AWGN) or white logarithmic noise (AWLN)
  double channel_characteristic, // for BSC: error probability; for AWGN: noise standart deviation; for AWLN: width of noise distribution
  int max_iterations, // max iterations for the probability propagation
  // parameters for parity matrix creation:
  int parity_matrix_creation_method,
  int checks_per_col,
  int seed,
  int avoid4cycle,
  // parameters for generator matrix creation:
  int generator_matrix_sparse_lu_strategy,
  char* out_result // each char represents one bit. All values 0s and 1s. Must have message length.
);

#endif