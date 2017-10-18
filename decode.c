/* DECODE.C - Decode blocks of received data. */

/* Based on Code by Radford M. Neal, see LICENSE_LDPC.
This file is an adaption of decode.c */

#include "decode.h"

void decode
( double* received_data, // each char represents one bit. 0 means pretty sure that it's a 0, 255 pretty sure it's a 1, etc.
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
)
{
  char* decoded;
  char *pchk; // parity check. If decoding resulted in a codeword will be all 0

  unsigned iters;		/* Unsigned because can be huge for enum */

  double chngd;	/* Double because can be fraction */
  double *bitpr = NULL;

  int valid;

  int i, j, k;

  /* Set global M and N */
  N = message_length + parity_length;
  M = parity_length;

  if (N<=M)
  { printf("Can't encode if number of bits (%d) not greater than number of checks (%d)\n",
      N,M);
    free_and_exit(1);
  }

  #ifndef RELEASE
  printf("received data:\n");
  for (i=0; i<N; ++i) {
    printf("%f ", received_data[i]);
  }
  printf("\n");
  #endif

  /* Create parity check matrix. This will be written to global variable H */
  create_parity_matrix(parity_matrix_creation_method, checks_per_col,
    seed, avoid4cycle);


  /* Allocate other space. */

  decoded = chk_alloc(N, sizeof *decoded);
  pchk   = chk_alloc (M, sizeof *pchk);
  #ifndef RELEASE
  bitpr  = chk_alloc (N, sizeof *bitpr);
  #endif

  /* Print header for summary table. */
  printf("  iterations valid  changed\n");


  /* Convert to likelihood ratio in favour of a 1, which is P(data | bit is 1) / P(data | bit is 0) */
  switch (channel_type)
  { case CHANNEL_BINARY_SYMMETRIC:
    { // channel_characteristic is error probability
      for (i = 0; i<N; i++)
      { received_data[i] = received_data[i]>0.5 ?
          // let's assume we got a 1. What's the 1 favoring probability ratio P(actually 1) / P(actually not 1).
          // Where P(actually 1) = bit_1_probability - error_prop.
          // and P(actually not 1) = 1 - P(actually 1)
          (received_data[i] - channel_characteristic) / (1 - (received_data[i] - channel_characteristic))
          // assume we got a 0. Thus, 1 favoring ratio is P(actually not 0) / P(actually 0)
          // Where P(actually not 0) = bit_1_probability + error_prop
          // and P(acyually 0) = 1 - P(actually not 0)
          : (received_data[i] + channel_characteristic) / (1 - (received_data[i] + channel_characteristic));
      }
      break;
    }
    case CHANNEL_ADDITIVE_WHITE_GAUSSIAN_NOISE:
    { // channel_characteristic is noise standart deviation
      for (i = 0; i<N; i++)
      { received_data[i] = exp(2*received_data[i]/(channel_characteristic*channel_characteristic));
      }
      break;
    }
    case CHANNEL_ADDITIVE_WHITE_LOGISTIC_NOISE:
    { // channel_characteristic is width of noise distribution
      for (i = 0; i<N; i++)
      { double e, d1, d0;
        e = exp(-(received_data[i]-1)/channel_characteristic);
        d1 = 1 / ((1+e)*(1+1/e));
        e = exp(-(received_data[i]+1)/channel_characteristic);
        d0 = 1 / ((1+e)*(1+1/e));
        received_data[i] = d1/d0;
      }
      break;
    }
    default: exit(1);
  }

  /* Try to decode using the specified method. */

  iters = prprp_decode (H, received_data, max_iterations, decoded, pchk, bitpr);

  /* See if it worked, and how many bits were changed. */
  #ifndef RELEASE
  valid = check(H,decoded,pchk)==0;
  chngd = changed(received_data,decoded,N);
  printf("\n\n%10f    %d  %8.1f\n", (double)iters, valid, (double)chngd);
  /*printf("bit probabilities:\n");
  for (i = 0; i<N; i++)
    { printf("%.2f", bitpr[i]);
    }*/
  #endif

  // if max_iterations was reached, assume we couldn't decode to a valid codeword
  if (iters == max_iterations) {
    free_and_exit(1);
  }
  
  /* Create generator matrix. It is required for the ordering of columns to retrieve the message bits. */
  create_generator_matrix(generator_matrix_sparse_lu_strategy);
  // retrieve the message bits (see extract.c in the original code)
  printf("decoded message:\n");
  for (i=0; i<message_length; ++i) {
    printf("%d ", decoded[cols[i+M]]);
    out_result[i] = decoded[cols[i+M]];
  }

  // TODO free memory
  free_globals();
}
