/* Based on Code by Radford M. Neal, see LICENSE_LDPC.
This file is an adaption of encode.c */


#include "encode.h"


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
  int generator_matrix_sparse_lu_strategy
) {
  char *encoded_message, *check;
  int i;

  /* Set global M and N */
  N = message_length + parity_length;
  M = parity_length;

  if (N<=M)
  { fprintf(stderr,
    "Can't encode if number of bits (%d) not greater than number of checks (%d)\n",
      N,M);
    free_and_exit(1);
  }


  /* Create parity check matrix. This will be written to global variable H */
  create_parity_matrix(parity_matrix_creation_method, checks_per_col_or_check_distribution,
    seed, avoid4cycle);

  /* Create generator matrix. */
  create_generator_matrix(generator_matrix_sparse_lu_strategy);

  /* Allocate needed space. */

  encoded_message = chk_alloc (N, sizeof *encoded_message);
  check = chk_alloc (M, sizeof *check);

  sparse_encode (message, encoded_message);

  /* Multiply encoded message with H to check that encoded block is a code word. */

  mod2sparse_mulvec (H, encoded_message, check);

  for (i = 0; i<M; i++) 
  { if (check[i]==1)
    { fprintf(stderr,"LDPC: Encoded message is not a code word!  (Fails check %d)\n",i);
      free(check);
      free_and_exit(1); 
    }
  }

  free(check);
  free_globals();
  return encoded_message;
}