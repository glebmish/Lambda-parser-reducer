#include "Abs.h"
using namespace std;

void *Abs::operator new (size_t n, Pool *pool) {
    return pool->palloc(n);
}

void Abs::operator delete(void *ptr){
    free(ptr);
}

void Abs::get_expression(ostream& out, string wrapEntity) {
    // when in application, abstraction should be wrapped in brackets
    // example: a (\x.x) b
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
    // newShift will point here:
    // Abs/-- 
    //        ^
    int newShift = shift + _entName.size() + _horizontalFirst.size() + 1;

    // process argument of abstraction
    vector<string> treeBegin = argument->get_tree_view(newShift);
    
    // add "Abs/-- " to already processed argument
    //     "   |   "
    treeBegin[0].replace(shift, _entName.size() + _horizontalFirst.size() + 1, _entName + _horizontalFirst + ' ');
    treeBegin.push_back(string(shift + _entName.size(), ' ') + _vertical);
    
    // process function of abstraction
    vector<string> treeEnd = function->get_tree_view(newShift);
    
    // add "   \__" to already processed function
    treeEnd[0].replace(shift + _entName.size(), _horizontalSecond.size(), _horizontalSecond);

    // merge parts of result
    treeBegin.insert(treeBegin.end(), treeEnd.begin(), treeEnd.end());

    return treeBegin;
}

Node *Abs::reduce(Pool *pool) {
    return new(pool) Abs(argument, function->reduce(pool));
}

Node *Abs::substitute(Pool *pool, Node *substituteTo, Var *substituteThis) {
    // (\x.x) y
    //     ^  ^
    //     |  \_substituteTo
    //     |
    // substituteThis

    // substituteThis == NULL when this abstraction is starting point of reduction
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
