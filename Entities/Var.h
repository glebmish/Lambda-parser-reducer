#pragma once

#include <string>
#include <iostream>
#include <streambuf>
#include <fstream>
using namespace std;

#include "Node.h"

class Var : public Node {
    int s;

    public:

    Var(int ss): s(ss) {}

    void *operator new (size_t n, Pool *pool);
    void operator delete (void* ptr, Pool *pool);

    void getexp(ostream &out, bool isapp, bool isleft);
    void gettree(ostream &out, bool isDebug = 0, int = 0, list<int> = list<int>());

    string saymyname();
    int getvalue();

    Node *reduce(Pool *pool);
    bool isredex();
    Node *substitute(Pool *pool, int, int, Node*);
    Node *changeprior(Pool *pool, int, map<int, int> = map<int,int>());

    Node *copy(Pool *pool);
};
