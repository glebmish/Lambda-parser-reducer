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
    string variable;

    public:

    Var(string var): variable(var) {
        _entName = "Var"; 
    }

    void *operator new (size_t n, Pool *pool);
    void operator delete (void* ptr, Pool *pool);

    void get_expression(ostream &out, string wrapEntity, Position position);
    vector<string> get_tree_view(int shift);

    Node *reduce(Pool *pool);
    Node *substitute(Pool *pool, Node *substituteTo, Var *substituteThis);
    bool is_redex();

    Var *copy(Pool *pool);
};
