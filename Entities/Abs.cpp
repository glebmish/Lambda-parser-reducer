#include "Abs.h"
using namespace std;

void *Abs::operator new (size_t n, Pool *pool) {
    return pool -> palloc(sizeof(Abs));
}

void Abs::operator delete(void *ptr, Pool *pool){
    free(ptr);
}

void Abs::get_expression(ostream& out, string wrapEntity) {
    if (wrapEntity == "App") 
        out << '(';
    
    out << '\\';
    argument->get_expression(out, _entName);
    out << '.';
    
    function -> get_expression(out, _entName);
    
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
    return new(pool) Abs(argument, function->reduce(pool));
}

Node *Abs::substitute(Pool *pool, Node *substituteTo, Var *substituteThis) {
    if (substituteThis == NULL)
        return function->substitute(pool, substituteTo, argument);
    else 
        return new(pool) Abs(argument, function->substitute(pool, substituteTo, substituteThis));
}

bool Abs::is_redex() {
    return function->is_redex();
}

Abs *Abs::copy (Pool *pool) {
    return new(pool) Abs(argument->copy(pool), function -> copy(pool));
}

Abs::~Abs() {
    delete function;
}
