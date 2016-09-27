#include <string>
#include <vector>
using namespace std;

#include "Tree.h"

bool Tree::is_full_pool() {
    return pool -> blockCt >= MAX_BLOCKS;
}

void Tree::refresh_pool() {
    Pool* newPool =  new Pool();
    Node* newTree = tree -> copy(newPool);
    delete pool;
    pool = newPool;
    tree = newTree;
}

void Tree::clean() {
    delete pool;
    pool = NULL;
    tree = NULL;
}

void Tree::debug_inf() {
    cout << pool -> blockCt << " ";
    cout << pool -> cur -> shift - pool -> cur -> data << " ";
    cout << pool -> cur << " ";
    cout << pool -> cur -> next << endl;
}

void Tree::getexp(ostream& out) {
    tree -> get_expression(out);
}

void Tree::gettree(ostream& out) {
    vector<string> tree_view = tree->get_tree_view();
    for (int i = 0; i < tree_view.size(); i++)
        out << tree_view[i] << endl;
}

void Tree::reduce() {
    tree = tree -> reduce(pool);
    if (is_full_pool())
        refresh_pool();
}

bool Tree::isredex() {
    return tree -> isredex();
}
