/* MOD2DENSE.H - Interface to module for handling dense mod2 matrices. */

/* Based on Code by Radford M. Neal, see LICENSE_LDPC. */


/* This module implements operations on matrices of mod2 elements (bits,
   with addition and multiplication being done modulo 2).  The matrices
   are stored with consecutive bits of a column packed into words, and 
   the procedures are implemented where possible using bit operations 
   on these words.  This is an appropriate representation when the matrices 
   are dense (ie, 0s and 1s are about equally frequent). 
  
   All procedures in this module display an error message on standard 
   error and terminate the program if passed an invalid argument (indicative
   of a programming error), or if memory cannot be allocated.  Errors from 
   invalid contents of a file result in an error code being returned to the 
   caller, with no message being printed by this module. 
*/


#ifndef MOD2DENSE_H
#define MOD2DENSE_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "alloc.h"
#include "mod2dense_struct.h"


/* MACROS. */

#define mod2dense_rows(m) ((m)->n_rows)  /* Get the number of rows or columns */
#define mod2dense_cols(m) ((m)->n_cols)  /* in a matrix                       */


/* PROCEDURES. */

mod2dense *mod2dense_allocate (int, int);
void mod2dense_free           (mod2dense *);

void mod2dense_clear    (mod2dense *);
void mod2dense_copy     (mod2dense *, mod2dense *);
void mod2dense_copyrows (mod2dense*, mod2dense *, int *);
void mod2dense_copycols (mod2dense*, mod2dense *, int *);

void mod2dense_print      (mod2dense *);

int  mod2dense_get (mod2dense *, int, int);
void mod2dense_set (mod2dense *, int, int, int);
int  mod2dense_flip(mod2dense *, int, int);

void mod2dense_transpose (mod2dense *, mod2dense *);
void mod2dense_add       (mod2dense *, mod2dense *, mod2dense *);
void mod2dense_multiply  (mod2dense *, mod2dense *, mod2dense *);

int mod2dense_equal (mod2dense *, mod2dense *);

int mod2dense_invert          (mod2dense *, mod2dense *);
int mod2dense_forcibly_invert (mod2dense *, mod2dense *, int *, int *);
int mod2dense_invert_selected (mod2dense *, mod2dense *, int *, int *);

#endif