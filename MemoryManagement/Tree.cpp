#include "Tree.h"
using namespace std;

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

string Tree::get_expression() {
    return parsedExpression->get_expression();
}

vector<string> Tree::get_tree_view() {
    return parsedExpression->get_tree_view();
}

void Tree::reduce() {
    parsedExpression = parsedExpression->reduce(pool);

    if (is_full_pool())
        refresh_pool();
}

bool Tree::is_redex() {
    return parsedExpression->is_redex();
}
