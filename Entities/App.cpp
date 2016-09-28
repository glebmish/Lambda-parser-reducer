#include "App.h"

void *App::operator new (size_t n, Pool *pool) {
    return pool -> palloc(sizeof(App));
}

void App::operator delete(void* ptr, Pool *pool) {
    free(ptr);
}

void App::get_expression(ostream& out, string wrapEntity, Position position) {
    if (wrapEntity == "App" && position == _left)
        out << '(';
    
    leftFunction -> get_expression(out, _entName, _left);
    rightFunction -> get_expression(out, _entName, _right);
    
    if (wrapEntity == "App" && position == _left) 
        out << ')';
}

vector<string> App::get_tree_view(int shift) {
    vector<string> treeBegin;

    int newShift = shift + _entName.size() + _horizontalFirst.size() + 1;
    vector<string> treeMid = leftFunction->get_tree_view(newShift);

    treeMid[0].replace(shift, _entName.size() + _horizontalFirst.size() + 1, _entName + _horizontalFirst + ' ');
    for (int i = 1; i < treeMid.size(); i++)
        treeMid[i].replace(shift + _entName.size(), _vertical.size(), _vertical);
    
    treeBegin.insert(treeBegin.end(), treeMid.begin(), treeMid.end());
    treeBegin.push_back(string(shift + _entName.size(), ' ') + _vertical);

    vector<string> treeEnd = rightFunction->get_tree_view(newShift);
    treeEnd[0].replace(shift + _entName.size(), _horizontalSecond.size(), _horizontalSecond);

    treeBegin.insert(treeBegin.end(), treeEnd.begin(), treeEnd.end());

    return treeBegin;
}
    
int App::getvalue() {
    return 0;
}

Node *App::reduce(Pool *pool) {
    if (leftFunction -> _entName == "Abs") {
        return leftFunction -> substitute(pool, 0, 0, rightFunction);
    } else {
        return new(pool) App(leftFunction -> reduce(pool), rightFunction -> reduce(pool));
    }
}

bool App::isredex() {
    if (leftFunction -> _entName == "Abs") 
        return true;
    else
        return leftFunction -> isredex() || rightFunction -> isredex();
}

Node *App::substitute(Pool *pool, int free, int who, Node *with) {
    return new(pool) App(leftFunction -> substitute(pool, free, who, with), rightFunction -> substitute(pool, free, who, with));
}

Node *App::changeprior(Pool *pool, int prior, map<int, int> m) {
    return new(pool) App(leftFunction -> changeprior(pool, prior, m), rightFunction -> changeprior(pool, prior, m));
}

Node *App::copy (Pool *pool) {
    return new(pool) App(leftFunction -> copy(pool), rightFunction -> copy(pool));
}

App::~App() {
    delete leftFunction; 
    delete rightFunction;
}
