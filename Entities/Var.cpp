#include "Var.h"

void *Var::operator new (size_t n, Pool *pool) {
    return pool -> palloc(sizeof(Var));
}

void Var::operator delete(void* ptr, Pool *pool) {
    free(ptr);
}

void Var::get_expression(ostream &out, string wrapEntity, Position position) {
    if (wrapEntity == "App" && position == _right)
        out << ' ';

    out << variable;
}

vector<string> Var::get_tree_view(int shift) {
    vector<string> treeAll;
    treeAll.push_back(string(shift, ' ') + char('0' + variable));

    return treeAll;
}

int Var::getvalue() {
    return variable;
}

Node *Var::reduce(Pool *pool) {
    return this;
}

bool Var::isredex() {
    return false;
}

Node *Var::substitute(Pool *pool, int free, int who, Node *with) {
    if (variable == who)
        return with -> changeprior(pool, free);
    else
        if (variable > 0)
            return new(pool) Var(variable - 1);
        else return new(pool) Var(variable);
}

Node *Var::changeprior(Pool *pool, int prior, map<int, int> m) {
    int newvar;
    if (variable < 0)
        newvar = variable;
    else
        if (m.count(variable))
            newvar = m[variable];
        else m[variable] = newvar = prior, prior++;

    return new(pool) Var(newvar);
}

Node *Var::copy(Pool *pool) {
    return new(pool) Var(variable);
}


