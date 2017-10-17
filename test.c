#ifndef RELEASE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "rand.h"
#include "alloc.h"
#include "distrib.h"
#include "mod2sparse.h"
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
  create_parity_matrix(PARITY_MATRIX_CREATION_EVENBOTH, 3, 42, 1);
  mod2sparse_print(H);
  
  printf("\n\n\nCreate Generator matrix.\n");
  create_generator_matrix(GENERATOR_MATRIX_CREATION_LU_STRATEGY_MINPROD);
  print_generator_matrix();
  free_and_exit(0);
}

#endif