#pragma once

#include <string>
#include <iostream>
#include <list>
#include <vector>
#include <cstdlib>
using namespace std;

#include "Node.h"
#include "Var.h"

class Abs : public Node {
    Var *argument;
    Node *function;

    public:

    Abs(Var *arg, Node *func): argument(arg), function(func) {
        _entName = "Abs";
    }

    void *operator new (size_t n, Pool *pool);
    void operator delete (void* ptr, Pool *pool);

    void get_expression(ostream &out, string wrapEntity, Position position);
    vector<string> get_tree_view(int shift);

    Node *reduce(Pool *pool);
    bool isredex();
    Node *substitute(Pool *pool, int free, int who, Node *with );
    Node *changeprior(Pool *pool, int prior, map<int, int> m = map<int,int>());

    Node *copy(Pool *pool);

    ~Abs();
};


