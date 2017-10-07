/* MOD2CONVERT.H - Routines converting between sparse and dense mod2 matrices.*/

/* Based on Code by Radford M. Neal, see LICENSE_LDPC. */

#ifndef MOD2CONVERT_H
#define MOD2CONVERT_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "mod2dense.h"
#include "mod2sparse.h"


void mod2sparse_to_dense (mod2sparse *, mod2dense *);
void mod2dense_to_sparse (mod2dense *, mod2sparse *);

#endif