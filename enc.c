/* ENC.C - Encoding procedures. */

/* Based on Code by Radford M. Neal, see LICENSE_LDPC. */

#include "enc.h"


/* The procedures in this module obtain the generator matrix to use for
   encoding from the global variables declared in rcode.h */


/* ENCODE A BLOCK USING A SPARSE REPRESENTATION OF THE GENERATOR MATRIX. */

void sparse_encode
( char *sblk,
  char *cblk
)
{
  int i, j;

  mod2entry *e;
  char *x, *y;

  x = chk_alloc (M, sizeof *x);
  y = chk_alloc (M, sizeof *y);

  /* Multiply the vector of source bits by the systematic columns of the 
     parity check matrix, giving x.  Also copy these bits to the coded block. */

  for (i = 0; i<M; i++) x[i] = 0;

  for (j = M; j<N; j++)
  { 
    cblk[cols[j]] = sblk[j-M];

    if (sblk[j-M]==1)
    { for (e = mod2sparse_first_in_col(H,cols[j]);
           !mod2sparse_at_end(e);
           e = mod2sparse_next_in_col(e))
      { x[mod2sparse_row(e)] ^= 1;
      }
    }
  }
 
  /* Solve Ly=x for y by forward substitution, then U(cblk)=y by backward
     substitution. */

  if (!mod2sparse_forward_sub(L,rows,x,y)
   || !mod2sparse_backward_sub(U,cols,y,cblk))
  { 
    free(x);
    free(y);
    free(sblk);
    free(cblk);
    free_and_exit(1); /* Shouldn't occur, even if the parity check matrix has 
                redundant rows */
  }

  free(x);
  free(y);
}


