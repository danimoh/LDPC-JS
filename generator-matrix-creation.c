/* Based on Code by Radford M. Neal, see LICENSE_LDPC.
This file is an adaption of make-gen.c
For the description of the original code see http://radfordneal.github.io/LDPC-codes/encoding.html.
Note that while computing the generator matrix is still in order of O(N^3), if the sparse method
is chosen, it makes the computation much faster. */

#include "generator-matrix-creation.h"



void create_generator_matrix(int lu_strategy)
{
  mod2sparse_strategy strategy;
  
  if (lu_strategy == GENERATOR_MATRIX_CREATION_LU_STRATEGY_FIRST) {
      strategy = Mod2sparse_first;
  } else if (lu_strategy == GENERATOR_MATRIX_CREATION_LU_STRATEGY_MINCOL) {
      strategy = Mod2sparse_mincol;
  } else {
      strategy = Mod2sparse_minprod;
  }


  /* Allocate space for row and column permutations. These are global variables. */
  cols = chk_alloc (N, sizeof *cols);
  rows = chk_alloc (M, sizeof *rows);

  /* Create generator matrix */
  make_sparse(strategy); 
}


/* MAKE SPARSE REPRESENTATION OF GENERATOR MATRIX. */

void make_sparse(mod2sparse_strategy strategy)
{
  int n, cL, cU, cB;
  int i;

  /* Find LU decomposition. L an U are gloabl variables. */

  L = mod2sparse_allocate(M,M);
  U = mod2sparse_allocate(M,N);

  n = mod2sparse_decomp(H,M,L,U,rows,cols,strategy);

  if (n!=0)
  { printf("LDPC: Note: Parity check matrix has %d redundant checks\n",n);
  }

  /* Compute and print number of 1s. */
  // TODO can be removed in release
  cL = cU = cB = 0;

  for (i = 0; i<M; i++) cL += mod2sparse_count_row(L,i);
  for (i = 0; i<M; i++) cU += mod2sparse_count_row(U,i);
  for (i = M; i<N; i++) cB += mod2sparse_count_col(H,cols[i]);

  printf("LDPC: Number of 1s per check in L is %.1f, U is %.1f, B is %.1f, total is %.1f\n",
    (double)cU/M, (double)cL/M, (double)cB/M, (double)(cL+cU+cB)/M);
}


#ifndef RELEASE
// This is taken from print-gen.c
void print_generator_matrix() {
  int i, j;
  printf("\nGenerator matrix in sparse representation:\n\n");

  printf("Column order (message bits at end):\n");
  for (j = 0; j<N; j++) 
  { if (j%20==0) printf("\n");
    printf(" %3d",cols[j]);
  }
  printf("\n\n");

  printf("Row order:\n");
  for (i = 0; i<M; i++) 
  { if (i%20==0) printf("\n");
    printf(" %3d",rows[i]); 
  }
  printf("\n\n");

  printf("L:\n\n");
  mod2sparse_print(L);
  printf("\n");
  printf("U:\n\n");
  mod2sparse_print(U);
  printf("\n");
}
#endif