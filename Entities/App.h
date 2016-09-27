#pragma once

#include<iostream>
#include <string>
using namespace std;

#include "Node.h"

class App : public Node {
    Node *l;
    Node *r;


    public:

    App(Node *ll, Node *rr): l(ll), r(rr) {}

    void *operator new (size_t n, Pool *pool);
    void operator delete (void *ptr, Pool *pool);

    void getexp(ostream &out, bool isapp = false, bool isleft = false);
    void gettree(ostream &out, int shift = 0, list<int> l = list<int>());

    string saymyname();
    int getvalue();

    Node *reduce(Pool *pool);
    bool isredex();
    Node *substitute(Pool *pool, int free, int who, Node* with);
    Node *changeprior(Pool *pool, int prior, map<int, int> m = map<int,int>());

    Node *copy(Pool *pool);

    ~App();
};
