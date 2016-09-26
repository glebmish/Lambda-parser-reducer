#include "App.h"

void *App::operator new (size_t n, Pool *pool) {
    return pool -> palloc(sizeof(App));
}

void App::operator delete(void* ptr, Pool *pool) {
    free(ptr);
}

void App::getexp(ostream& out, bool isapp, bool isleft) {
    if (isapp == true && isleft == false) out << '(';
    l -> getexp(out, true, true);
    r -> getexp(out, true, false);
    if (isapp == true && isleft == false) out << ')';
}

void App::gettree(ostream &out, bool isDebug, int shift, std::list<int> l) {
    int len;
    if (isDebug)
        len = 12;
    else
        len = 3;

    if (isDebug)
        out << this << " ";
    out << "App";

    l.push_back(shift + len);

    //out << (char) 203 << (char) 205 << (char) 205;
    out << "/--";
    App::l -> gettree(out, isDebug, shift + len + 3, l);

    std::list<int> tmpl(l);
    int tmp;
    if (tmpl.empty()) {
        tmp = shift + len + 1;
    } else {
        tmp = tmpl.front();
        tmpl.pop_front();
    }

    out << '\n';
    for(int i = 0; i < shift + len + 1; ++i) {
        if (i == tmp) {
            //out << (char) 186;
            out << "|";
            if (tmpl.empty()) {
                tmp = shift + len + 1;
            } else {
                tmp = tmpl.front();
                tmpl.pop_front();
            }
        } else
            out << ' ';
    }

    tmpl = l;
    if (tmpl.empty()) {
        tmp = shift + len + 1;
    } else {
        tmp = tmpl.front();
        tmpl.pop_front();
    }

    out << '\n';
    for(int i = 0; i < shift + len; ++i) {
        if (i == tmp) {
            //out << (char) 186;
            out << "|";
            if (tmpl.empty()) {
                tmp = shift + len + 1;
            } else {
                tmp = tmpl.front();
                tmpl.pop_front();
            }
        } else
            out << ' ';
    }
    //out << (char) 200 << (char) 205 << (char) 205;
    out << "\\__";
    l.pop_back();
    r -> gettree(out, isDebug, shift + len + 3, l);
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

        return new(pool) App(l -> reduce(pool), r -> reduce(pool));//�������� �� ����� �������� ����� ���� ������� � ������ ���
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