#pragma once

// Var represents a single variable.
// If the adress is the same, then two variables are the same
// otherwise, they are different, even if they names are the same

#include "Node.h"

class Var : public Node {
    string variable;

    public:

    Var(string var): variable(var) {
        _entName = "Var"; 
    }

    void *operator new (size_t n, Pool *pool);
    void operator delete (void* ptr, Pool *pool);

    // functions for visual representing of expression
    void get_expression(ostream &out, string wrapEntity);
    vector<string> get_tree_view(int shift);

    // reduction related functions
    Node *reduce(Pool *pool);
    Node *substitute(Pool *pool, Node *substituteTo, Var *substituteThis);
    bool is_redex();

    Var *copy(Pool *pool);
};
