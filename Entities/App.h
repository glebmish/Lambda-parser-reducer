#pragma once

#include<iostream>
#include <string>
#include <vector>
using namespace std;

#include "Node.h"

class App : public Node {
    Node *l;
    Node *r;

    public:

    App(Node *ll, Node *rr): l(ll), r(rr) {
        _entName = "App";
    }

    void *operator new (size_t n, Pool *pool);
    void operator delete (void *ptr, Pool *pool);

    void get_expression(ostream &out, string wrapEntity, Position position);
    vector<string> get_tree_view(int shift = 0);

    string saymyname();
    int getvalue();

    Node *reduce(Pool *pool);
    bool isredex();
    Node *substitute(Pool *pool, int free, int who, Node* with);
    Node *changeprior(Pool *pool, int prior, map<int, int> m = map<int,int>());

    Node *copy(Pool *pool);

    ~App();
};


