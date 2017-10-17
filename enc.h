/* ENC.H - Interface to encoding procedures. */

/* Based on Code by Radford M. Neal, see LICENSE_LDPC. */

#ifndef ENC_H
#define ENC_H

#include <stdlib.h>
#include <math.h>

#ifndef RELEASE
#include <stdio.h>
#endif

#include "rand.h"
#include "alloc.h"
#include "mod2sparse.h"
#include "globals.h"


void sparse_encode (char *, char *);

#endif