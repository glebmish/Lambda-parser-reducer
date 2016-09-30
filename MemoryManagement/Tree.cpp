#include <string>
#include <vector>
using namespace std;

#include "Tree.h"

bool Tree::is_full_pool() {
    return pool->blocksCounter >= POOL_MAX_BLOCKS;
}

void Tree::refresh_pool() {
    Pool *newPool = new Pool();
    Node *newParsedExpression = parsedExpression->copy(newPool);

    delete pool;

    pool = newPool;
    parsedExpression = newParsedExpression;
}

void Tree::clean() {
    delete pool;

    pool = NULL;
    parsedExpression = NULL;
}

void Tree::get_expression(ostream& out) {
    parsedExpression->get_expression(out);
}

void Tree::get_tree_view(ostream& out) {
    vector<string> tree_view = parsedExpression->get_tree_view();

    for (size_t i = 0; i < tree_view.size(); i++)
        out << tree_view[i] << endl;
}

void Tree::reduce() {
    parsedExpression = parsedExpression->reduce(pool);

    if (is_full_pool())
        refresh_pool();
}

bool Tree::is_redex() {
    return parsedExpression->is_redex();
}
