#pragma once

// App representin application from lambda calculus
// a b, where a - leftFunction, b - rightFunction

#include "Node.h"
//Var included, because Abs need to know its methods and attributes
#include "Var.h"

class App : public Node {
    Node *leftFunction;
    Node *rightFunction;

    public:

    App(Node *lfunc, Node *rfunc): leftFunction(lfunc), rightFunction(rfunc) {
        _entName = "App";
    }

    void *operator new (size_t n, Pool *pool);

    // functions for visual representing of expression
    std::string get_expression(std::string wrapEntity);
    std::vector<std::string> get_tree_view(int shift = 0);

    // reduction related functions
    Node *reduce(Pool *pool);
    Node *substitute(Pool *pool, Node *substituteTo, Var *substituteThis);
    bool is_redex();

    App *copy(Pool *pool);
};


