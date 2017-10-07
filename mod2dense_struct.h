/* Based on Code by Radford M. Neal, see LICENSE_LDPC.
Taken from mod2dense.h to avoid cyclic dependencay with globals.h */

#ifndef MOD2DENSE_STRUCT_H
#define MOD2DENSE_STRUCT_H

#include <stdint.h>   /* Has the definition of uint32_t used below */

/* PACKING OF BITS INTO WORDS.  Bits are packed into 32-bit words, with
   the low-order bit coming first. */

typedef uint32_t mod2word;  /* Data type that holds packed bits. If uint32_t
                   doesn't exist, change it to unsigned long */

#define mod2_wordsize 32    /* Number of bits that fit in a mod2word. */

#define mod2_wordsize_shift 5   /* Amount to shift by to divide by wordsize */
#define mod2_wordsize_mask 0x1f /* What to AND with to produce mod wordsize */

/* Extract the i'th bit of a mod2word. */

#define mod2_getbit(w,i) (((w)>>(i))&1) 

/* Make a word like w, but with the i'th bit set to 1 (if it wasn't already). */

#define mod2_setbit1(w,i) ((w)|(1<<(i))) 

/* Make a word like w, but with the i'th bit set to 0 (if it wasn't already). */

#define mod2_setbit0(w,i) ((w)&(~(1<<(i)))) 


/* STRUCTURE REPRESENTING A DENSE MATRIX.  These structures are dynamically
   allocated using mod2dense_allocate (or by other procedures that call
   mod2dense_allocate).  They should be freed with mod2dense_free when no 
   longer required. 

   Direct access to this structure should be avoided except in low-level
   routines.  Use the macros and procedures defined below instead. */

typedef struct 
{
  int n_rows;       /* Number of rows in the matrix */
  int n_cols;       /* Number of columns in the matrix */

  int n_words;      /* Number of words used to store a column of bits */

  mod2word **col;   /* Pointer to array of pointers to columns */

  mod2word *bits;   /* Pointer to storage block for bits in this matrix 
                           (pieces of this block are pointed to from col) */
} mod2dense;

#endif