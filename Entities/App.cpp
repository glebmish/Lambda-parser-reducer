#include "App.h"

void *App::operator new (size_t n, Pool *pool) {
    return pool -> palloc(sizeof(App));
}

void App::operator delete(void* ptr, Pool *pool) {
    free(ptr);
}
void App::get_expression(ostream& out, WrapEntity wentity, Position position) {
    if (wentity == _application && position == _left)
        out << '(';
    
    l -> get_expression(out, _application, _left);
    r -> get_expression(out, _application, _right);
    
    if (wentity == _application && position == _left) 
        out << ')';
}

vector<string> App::get_tree_view(int shift) {
    vector<string> treeBegin;

    int newShift = shift + _entName.size() + _horizontalFirst.size() + 1;
    vector<string> treeMid = l->get_tree_view(newShift);

    treeMid[0].replace(shift, _entName.size() + _horizontalFirst.size() + 1, _entName + _horizontalFirst + ' ');
    for (int i = 1; i < treeMid.size(); i++)
        treeMid[i].replace(shift + _entName.size(), _vertical.size(), _vertical);
    
    treeBegin.insert(treeBegin.end(), treeMid.begin(), treeMid.end());
    treeBegin.push_back(string(shift + _entName.size(), ' ') + _vertical);

    vector<string> treeEnd = r->get_tree_view(newShift);
    treeEnd[0].replace(shift + _entName.size(), _horizontalSecond.size(), _horizontalSecond);

    treeBegin.insert(treeBegin.end(), treeEnd.begin(), treeEnd.end());

    return treeBegin;
}
    
string App::saymyname() {
    return "App";
}

int App::getvalue() {
    return 0;
}

Node *App::reduce(Pool *pool) {
    if (l -> saymyname() == "Abs") {
        return l -> substitute(pool, 0, 0, r);
    } else {
        //l = l -> reduce(pool);
        //r = r -> reduce(pool);
        //return this -> copy(pool);

        return new(pool) App(l -> reduce(pool), r -> reduce(pool));//возможно не будет работать когда идет перенос в другой пул
    }
}

bool App::isredex() {
    if (l -> saymyname() == "Abs") 
        return true;
    else
        return l -> isredex() || r -> isredex();
}

Node *App::substitute(Pool *pool, int free, int who, Node *with) {
    return new(pool) App(l -> substitute(pool, free, who, with), r -> substitute(pool, free, who, with));
}

Node *App::changeprior(Pool *pool, int prior, map<int, int> m) {
    return new(pool) App(l -> changeprior(pool, prior, m), r -> changeprior(pool, prior, m));
}

Node *App::copy (Pool *pool) {
    return new(pool) App(l -> copy(pool), r -> copy(pool));
}

App::~App() {
    delete l; 
    delete r;
}
