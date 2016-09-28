#include "Abs.h"

void *Abs::operator new (size_t n, Pool *pool) {
    return pool -> palloc(sizeof(Abs));
}

void Abs::operator delete(void *ptr, Pool *pool){
    free(ptr);
}

void Abs::get_expression(ostream& out, string wrapEntity, Position position) {
    if (wrapEntity == "App") 
        out << '(';
    
    out << '\\';
    out << l;
    out << '.';
    
    r -> get_expression(out, _entName, _left);
    
    if (wrapEntity == "App")
        out << ')';
}

vector<string> Abs::get_tree_view(int shift) {
    vector<string> treeBegin;
    treeBegin.push_back(string(shift, ' ') + _entName + _horizontalFirst + char('0' + l));
    treeBegin.push_back(string(shift + _entName.size(), ' ') + _vertical);
    
    int newShift = shift + _entName.size() + _horizontalFirst.size() + 1;
    vector<string> treeEnd = r->get_tree_view(newShift);

    treeEnd[0].replace(shift + _entName.size(), _horizontalSecond.size(), _horizontalSecond);
    treeBegin.insert(treeBegin.end(), treeEnd.begin(), treeEnd.end());

    return treeBegin;
}

string Abs::saymyname() {
    return "Abs";
}

int Abs::getvalue() {
    return l;
}

Node *Abs::reduce(Pool *pool) {
    return new(pool) Abs(l, r -> reduce(pool));
}

bool Abs::isredex() {
    return r -> isredex();
}

Node *Abs::substitute(Pool *pool, int free, int who, Node *with) {
    if (who == 0)
        return r -> substitute(pool, l, l, with);
    else
        return new(pool) Abs(free, r -> substitute(pool, free + 1, who, with));
}

Node *Abs::changeprior(Pool *pool, int prior, map<int, int> m) {
    int newl;
    if (l < 0)
        newl = l;
    else
        if (m.count(l))
            newl = m[l];
        else m[l] = newl = prior, prior++;

    return new(pool) Abs(newl, r -> changeprior(pool, prior, m));
}

Node *Abs::copy (Pool *pool) {
    return new(pool) Abs(l, r -> copy(pool));
}

Abs::~Abs() {
    delete r;
}
