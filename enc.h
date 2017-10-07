/* ENC.H - Interface to encoding procedures. */

/* Based on Code by Radford M. Neal, see LICENSE_LDPC. */

#ifndef ENC_H
#define ENC_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "rand.h"
#include "alloc.h"
#include "mod2sparse.h"
#include "mod2dense.h"
#include "mod2convert.h"
#include "globals.h"


void sparse_encode (char *, char *);
void dense_encode  (char *, char *, mod2dense *, mod2dense *);
void mixed_encode  (char *, char *, mod2dense *, mod2dense *);

#endif