/* MOD2SPARSE.H - Interface to module for handling sparse mod2 matrices. */

/* Based on Code by Radford M. Neal, see LICENSE_LDPC. */


/* This module implements operations on sparse matrices of mod2 elements 
   (bits, with addition and multiplication being done modulo 2).  
  
   All procedures in this module display an error message on standard 
   error and terminate the program if passed an invalid argument (indicative
   of a programming error), or if memory cannot be allocated.  Errors from 
   invalid contents of a file result in an error code being returned to the 
   caller, with no message being printed by this module. 
*/


/* DATA STRUCTURES USED TO STORE A SPARSE MATRIX.  Non-zero entries (ie, 1s)
   are represented by nodes that are doubly-linked both by row and by column,
   with the headers for these lists being kept in arrays.  Nodes are allocated
   in blocks to reduce time and space overhead.  Freed nodes are kept for
   reuse in the same matrix, rather than being freed for other uses, except 
   that they are all freed when the matrix is cleared to all zeros by the
   mod2sparse_clear procedure, or copied into by mod2sparse_copy. 

   Direct access to these structures should be avoided except in low-level
   routines.  Use the macros and procedures defined below instead. */

#ifndef MOD2SPARSE_H
#define MOD2SPARSE_H

#include <stdlib.h>
#include <math.h>

#ifndef RELEASE
#include <stdio.h>
#endif

#include "alloc.h"
#include "mod2sparse_struct.h"
#include "globals.h"

/* MACROS TO GET AT ELEMENTS OF A SPARSE MATRIX.  The 'first', 'last', 'next',
   and 'prev' macros traverse the elements in a row or column.  Moving past
   the first/last element gets one to a header element, which can be identified
   using the 'at_end' macro.  Macros also exist for finding out the row 
   and column of an entry, and for finding out the dimensions of a matrix. */

#define mod2sparse_first_in_row(m,i) ((m)->rows[i].right) /* Find the first   */
#define mod2sparse_first_in_col(m,j) ((m)->cols[j].down)  /* or last entry in */
#define mod2sparse_last_in_row(m,i) ((m)->rows[i].left)   /* a row or column  */
#define mod2sparse_last_in_col(m,j) ((m)->cols[j].up)

#define mod2sparse_next_in_row(e) ((e)->right)  /* Move from one entry to     */
#define mod2sparse_next_in_col(e) ((e)->down)   /* another in any of the four */
#define mod2sparse_prev_in_row(e) ((e)->left)   /* possible directions        */
#define mod2sparse_prev_in_col(e) ((e)->up)   

#define mod2sparse_at_end(e) ((e)->row<0) /* See if we've reached the end     */

#define mod2sparse_row(e) ((e)->row)      /* Find out the row or column index */
#define mod2sparse_col(e) ((e)->col)      /* of an entry (indexes start at 0) */

#define mod2sparse_rows(m) ((m)->n_rows)  /* Get the number of rows or columns*/
#define mod2sparse_cols(m) ((m)->n_cols)  /* in a matrix                      */


/* POSSIBLE LU DECOMPOSITION STRATEGIES.  For use with mod2sparse_decomp. */

typedef enum 
{ Mod2sparse_first, 
  Mod2sparse_mincol, 
  Mod2sparse_minprod
} mod2sparse_strategy;


/* PROCEDURES TO MANIPULATE SPARSE MATRICES. */

mod2sparse *mod2sparse_allocate (int, int);
void mod2sparse_free            (mod2sparse *);

void mod2sparse_clear    (mod2sparse *);
void mod2sparse_copy     (mod2sparse *, mod2sparse *);
void mod2sparse_copyrows (mod2sparse *, mod2sparse *, int *);
void mod2sparse_copycols (mod2sparse *, mod2sparse *, int *);

void mod2sparse_print       (mod2sparse *);

mod2entry *mod2sparse_find   (mod2sparse *, int, int);
mod2entry *mod2sparse_insert (mod2sparse *, int, int);
void mod2sparse_delete       (mod2sparse *, mod2entry *);

void mod2sparse_transpose (mod2sparse *, mod2sparse *);
void mod2sparse_add       (mod2sparse *, mod2sparse *, mod2sparse *);
void mod2sparse_multiply  (mod2sparse *, mod2sparse *, mod2sparse *);
void mod2sparse_mulvec    (mod2sparse *, char *, char *);

int mod2sparse_equal (mod2sparse *, mod2sparse *);

int mod2sparse_count_row (mod2sparse *, int);
int mod2sparse_count_col (mod2sparse *, int);

void mod2sparse_add_row (mod2sparse *, int, mod2sparse *, int);
void mod2sparse_add_col (mod2sparse *, int, mod2sparse *, int);

int mod2sparse_decomp (mod2sparse *, int, mod2sparse *, mod2sparse *, 
                       int *, int *, mod2sparse_strategy);

int mod2sparse_forward_sub  (mod2sparse *, int *, char *, char *);
int mod2sparse_backward_sub (mod2sparse *, int *, char *, char *);

#endif