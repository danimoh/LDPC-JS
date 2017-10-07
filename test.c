#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "rand.h"
#include "alloc.h"
#include "distrib.h"
#include "mod2sparse.h"
#include "mod2dense.h"
#include "mod2convert.h"
#include "globals.h"
#include "parity-matrix-creation.h"
#include "generator-matrix-creation.h"

int main
( int argc,
  char **argv
)
{
  M = 20;
  N = 40;
  printf("Create parity matrix.\n");
  create_parity_matrix(PARITY_MATRIX_CREATION_EVENBOTH, "3", 42, 1);
  mod2dense* D = mod2dense_allocate(M,N);
  mod2sparse_to_dense(H,D);
  mod2dense_print(D);
  mod2dense_free(D);

  printf("\n\n\nCreate Generator matrix.\n");
  create_generator_matrix(GENERATOR_MATRIX_CREATION_SPARSE, GENERATOR_MATRIX_CREATION_LU_STRATEGY_MINPROD);
  print_generator_matrix(1);
  free_and_exit(0);
}