#pragma once

// Abs representing abstraction from lambda calculus
// \x.y, where x - argument, y - function

#include "Node.h"
//Var included, because Abs need to know its methods and attributes
#include "Var.h"

class Abs : public Node {
    Var *argument;
    Node *function;

    public:

    Abs(Var *arg, Node *func): argument(arg), function(func) {
        _entName = "Abs";
    }

    void *operator new (size_t n, Pool *pool);

    // functions for visual representing of expression
    std::string get_expression(std::string wrapEntity);
    std::vector<std::string> get_tree_view(int shift);

    // reduction related functions
    Node *reduce(Pool *pool);
    Node *substitute(Pool *pool, Node *substituteTo, Var *substituteThis);
    bool is_redex();

    Abs *copy(Pool *pool);
};


