#pragma once

#include <string>
#include <iostream>
#include <streambuf>
#include <fstream>
#include <vector>
#include <cstdlib>
using namespace std;

#include "Node.h"

class Var : public Node {
    int variable;

    public:

    Var(int var): variable(var) {
        _entName = "Var"; 
    }

    void *operator new (size_t n, Pool *pool);
    void operator delete (void* ptr, Pool *pool);

    void get_expression(ostream &out, string wrapEntity, Position position);
    vector<string> get_tree_view(int shift);

    int getvalue();

    Node *reduce(Pool *pool);
    bool isredex();
    Node *substitute(Pool *pool, int free, int who, Node *with);
    Node *changeprior(Pool *pool, int prior, map<int, int> m = map<int,int>());

    Node *copy(Pool *pool);
};
