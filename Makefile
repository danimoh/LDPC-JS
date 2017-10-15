# compile using emscripten
COMPILE_EMCC = emcc -c -O    # Command to compile a module from .c to .o
LINK_EMCC =    emcc          # Command to link a program


# MAKE ALL THE MAIN PROGRAMS.  First makes the modules used.

emcc:
	$(COMPILE_EMCC) globals.c
	$(COMPILE_EMCC) alloc.c
	$(COMPILE_EMCC) mod2sparse.c
	$(COMPILE_EMCC) distrib.c
	$(COMPILE_EMCC) rand.c
	$(COMPILE_EMCC) parity-matrix-creation.c
	$(COMPILE_EMCC) generator-matrix-creation.c
	$(COMPILE_EMCC) check.c
	$(COMPILE_EMCC) enc.c
	$(COMPILE_EMCC) dec.c
	$(COMPILE_EMCC) encode.c
	$(COMPILE_EMCC) decode.c
	$(COMPILE_EMCC) test.c
	# compile to asm.js (might want to add ONLY_MY_CODE=1, see https://github.com/kripken/emscripten/issues/3955)
	$(LINK_EMCC) -O3 parity-matrix-creation.o generator-matrix-creation.o mod2sparse.o \
	   rand.o alloc.o globals.o distrib.o check.o enc.o dec.o encode.o decode.o test.o -lm \
	   -s EXPORTED_FUNCTIONS='["_encode","_decode"]' -s NO_EXIT_RUNTIME=1 -s MODULARIZE=1 \
	   -s EXPORT_NAME="'LDPC_HANDLER'" -s EXPORTED_RUNTIME_METHODS='["ccall"]' \
	   -s LIBRARY_DEPS_TO_AUTOEXPORT='[]' -s DEFAULT_LIBRARY_FUNCS_TO_INCLUDE="[]" \
	   -s NO_FILESYSTEM=1 -s DISABLE_EXCEPTION_CATCHING=1 -s ELIMINATE\_DUPLICATE\_FUNCTIONS=1 \
	   --closure 1 \
	   -o dist/ldpc-asm.html
	# compile to wasm
	$(LINK_EMCC) -O3 parity-matrix-creation.o generator-matrix-creation.o mod2sparse.o \
	   rand.o alloc.o globals.o distrib.o check.o enc.o dec.o encode.o decode.o test.o -lm \
	   -s EXPORTED_FUNCTIONS='["_encode","_decode"]' -s NO_EXIT_RUNTIME=1 -s MODULARIZE=1 \
	   -s EXPORT_NAME="'LDPC_HANDLER'" -s EXPORTED_RUNTIME_METHODS='["ccall"]' \
	   -s LIBRARY_DEPS_TO_AUTOEXPORT='[]' -s DEFAULT_LIBRARY_FUNCS_TO_INCLUDE="[]" \
	   -s NO_FILESYSTEM=1 -s DISABLE_EXCEPTION_CATCHING=1 \
	   -s WASM=1 --closure 1 \
	   -o dist/ldpc-wasm.html
	rm -f *.o

clean:
	rm -f *.o dist/*-asm.data dist/*-asm.js dist/*-asm.html dist/*-wasm.data dist/*-wasm.html dist/*-wasm.js dist/*-wasm.wasm