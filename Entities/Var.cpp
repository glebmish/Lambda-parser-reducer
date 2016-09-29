#include <sstream>
#include "Var.h"
using namespace std;

void *Var::operator new (size_t n, Pool *pool) {
    return pool -> palloc(sizeof(Var));
}

void Var::operator delete(void* ptr, Pool *pool) {
    free(ptr);
}

void Var::get_expression(ostream &out, string wrapEntity) {
    out << variable;
}

vector<string> Var::get_tree_view(int shift) {
    stringstream convert;
    convert << this;

    vector<string> treeAll;
    treeAll.push_back(string(shift, ' ') + variable + ' ' + convert.str() + ' ');

    return treeAll;
}

Node *Var::reduce(Pool *pool) {
    return this;
}

Node *Var::substitute(Pool *pool, Node *substituteTo, Var *substituteThis) {
    if (this == substituteThis)
        return substituteTo->copy(pool);
    else
        return this;
}

bool Var::is_redex() {
    return false;
}

Var *Var::copy(Pool *pool) {
    return this;
}


