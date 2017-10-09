var LDPC = {
    encode: function(message, parityLength,
            // optional parameters
            parityMatrixCreationMethod, checksPerColumnOrCheckDistribution, randomSeed, avoid4Cycles, sparseLuStrategy) {
        parityMatrixCreationMethod = parityMatrixCreationMethod || LDPC.PARITY_MATRIX_CREATION_EVENBOTH;
        checksPerColumnOrCheckDistribution = checksPerColumnOrCheckDistribution || '3';
        randomSeed = randomSeed || LDPC.RANDOM_SEED;
        avoid4Cycles = avoid4Cycles || 1; // true
        sparseLuStrategy = sparseLuStrategy || LDPC.GENERATOR_MATRIX_CREATION_LU_STRATEGY_MINPROD;

        // single bits represented as chars
        var messageLength = message.length;
        var encodedLength = messageLength + parityLength;
        var messagePointer = Module._malloc(messageLength);
        var encodedMessagePointer = Module._malloc(encodedLength);
        var messageBuffer = new Int8Array(Module.HEAP8.buffer, Module.HEAP8.byteOffset + messagePointer, messageLength);
        var encodedMessageBuffer = new Int8Array(Module.HEAP8.buffer, Module.HEAP8.byteOffset + encodedMessagePointer, encodedLength);
        // Copy message to memory.
        for (var i=0; i<messageLength; ++i) {
            messageBuffer[i] = message[i];
        }
        Module.ccall('encode', null, [
            'number', // message pointer
            'number', // message length
            'number', // parity length
            'number', // parity matrix creation method
            'string', // checks_per_col_or_check_distribution, e.g. "3" or "0.3x2/0.6x3/0.1x7"
            'number', // random seed
            'number', // avoid 4 cycles?
            'number', // sparse LU strategy
            'number'  // pointer where to write encoded message
        ], [
            messagePointer,
            messageLength,
            parityLength,
            parityMatrixCreationMethod,
            checksPerColumnOrCheckDistribution,
            randomSeed,
            avoid4Cycles,
            sparseLuStrategy,
            encodedMessagePointer
        ]);
        // copy the result before we free the memory
        var result = new Int8Array(encodedMessageBuffer);
        Module._free(messagePointer);
        Module._free(encodedMessagePointer);
        return result;
    },

    decode: function(receivedData, messageLength, parityLength,
            // optional parameters
            channelType, channelCharacteristic, maxIterations, parityMatrixCreationMethod, checksPerColumnOrCheckDistribution, randomSeed, avoid4Cycles, sparseLuStrategy) {
        channelType = channelType || LDPC.CHANNEL_BINARY_SYMMETRIC;
        channelCharacteristic = channelCharacteristic || 0.1; // for a binary symmetric channel: bit error probability
        maxIterations = maxIterations || LDPC.DECODING_MAX_ITERATIONS;
        parityMatrixCreationMethod = parityMatrixCreationMethod || LDPC.PARITY_MATRIX_CREATION_EVENBOTH;
        checksPerColumnOrCheckDistribution = checksPerColumnOrCheckDistribution || '3';
        randomSeed = randomSeed || LDPC.RANDOM_SEED;
        avoid4Cycles = avoid4Cycles || 1; // true
        sparseLuStrategy = sparseLuStrategy || LDPC.GENERATOR_MATRIX_CREATION_LU_STRATEGY_MINPROD;
        
        var bytesPerDouble = 8;
        var dataLength = receivedData.length;
        var receivedDataByteLength = dataLength * bytesPerDouble; // doubles
        var receivedDataPointer = Module._malloc(receivedDataByteLength);
        var decodedMessagePointer = Module._malloc(messageLength); // chars
        var decodedMessageBuffer = new Uint8Array(Module.HEAPU8.buffer, Module.HEAPU8.byteOffset + decodedMessagePointer, messageLength);
        // Copy received data to memory.
        // Use a DataView to ensure little endianess which is always used by Webassembly regardless
        // of the endianness of the system. The pointers we got are byte aligned.
        var receivedDataView = new DataView(Module.HEAP8.buffer, Module.HEAP8.byteOffset + receivedDataPointer,
            receivedDataByteLength);
        for (var i=0; i<dataLength; ++i) {
            receivedDataView.setFloat64(i * bytesPerDouble, receivedData[i], true);
        }
        Module.ccall('decode', null, [
            'number', // received data pointer
            'number', // message length
            'number', // parity length
            'number', // channel type
            'number', // channel characteristic
            'number', // max iterations
            'number', // parity matrix creation method
            'string', // checks_per_col_or_check_distribution, e.g. "3" or "0.3x2/0.6x3/0.1x7"
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
            checksPerColumnOrCheckDistribution,
            randomSeed,
            avoid4Cycles,
            sparseLuStrategy,
            decodedMessagePointer
        ]);
        // copy result before we free the memory
        var result = new Uint8Array(decodedMessageBuffer);
        Module._free(receivedDataPointer);
        Module._free(decodedMessagePointer);
        return result;
    }
};

// see http://radfordneal.github.io/LDPC-codes/encoding.html#make-gen
LDPC.PARITY_MATRIX_CREATION_EVENCOL = 0;
LDPC.PARITY_MATRIX_CREATION_EVENBOTH = 1; 

// see http://radfordneal.github.io/LDPC-codes/sparse-LU.html
LDPC.GENERATOR_MATRIX_CREATION_LU_STRATEGY_FIRST = 0;
LDPC.GENERATOR_MATRIX_CREATION_LU_STRATEGY_MINCOL = 1;
LDPC.GENERATOR_MATRIX_CREATION_LU_STRATEGY_MINPROD = 2;

LDPC.CHANNEL_BINARY_SYMMETRIC = 0;
LDPC.CHANNEL_ADDITIVE_WHITE_GAUSSIAN_NOISE = 1;
LDPC.CHANNEL_ADDITIVE_WHITE_LOGISTIC_NOISE = 2;

LDPC.RANDOM_SEED = 42;

LDPC.DECODING_MAX_ITERATIONS = 100;