/* Based on Code by Radford M. Neal, see LICENSE_LDPC.
This file is an adaption of make-ldpc.c 
For the description of the original code see http://radfordneal.github.io/LDPC-codes/pchk.html */

#include "parity-matrix-creation.h"


void create_parity_matrix(int creation_method, int checks_per_col, int seed, int avoid4cycle)
{
  distrib* d = distrib_create(checks_per_col); // see http://radfordneal.github.io/LDPC-codes/pchk.html#make-ldpc

  /* Check for some problems. */

  if (distrib_max(d)>M)
  { printf("LDPC: At least one checks per bit (%d) is greater than total checks (%d)\n",
      distrib_max(d), M);
    distrib_free(d);
    free_and_exit(1);
  }

  if (distrib_max(d)==M && N>1 && avoid4cycle)
  { printf("LDPC: Can't eliminate cycles of length four with this many checks per bit\n");
    distrib_free(d);
    free_and_exit(1);
  }

  /* Make the parity check matrix. */

  make_ldpc(seed,creation_method,d,avoid4cycle);
  distrib_free(d);
}


void make_ldpc
( int seed,     /* Random number seed */
  int creation_method,   /* How to make it */
  distrib *d,       /* Distribution list specified */
  int no4cycle      /* Eliminate cycles of length four? */
)
{
  mod2entry *e, *f, *g, *h;
  int added, uneven, elim4, all_even, n_full, left;
  int i, j, k, t, z, cb_N;
  int *part, *u;

  rand_seed(10*seed+1);

  H = mod2sparse_allocate(M,N);
  part = column_partition(d,N);

  /* Create the initial version of the parity check matrix. */

  switch (creation_method)
  { 
    case PARITY_MATRIX_CREATION_EVENCOL:
    { 
      z = 0;
      left = part[z];

      for (j = 0; j<N; j++)
      { while (left==0)
        { z += 1;
          if (z>distrib_size(d))
          { distrib_free(d);
            free(part);
            free_and_exit(1);
          }
          left = part[z];
        }
        for (k = 0; k<distrib_num(d,z); k++)
        { do
          { i = rand_int(M);
          } while (mod2sparse_find(H,i,j));
          mod2sparse_insert(H,i,j);
        }
        left -= 1;
      }

      break;
    }

    case PARITY_MATRIX_CREATION_EVENBOTH:
    {
      cb_N = 0;
      for (z = 0; z<distrib_size(d); z++)
      { cb_N += distrib_num(d,z) * part[z];
      }
      
      u = chk_alloc (cb_N, sizeof *u);

      for (k = cb_N-1; k>=0; k--)
      { u[k] = k%M;
      }
  
      uneven = 0;
      t = 0;
      z = 0;
      left = part[z];

      for (j = 0; j<N; j++)
      { 
        while (left==0)
        { z += 1;
          if (z>distrib_size(d))
          { distrib_free(d);
            free(part);
            free_and_exit(1);
          }
          left = part[z];
        }

      for (k = 0; k<distrib_num(d,z); k++)
        { 
          for (i = t; i<cb_N && mod2sparse_find(H,u[i],j); i++) ;

          if (i==cb_N)
          { uneven += 1;
            do
            { i = rand_int(M);
            } while (mod2sparse_find(H,i,j));
            mod2sparse_insert(H,i,j);
          }
          else
          { do
            { i = t + rand_int(cb_N-t);
            } while (mod2sparse_find(H,u[i],j));
            mod2sparse_insert(H,u[i],j);
            u[i] = u[t];
            t += 1;
          }
        }

        left -= 1;
      }

      if (uneven>0)
      { printf("LDPC: Had to place %d checks in rows unevenly\n",uneven);
      }

      free(u);

      break;
    }

    default: {
      distrib_free(d);
      free(part);
      free_and_exit(1);
    }
  }

  /* Add extra bits to avoid rows with less than two checks. */

  added = 0;

  for (i = 0; i<M; i++)
  { e = mod2sparse_first_in_row(H,i);
    if (mod2sparse_at_end(e))
    { j = rand_int(N);
      e = mod2sparse_insert(H,i,j);
      added += 1;
    }
    e = mod2sparse_first_in_row(H,i);
    if (mod2sparse_at_end(mod2sparse_next_in_row(e)) && N>1)
    { do 
      { j = rand_int(N); 
      } while (j==mod2sparse_col(e));
      mod2sparse_insert(H,i,j);
      added += 1;
    }
  }

  if (added>0)
  { printf("LDPC: Added %d extra bit-checks to make row counts at least two\n",
      added);
  }

  /* Add extra bits to try to avoid problems with even column counts. */

  n_full = 0;
  all_even = 1;
  for (z = 0; z<distrib_size(d); z++)
  { if (distrib_num(d,z)==M) 
    { n_full += part[z];
    }
    if (distrib_num(d,z)%2==1)
    { all_even = 0;
    }
  }

  if (all_even && N-n_full>1 && added<2)
  { int a;
    for (a = 0; added+a<2; a++)
    { do
      { i = rand_int(M);
        j = rand_int(N);
      } while (mod2sparse_find(H,i,j));
      mod2sparse_insert(H,i,j);
    }
    printf("LDPC: Added %d extra bit-checks to try to avoid problems from even column counts\n",
      a);
  }

  /* Eliminate cycles of length four, if asked, and if possible. */

  if (no4cycle)
  { 
    elim4 = 0;

    for (t = 0; t<10; t++) 
    { k = 0;
      for (j = 0; j<N; j++)
      { for (e = mod2sparse_first_in_col(H,j);
             !mod2sparse_at_end(e);
             e = mod2sparse_next_in_col(e))
        { for (f = mod2sparse_first_in_row(H,mod2sparse_row(e));
               !mod2sparse_at_end(f);
               f = mod2sparse_next_in_row(f))
          { if (f==e) continue;
            for (g = mod2sparse_first_in_col(H,mod2sparse_col(f));
                 !mod2sparse_at_end(g);
                 g = mod2sparse_next_in_col(g))
            { if (g==f) continue;
              for (h = mod2sparse_first_in_row(H,mod2sparse_row(g));
                   !mod2sparse_at_end(h);
                   h = mod2sparse_next_in_row(h))
              { if (mod2sparse_col(h)==j)
                { do
                  { i = rand_int(M);
                  } while (mod2sparse_find(H,i,j));
                  mod2sparse_delete(H,e);
                  mod2sparse_insert(H,i,j);
                  elim4 += 1;
                  k += 1;
                  goto nextj;
                }
              }
            }
          }
        }
      nextj: ;
      }
      if (k==0) break;
    }

    if (elim4>0)
    { printf("LDPC: Eliminated %d cycles of length four by moving checks within column\n",
         elim4);
    }

    if (t==10) 
    { printf("LDPC: Couldn't eliminate all cycles of length four in 10 passes\n");
    }
  }
}


int *column_partition
( distrib *d,       /* List of proportions and number of check-bits */
  int n         /* Total number of columns to partition */
)
{
  double *trunc;
  int *part;
  int cur, used;
  int i, j;

  trunc = chk_alloc (distrib_size(d), sizeof(double));
  part = chk_alloc (distrib_size(d), sizeof(int));

  used = 0;
  for (i = 0; i<distrib_size(d); i++)
  { cur = floor(distrib_prop(d,i)*n);
    part[i] = cur; 
    trunc[i] = distrib_prop(d,i)*n - cur; 
    used += cur; 
  }

  if (used>n) 
  { 
    free(trunc);
    free(part);
    distrib_free(d);
    free_and_exit(1);
  }
  
  while (used<n)
  { cur = 0;
    for (j = 1; j<distrib_size(d); j++) 
    { if (trunc[j]>trunc[cur])
      { cur = j;
      }
    }
    part[cur] += 1;
    used += 1;
    trunc[cur] = -1;
  }

  free(trunc);
  return part;
}
