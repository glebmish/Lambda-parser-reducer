#pragma once

#include <cstddef>
#include <cstdlib>
#include <stack>
#include <iostream>
using namespace std;

#define BLOCK_SIZE 128
#define MAX_BLOCKS 2

class PoolBlock {
    public:
        static int blocksInMemory;

        PoolBlock* next;
        char* shift;
        char* data;

        PoolBlock();

        ~PoolBlock();
};

class Pool {
    public:
        PoolBlock* cur;
        int blockCt;

        Pool(): cur(NULL), blockCt(0) {}

        void* palloc(size_t n);

        ~Pool() {delete cur;}
};
