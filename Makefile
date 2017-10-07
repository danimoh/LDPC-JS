# compile using emscripten
COMPILE_EMCC = emcc -c -O    # Command to compile a module from .c to .o
LINK_EMCC =    emcc          # Command to link a program


# MAKE ALL THE MAIN PROGRAMS.  First makes the modules used.

emcc:
	$(COMPILE_EMCC) globals.c
	$(COMPILE_EMCC) alloc.c
	$(COMPILE_EMCC) mod2dense.c
	$(COMPILE_EMCC) mod2sparse.c
	$(COMPILE_EMCC) mod2convert.c
	$(COMPILE_EMCC) distrib.c
	$(COMPILE_EMCC) enc.c
	$(COMPILE_EMCC) -DRAND_FILE=\"./randfile\" rand.c
	$(COMPILE_EMCC) parity-matrix-creation.c
	$(COMPILE_EMCC) generator-matrix-creation.c
	$(COMPILE_EMCC) encode.c
	$(COMPILE_EMCC) test.c
	# compile to asm.js (might want to add ONLY_MY_CODE=1, see https://github.com/kripken/emscripten/issues/3955)
	$(LINK_EMCC) parity-matrix-creation.o generator-matrix-creation.o mod2sparse.o mod2dense.o mod2convert.o \
	   rand.o alloc.o globals.o distrib.o enc.o encode.o test.o -lm -s EXPORTED_FUNCTIONS='["_create_parity_matrix","_encode"]' \
	   -s NO_EXIT_RUNTIME=1 -o ldpc-asm.html --preload-file ./randfile
	# compile to wasm
	$(LINK_EMCC) parity-matrix-creation.o generator-matrix-creation.o mod2sparse.o mod2dense.o mod2convert.o \
	   rand.o alloc.o globals.o distrib.o enc.o encode.o test.o -lm -s EXPORTED_FUNCTIONS='["_create_parity_matrix","_encode"]' \
	   -s NO_EXIT_RUNTIME=1 -s WASM=1 -o ldpc-wasm.html --preload-file ./randfile


clean:
	rm -f *.o *-asm.data *-asm.js *-asm.html *-wasm.data *-wasm.html *-wasm.js *-wasm.wasm