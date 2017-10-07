/* MOD2CONVERT.C - Routines converting between sparse and dense mod2 matrices.*/

/* Based on Code by Radford M. Neal, see LICENSE_LDPC. */


/* NOTE:  See mod2convert.html for documentation on these procedures. */


#include "mod2convert.h"


/* CONVERT A MOD2 MATRIX FROM SPARSE TO DENSE FORM.  */

void mod2sparse_to_dense 
( mod2sparse *m, 	/* Sparse matrix to convert */
  mod2dense *r		/* Place to store result */
)
{
  mod2entry *e;
  int i;

  if (mod2sparse_rows(m)>mod2dense_rows(r) 
   || mod2sparse_cols(m)>mod2dense_cols(r))
  { fprintf(stderr,
      "mod2sparse_to_dense: Dimension of result matrix is less than source\n");
    free_and_exit(1);
  }

  mod2dense_clear(r);

  for (i = 0; i<mod2sparse_rows(m); i++)
  { e = mod2sparse_first_in_row(m,i);
    while (!mod2sparse_at_end(e))
    { mod2dense_set(r,i,mod2sparse_col(e),1);
      e = mod2sparse_next_in_row(e);
    }
  }
}


/* CONVERT A MOD2 MATRIX FROM DENSE TO SPARSE FORM.  */

void mod2dense_to_sparse 
( mod2dense *m, 	/* Dense matrix to convert */
  mod2sparse *r		/* Place to store result */
)
{
  int i, j;

  if (mod2dense_rows(m)>mod2sparse_rows(r) 
   || mod2dense_cols(m)>mod2sparse_cols(r))
  { fprintf(stderr,
      "mod2dense_to_sparse: Dimension of result matrix is less than source\n");
    free_and_exit(1);
  }

  mod2sparse_clear(r);

  for (i = 0; i<mod2dense_rows(m); i++)
  { for (j = 0; j<mod2dense_cols(m); j++)
    { if (mod2dense_get(m,i,j))
      { mod2sparse_insert(r,i,j);
      }
    }
  }
}
