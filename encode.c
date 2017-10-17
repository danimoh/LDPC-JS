/* Based on Code by Radford M. Neal, see LICENSE_LDPC.
This file is an adaption of encode.c */


#include "encode.h"


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
) {
  char *check;
  int i;

  /* Set global M and N */
  N = message_length + parity_length;
  M = parity_length;

  if (N<=M)
  { printf(
    "Can't encode if number of bits (%d) not greater than number of checks (%d)\n",
      N,M);
    free_and_exit(1);
  }

  printf("Message to encode:\n");
  for (i=0; i<message_length; ++i) {
    printf("%d ", message[i]);
  }
  printf("\n");

  /* Create parity check matrix. This will be written to global variable H */
  create_parity_matrix(parity_matrix_creation_method, checks_per_col,
    seed, avoid4cycle);

  /* Create generator matrix. */
  create_generator_matrix(generator_matrix_sparse_lu_strategy);

  /* Allocate needed space. */

  check = chk_alloc (M, sizeof *check);

  sparse_encode (message, out_encoded_message);

  /* Multiply encoded message with H to check that encoded block is a code word. */

  mod2sparse_mulvec (H, out_encoded_message, check);
  // TODO might also use check from check.h - Maybe remove in release
  for (i = 0; i<M; i++) 
  { if (check[i]==1)
    { printf("LDPC: Encoded message is not a code word!  (Fails check %d)\n",i);
      free(check);
      free_and_exit(1); 
    }
  }

  printf("Encoded message:\n");
  for (i=0; i<N; ++i) {
    printf("%d ", out_encoded_message[i]);
  }
  printf("\n");

  free(check);
  free_globals();
}