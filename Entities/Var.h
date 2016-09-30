#pragma once

// Var represents a single variable.
// If the adress is the same, then two variables are the same
// otherwise, they are different, even if they names are the same

#include "Node.h"

class Var : public Node {
    std::string variable;

    public:

    Var(std::string var): variable(var) {
        _entName = "Var"; 
    }

    void *operator new (size_t n, Pool *pool);

    // functions for visual representing of expression
    std::string get_expression(std::string wrapEntity);
    std::vector<std::string> get_tree_view(int shift);

    // reduction related functions
    Node *reduce(Pool *pool);
    Node *substitute(Pool *pool, Node *substituteTo, Var *substituteThis);
    bool is_redex();

    Var *copy(Pool *pool);
};
