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

    out << s;
}

vector<string> Var::get_tree_view(int shift) {
    vector<string> treeAll;
    treeAll.push_back(string(shift, ' ') + char('0' + s));

    return treeAll;
}

string Var::saymyname() {
    return "Var";
}

int Var::getvalue() {
    return s;
}

Node *Var::reduce(Pool *pool) {
    return this;
}

bool Var::isredex() {
    return false;
}

Node *Var::substitute(Pool *pool, int free, int who, Node *with) {
    if (s == who)
        return with -> changeprior(pool, free);
    else
        if (s > 0)
            return new(pool) Var(s - 1);
        else return new(pool) Var(s);
}

Node *Var::changeprior(Pool *pool, int prior, map<int, int> m) {
    int newl;
    if (s < 0)
        newl = s;
    else
        if (m.count(s))
            newl = m[s];
        else m[s] = newl = prior, prior++;

    return new(pool) Var(newl);
}

Node *Var::copy(Pool *pool) {
    return new(pool) Var(s);
}


