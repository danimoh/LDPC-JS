# LDPC-JS

Low density parity check in Javascript.

This code is based on C code by Radford M. Neal (http://radfordneal.github.io/LDPC-codes/index.html)
which has been changed and optimized for compilation to WebAssembly.
The particular changes are listed in LICENSE_LDPC.

The code builds sparse parity matrices H by the random strategy by Neal and MacKay.
The matrices are stored in a sparse representation, saving memory and computation time.
Building the generator matrix G is done by a sparse LU decomposition algorithm.
For more details visit http://radfordneal.github.io/LDPC-codes/index.html.