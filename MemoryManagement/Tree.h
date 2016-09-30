#pragma once

#include "../Entities/Node.h"
#include "Pool.h"

class Tree {
    Pool* pool;
    Node* parsedExpression;

    public:

    Tree(Pool* p, Node* exp): pool(p), parsedExpression(exp) {}

    bool is_full_pool();
    void refresh_pool();
    void clean();

    void get_expression(std::ostream& out);
    void get_tree_view(std::ostream& out);

    void reduce();
    bool is_redex();
};
