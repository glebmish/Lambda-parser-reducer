#include "App.h"
using namespace std;

void *App::operator new (size_t n, Pool *pool) {
    return pool -> palloc(n);
}

void App::operator delete(void* ptr) {
    free(ptr);
}

void App::get_expression(ostream& out, string wrapEntity) {
    // when leftFuntion is abstraction, application should be wrapped in brackets
    // example: a ((\x.x) b) c
    if (leftFunction->_entName == "Abs")
        out << '(';

    leftFunction -> get_expression(out, _entName);
    out << ' ';
    rightFunction -> get_expression(out, _entName);
    
    if (leftFunction->_entName == "Abs")
        out << ')';
}

vector<string> App::get_tree_view(int shift) {
    // newShift will point here:
    // App/-- 
    //        ^
    int newShift = shift + _entName.size() + _horizontalFirst.size() + 1;

    // process left function of abstraction
    vector<string> treeBegin = leftFunction->get_tree_view(newShift);
    
    //  add "/-- " to already processed left function
    //      "|   "
    //      ......
    //      "|   "
    treeBegin[0].replace(shift, _entName.size() + _horizontalFirst.size() + 1, _entName + _horizontalFirst + ' ');
    for (int i = 1; i < treeBegin.size(); i++)
        treeBegin[i].replace(shift + _entName.size(), _vertical.size(), _vertical);
    treeBegin.push_back(string(shift + _entName.size(), ' ') + _vertical);
    
    // process right function of abstraction
    vector<string> treeEnd = rightFunction->get_tree_view(newShift);

    // add "\__ " to already processed right function
    treeEnd[0].replace(shift + _entName.size(), _horizontalSecond.size(), _horizontalSecond);
    
    //merge parts of result
    treeBegin.insert(treeBegin.end(), treeEnd.begin(), treeEnd.end());

    return treeBegin;
}
    
Node *App::reduce(Pool *pool) {
    // if leftFunction is abstraction,
    // this abstraction will be the entry point of reduction
    if (leftFunction->_entName == "Abs") {
        return leftFunction->substitute(pool, rightFunction);
    } else {
        // this if used to ensure that it will be only one reduction at a time
        if (rightFunction->is_redex())
            return new(pool) App(leftFunction->copy(pool), rightFunction->reduce(pool));
        else
            return new(pool) App(leftFunction->reduce(pool), rightFunction->copy(pool));
    }
}

Node *App::substitute(Pool *pool, Node *substituteTo, Var *substituteThis) {
    // (\x.x) y
    //     ^  ^
    //     |  \_substituteTo
    //     |
    // substituteThis


    return new(pool) App(leftFunction -> substitute(pool, substituteTo, substituteThis), 
                        rightFunction -> substitute(pool, substituteTo, substituteThis));
}

bool App::is_redex() {
    if (leftFunction->_entName == "Abs") 
        return true;
    else
        return leftFunction->is_redex() || rightFunction->is_redex();
}

App *App::copy (Pool *pool) {
    return new(pool) App(leftFunction -> copy(pool), rightFunction -> copy(pool));
}

App::~App() {
    delete leftFunction; 
    delete rightFunction;
}
