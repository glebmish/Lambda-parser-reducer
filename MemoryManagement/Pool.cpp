#include <cstdlib>
#include <iostream>

#include "Pool.h"
using namespace std;

TooMuchBlocksException::TooMuchBlocksException(int maxB, int curB): maxBlocks(maxB), curBlocks(curB) {}

void TooMuchBlocksException::print() {
    cout << "Pool error: too much blocks allocated\n";
    cout << "Maximum: " << maxBlocks << "   Allocated: " << curBlocks << endl;
}
   
int PoolBlock::blocksInMemory = 0;

PoolBlock::PoolBlock() {
    blocksInMemory++;

    next = NULL;
    allocatedSpaceBegin = (char*) malloc(BLOCK_SIZE);
    freeChunkBegin = allocatedSpaceBegin;
}

PoolBlock::~PoolBlock() {
    blocksInMemory--;
    
    delete next;
}

Pool::Pool(): currentBlock(NULL), blocksCounter(0) {}

void * Pool::palloc(size_t n) {
    // check if it's enough space in current block for new chunk
    if (currentBlock == NULL || currentBlock->freeChunkBegin + n >= currentBlock->allocatedSpaceBegin + BLOCK_SIZE) {
        PoolBlock* newBlock = new PoolBlock();
        ++blocksCounter;

        if (blocksCounter > POOL_MAX_BLOCKS)
            throw TooMuchBlocksException(POOL_MAX_BLOCKS, PoolBlock::blocksInMemory);

        newBlock->next = currentBlock;
        currentBlock = newBlock;
    }

    void *allocatedChunk = currentBlock->freeChunkBegin;
    currentBlock->freeChunkBegin += n;

    return allocatedChunk;
}

Pool::~Pool() {
    delete currentBlock;
}
