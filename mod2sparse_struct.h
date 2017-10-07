/* Based on Code by Radford M. Neal, see LICENSE_LDPC.
Taken from mod2sparse.h to avoid cyclic dependencay with globals.h */

#ifndef MOD2SPARSE_STRUCT_H
#define MOD2SPARSE_STRUCT_H

typedef struct mod2entry /* Structure representing a non-zero entry, or
                  the header for a row or column               */
{
  int row, col;       /* Row and column indexes of this entry, starting
                             at 0, and with -1 for a row or column header  */

  struct mod2entry *left, *right,  /* Pointers to entries adjacent in row  */
                   *up, *down;     /*   and column, or to headers.  Free   */
                                   /*   entries are linked by 'left'.      */

  double pr, lr;      /* Probability and likelihood ratios - not used  */
              /*   by the mod2sparse module itself             */
} mod2entry;

#define Mod2sparse_block 10  /* Number of entries to block together for
                                memory allocation */

typedef struct mod2block /* Block of entries allocated all at once */
{
  struct mod2block *next;  /* Next block that has been allocated */

  mod2entry entry[Mod2sparse_block]; /* Entries in this block */

} mod2block;

typedef struct      /* Representation of a sparse matrix */
{ 
  int n_rows;         /* Number of rows in the matrix */
  int n_cols;         /* Number of columns in the matrix */

  mod2entry *rows;    /* Pointer to array of row headers */
  mod2entry *cols;    /* Pointer to array of column headers */

  mod2block *blocks;      /* Blocks that have been allocated */
  mod2entry *next_free;   /* Next free entry */

} mod2sparse;

#endif