var LDPC = {
    LDPC_BASE_PATH: window.LDPC_PATH || 'dist/',

    // see http://radfordneal.github.io/LDPC-codes/encoding.html#make-gen
    PARITY_MATRIX_CREATION_EVENCOL: 0,
    PARITY_MATRIX_CREATION_EVENBOTH: 1, 

    // see http://radfordneal.github.io/LDPC-codes/sparse-LU.html
    GENERATOR_MATRIX_CREATION_LU_STRATEGY_FIRST: 0,
    GENERATOR_MATRIX_CREATION_LU_STRATEGY_MINCOL: 1,
    GENERATOR_MATRIX_CREATION_LU_STRATEGY_MINPROD: 2,

    CHANNEL_BINARY_SYMMETRIC: 0,
    CHANNEL_ADDITIVE_WHITE_GAUSSIAN_NOISE: 1,
    CHANNEL_ADDITIVE_WHITE_LOGISTIC_NOISE: 2,

    RANDOM_SEED: 42,

    DECODING_MAX_ITERATIONS: 100,

    _handler: null,
    _handlerPromise: null,
    _awaitHandler: function() {
        if (!LDPC._handlerPromise) {
            LDPC._handlerPromise = new Promise(function(resolve, reject) {
                // load the handler
                var script = document.createElement('script');
                script.onload = resolve;
                script.onerror = reject;
                script.src = LDPC.LDPC_BASE_PATH + (window.WebAssembly? 'ldpc-wasm.js' : 'ldps-asm.js');
                document.body.appendChild(script);
            }).then(function() {
                return new Promise(function(resolve, reject) {
                    LDPC._handler = LDPC_HANDLER({
                        wasmBinaryFile: LDPC.LDPC_BASE_PATH + 'ldpc-wasm.wasm',
                        filePackagePrefixURL: LDPC.LDPC_BASE_PATH
                    });
                    // wait until the handler is ready
                    LDPC._handler.onRuntimeInitialized = resolve;
                });
            });
        }
        return LDPC._handlerPromise;
    },

    // async
    encode: function(message, parityLength,
            // optional parameters
            parityMatrixCreationMethod, checksPerColumn, randomSeed, avoid4Cycles, sparseLuStrategy) {
        return LDPC._awaitHandler().then(function() {
            parityMatrixCreationMethod = parityMatrixCreationMethod || LDPC.PARITY_MATRIX_CREATION_EVENBOTH;
            checksPerColumn = checksPerColumn || 3;
            randomSeed = randomSeed || LDPC.RANDOM_SEED;
            avoid4Cycles = avoid4Cycles || 1; // true
            sparseLuStrategy = sparseLuStrategy || LDPC.GENERATOR_MATRIX_CREATION_LU_STRATEGY_MINPROD;

            // single bits represented as chars
            var messageLength = message.length;
            var encodedLength = messageLength + parityLength;
            var messagePointer = LDPC._handler._malloc(messageLength);
            var encodedMessagePointer = LDPC._handler._malloc(encodedLength);
            var messageBuffer = new Int8Array(LDPC._handler.HEAP8.buffer, LDPC._handler.HEAP8.byteOffset + messagePointer, messageLength);
            var encodedMessageBuffer = new Int8Array(LDPC._handler.HEAP8.buffer, LDPC._handler.HEAP8.byteOffset + encodedMessagePointer, encodedLength);
            // Copy message to memory.
            for (var i=0; i<messageLength; ++i) {
                messageBuffer[i] = message[i];
            }
            LDPC._handler.ccall('encode', null, [
                'number', // message pointer
                'number', // message length
                'number', // parity length
                'number', // parity matrix creation method
                'number', // checks per column (column weight)
                'number', // random seed
                'number', // avoid 4 cycles?
                'number', // sparse LU strategy
                'number'  // pointer where to write encoded message
            ], [
                messagePointer,
                messageLength,
                parityLength,
                parityMatrixCreationMethod,
                checksPerColumn,
                randomSeed,
                avoid4Cycles,
                sparseLuStrategy,
                encodedMessagePointer
            ]);
            // copy the result before we free the memory
            var result = new Int8Array(encodedMessageBuffer);
            LDPC._handler._free(messagePointer);
            LDPC._handler._free(encodedMessagePointer);
            return result;
        });
    },

    // async
    decode: function(receivedData, messageLength, parityLength,
            // optional parameters
            channelType, channelCharacteristic, maxIterations, parityMatrixCreationMethod, checksPerColumn, randomSeed, avoid4Cycles, sparseLuStrategy) {
        return LDPC._awaitHandler().then(function() {
            channelType = channelType || LDPC.CHANNEL_BINARY_SYMMETRIC;
            channelCharacteristic = channelCharacteristic || 0.1; // for a binary symmetric channel: bit error probability
            maxIterations = maxIterations || LDPC.DECODING_MAX_ITERATIONS;
            parityMatrixCreationMethod = parityMatrixCreationMethod || LDPC.PARITY_MATRIX_CREATION_EVENBOTH;
            checksPerColumn = checksPerColumn || 3;
            randomSeed = randomSeed || LDPC.RANDOM_SEED;
            avoid4Cycles = avoid4Cycles || 1; // true
            sparseLuStrategy = sparseLuStrategy || LDPC.GENERATOR_MATRIX_CREATION_LU_STRATEGY_MINPROD;
            
            var bytesPerDouble = 8;
            var dataLength = receivedData.length;
            var receivedDataByteLength = dataLength * bytesPerDouble; // doubles
            var receivedDataPointer = LDPC._handler._malloc(receivedDataByteLength);
            var decodedMessagePointer = LDPC._handler._malloc(messageLength); // chars
            var decodedMessageBuffer = new Uint8Array(LDPC._handler.HEAPU8.buffer, LDPC._handler.HEAPU8.byteOffset + decodedMessagePointer, messageLength);
            // Copy received data to memory.
            // Use a DataView to ensure little endianess which is always used by Webassembly regardless
            // of the endianness of the system. The pointers we got are byte aligned.
            var receivedDataView = new DataView(LDPC._handler.HEAP8.buffer, LDPC._handler.HEAP8.byteOffset + receivedDataPointer,
                receivedDataByteLength);
            for (var i=0; i<dataLength; ++i) {
                receivedDataView.setFloat64(i * bytesPerDouble, receivedData[i], true);
            }
            LDPC._handler.ccall('decode', null, [
                'number', // received data pointer
                'number', // message length
                'number', // parity length
                'number', // channel type
                'number', // channel characteristic
                'number', // max iterations
                'number', // parity matrix creation method
                'number', // checks per column (column weight)
                'number', // random seed
                'number', // avoid 4 cycles?
                'number', // sparse LU strategy
                'number'  // pointer where to write decoded data
            ], [
                receivedDataPointer,
                messageLength,
                parityLength,
                channelType,
                channelCharacteristic,
                maxIterations,
                parityMatrixCreationMethod,
                checksPerColumn,
                randomSeed,
                avoid4Cycles,
                sparseLuStrategy,
                decodedMessagePointer
            ]);
            // copy result before we free the memory
            var result = new Uint8Array(decodedMessageBuffer);
            LDPC._handler._free(receivedDataPointer);
            LDPC._handler._free(decodedMessagePointer);
            return result;
        });
    }
};