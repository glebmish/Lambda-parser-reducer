#pragma once

#include "Node.h"
#include "Var.h"

class App : public Node {
    Node *leftFunction;
    Node *rightFunction;

    public:

    App(Node *lfunc, Node *rfunc): leftFunction(lfunc), rightFunction(rfunc) {
        _entName = "App";
    }

    void *operator new (size_t n, Pool *pool);
    void operator delete (void *ptr, Pool *pool);

    void get_expression(ostream &out, string wrapEntity);
    vector<string> get_tree_view(int shift = 0);

    Node *reduce(Pool *pool);
    Node *substitute(Pool *pool, Node *substituteTo, Var *substituteThis);
    bool is_redex();

    App *copy(Pool *pool);

    ~App();
};


