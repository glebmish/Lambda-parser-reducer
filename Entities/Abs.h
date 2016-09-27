#pragma once

#include <string>
#include <iostream>
#include <list>
using namespace std;

#include "Node.h"

class Abs : public Node {
    int l;
    Node *r;


    public:

    Abs(int ll, Node *rr): l(ll), r(rr) {}

    void *operator new (size_t n, Pool *pool);
    void operator delete (void* ptr, Pool *pool);

    void getexp(ostream &out, bool isapp, bool isleft);
    void gettree(ostream &out, int shift = 0, list<int> l = list<int>());

    string saymyname();
    int getvalue();

    Node *reduce(Pool *pool);
    bool isredex();
    Node *substitute(Pool *pool, int free, int who, Node *with );
    Node *changeprior(Pool *pool, int prior, map<int, int> m = map<int,int>());

    Node *copy(Pool *pool);

    ~Abs();
};
