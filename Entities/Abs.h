#pragma once

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

    void get_expression(std::ostream &out, std::string wrapEntity, Position position);
    std::vector<string> get_tree_view(int shift);

    Node *reduce(Pool *pool);
    Node *substitute(Pool *pool, Node *substituteTo, Var *substituteThis);
    bool is_redex();

    Abs *copy(Pool *pool);

    ~Abs();
};


