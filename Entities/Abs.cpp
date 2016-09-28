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
    argument->get_expression(out, _entName, position);
    out << '.';
    
    function -> get_expression(out, _entName, _left);
    
    if (wrapEntity == "App")
        out << ')';
}

vector<string> Abs::get_tree_view(int shift) {
    int newShift = shift + _entName.size() + _horizontalFirst.size() + 1;
    vector<string> treeBegin = argument->get_tree_view(newShift);
    
    treeBegin[0].replace(shift, _entName.size() + _horizontalFirst.size() + 1, _entName + _horizontalFirst + ' ');
    treeBegin.push_back(string(shift + _entName.size(), ' ') + _vertical);
    
    vector<string> treeEnd = function->get_tree_view(newShift);

    treeEnd[0].replace(shift + _entName.size(), _horizontalSecond.size(), _horizontalSecond);
    treeBegin.insert(treeBegin.end(), treeEnd.begin(), treeEnd.end());

    return treeBegin;
}

Node *Abs::reduce(Pool *pool) {
    return new(pool) Abs(variable, function -> reduce(pool));
}

bool Abs::isredex() {
    return function -> isredex();
}

Node *Abs::substitute(Pool *pool, int free, int who, Node *with) {
    if (who == 0)
        return function -> substitute(pool, variable, variable, with);
    else
        return new(pool) Abs(free, function -> substitute(pool, free + 1, who, with));
}

Node *Abs::changeprior(Pool *pool, int prior, map<int, int> m) {
    int newvar;
    if (variable < 0)
        newvar = variable;
    else
        if (m.count(variable))
            newvar = m[variable];
        else m[variable] = newvar = prior, prior++;

    return new(pool) Abs(newvar, function -> changeprior(pool, prior, m));
}

Abs *Abs::copy (Pool *pool) {
    return new(pool) Abs(argument->copy(pool), function -> copy(pool));
}

Abs::~Abs() {
    delete function;
}
