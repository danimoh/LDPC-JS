/* Based on Code by Radford M. Neal, see LICENSE_LDPC.
This file is an adaption of make-gen.c
For the description of the original code see http://radfordneal.github.io/LDPC-codes/encoding.html.
Note that while computing the generator matrix is still in order of O(N^3), if the sparse method
is chosen, it makes the computation much faster. */

#include "generator-matrix-creation.h"



void create_generator_matrix(int creation_method, int lu_strategy)
{
  mod2sparse_strategy strategy;
  
  if (creation_method == GENERATOR_MATRIX_CREATION_SPARSE) {
    if (lu_strategy == GENERATOR_MATRIX_CREATION_LU_STRATEGY_FIRST) {
        strategy = Mod2sparse_first;
    } else if (lu_strategy == GENERATOR_MATRIX_CREATION_LU_STRATEGY_MINCOL) {
        strategy = Mod2sparse_mincol;
    } else {
        strategy = Mod2sparse_minprod;
    }
  }


  /* Allocate space for row and column permutations. These are global variables. */
  cols = chk_alloc (N, sizeof *cols);
  rows = chk_alloc (M, sizeof *rows);

  /* Create generator matrix with specified method. */
  if (creation_method == GENERATOR_MATRIX_CREATION_SPARSE) {
    make_sparse(strategy); 
  } else {
    make_dense_mixed(creation_method);
  }
}


/* MAKE DENSE OR MIXED REPRESENTATION OF GENERATOR MATRIX. */

void make_dense_mixed (int creation_method)
{ 
  mod2dense *DH, *A, *A2, *AI, *B;
  int i, j, c, c2, n;
  int *rows_inv;

  DH = mod2dense_allocate(M,N);
  AI = mod2dense_allocate(M,M);
  B  = mod2dense_allocate(M,N-M);
  G  = mod2dense_allocate(M,N-M);

  mod2sparse_to_dense(H,DH);

  /* Invert using whatever selection of rows/columns is needed to get a non-singular sub-matrix. */

  A  = mod2dense_allocate(M,N);
  A2 = mod2dense_allocate(M,N);

  n = mod2dense_invert_selected(DH,A2,rows,cols);
  mod2sparse_to_dense(H,DH);  /* DH was destroyed by invert_selected */

  if (n>0)
  { printf("LDPC: Parity check matrix has %d redundant checks\n",n);
  }

  rows_inv = chk_alloc(M, sizeof *rows_inv);

  for (i = 0; i<M; i++)
  { rows_inv[rows[i]] = i;
  }

  mod2dense_copyrows(A2,A,rows);
  mod2dense_copycols(A,A2,cols);
  mod2dense_copycols(A2,AI,rows_inv);

  mod2dense_copycols(DH,B,cols+M);

  /* Form final generator matrix. */

  if (creation_method == GENERATOR_MATRIX_CREATION_DENSE) 
  { mod2dense_multiply(AI,B,G);
  }
  else if (creation_method == GENERATOR_MATRIX_CREATION_MIXED)
  { G = AI;
    AI = NULL;
  }
  else
  { free_and_exit(1);
  }

  /* Compute and print number of 1s. */

  // TODO this can be removed in release
  if (creation_method == GENERATOR_MATRIX_CREATION_DENSE)  
  { c = 0;
    for (i = 0; i<M; i++)
    { for (j = 0; j<N-M; j++)
      { c += mod2dense_get(G,i,j);
      }
    }
    printf("LDPC: Number of 1s per check in Inv(A) X B is %.1f\n", (double)c/M);
  }
  else // mixed
  { c = 0;
    for (i = 0; i<M; i++)
    { for (j = 0; j<M; j++)
      { c += mod2dense_get(G,i,j);
      }
    }
    c2 = 0;
    for (i = M; i<N; i++) 
    { c2 += mod2sparse_count_col(H,cols[i]);
    }
    printf("LDPC: Number of 1s per check in Inv(A) is %.1f, in B is %.1f, total is %.1f\n",
     (double)c/M, (double)c2/M, (double)(c+c2)/M);
  }

  // TODO free
}


/* MAKE SPARSE REPRESENTATION OF GENERATOR MATRIX. */

void make_sparse(mod2sparse_strategy strategy)
{
  int n, cL, cU, cB;
  int i;

  /* Find LU decomposition. */

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



// This is taken from print-gen.c
// TODO can be removed in release
void print_generator_matrix(int print_dense) {
  int i, j;
  switch (type)
  {
    case 's': 
    { 
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

      if (print_dense)
      { mod2dense *Ld, *Ud;
        Ld = mod2dense_allocate(M,M);
        Ud = mod2dense_allocate(M,N);
        mod2sparse_to_dense(L,Ld);
        mod2sparse_to_dense(U,Ud);
        printf("L:\n\n");
        mod2dense_print(Ld);
        printf("\n");
        printf("U:\n\n");
        mod2dense_print(Ud);
        printf("\n");
        free(Ld);
        free(Ud);
      }
      else
      { printf("L:\n\n");
        mod2sparse_print(L);
        printf("\n");
        printf("U:\n\n");
        mod2sparse_print(U);
        printf("\n");
      }
     
      break;
    }

    case 'd': case 'm':
    {
      if (type=='d')
      { printf("\nGenerator matrix in dense representation:\n\n");
      }
      if (type=='m')
      { printf("\nGenerator matrix in mixed representation:\n\n");
      }

      printf("Column order (message bits at end):\n");
      for (j = 0; j<N; j++) 
      { if (j%20==0) printf("\n");
        printf(" %3d",cols[j]);
      }
      printf("\n\n");

      printf (type=='d' ? "Inv(A) X B:\n\n" : "Inv(A):\n\n");
      mod2dense_print(G);
      printf("\n");

      break;
    }

    default: 
    { fprintf(stderr,"Unknown type of generator matrix file\n");
      free_and_exit(1);
    }
  }
}