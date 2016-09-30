#pragma once

#include <cstddef>

#define BLOCK_SIZE 128
#define POOL_MAX_BLOCKS 16

class TooMuchBlocksException {
    int maxBlocks;
    int curBlocks;

    public:
    TooMuchBlocksException(int maxB, int curB);

    void print();
};

class PoolBlock {
    public:
        // every new block increments this counter
        // every deleted block decrements this counter
        // should be 0 when deleted all parsed expressions
        static int blocksInMemory;

        PoolBlock* next;
        char* allocatedSpaceBegin;
        char* freeChunkBegin;

        PoolBlock();

        ~PoolBlock();
};

class Pool {
    public:
        PoolBlock* currentBlock;
        int blocksCounter;

        Pool();
        void* palloc(std::size_t n);

        ~Pool();
};
