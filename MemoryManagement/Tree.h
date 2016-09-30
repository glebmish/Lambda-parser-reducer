#pragma once

#include <vector>
#include <string>

#include "../Entities/Node.h"
#include "Pool.h"

class Tree {
    Pool* pool;
    Node* parsedExpression;

    bool is_full_pool();
    void refresh_pool();
    void clean();

    public:

    Tree(Pool* p, Node* exp): pool(p), parsedExpression(exp) {}

    std::string get_expression();
    std::vector<std::string> get_tree_view();

    void reduce();
    bool is_redex();
};
