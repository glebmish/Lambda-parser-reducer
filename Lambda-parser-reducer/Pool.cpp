#include "Pool.h"

int PoolBlock::blocksInMemory = 0;

PoolBlock::PoolBlock() {
    blocksInMemory++;
    next = NULL;
    data = (char*) malloc(BLOCK_SIZE);
    shift = data;
}

PoolBlock::~PoolBlock() {
    blocksInMemory--;
    if (next != NULL)
        delete next;
}

void * Pool::palloc(size_t n) {
    if (cur == NULL || cur -> shift + n >= cur -> data + BLOCK_SIZE) {
        blockCt++;
        if (blockCt > MAX_BLOCKS + 1) cout << "Too much blocks\n";
        PoolBlock* newBlock = new PoolBlock();
        newBlock -> next = cur;
        cur = newBlock;
    }
    void* res = cur -> shift;
    cur -> shift += n;
    return res;
}
