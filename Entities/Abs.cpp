#include "Abs.h"

void *Abs::operator new (size_t n, Pool *pool) {
    return pool -> palloc(sizeof(Abs));
}

void Abs::operator delete(void *ptr, Pool *pool){
    free(ptr);
}

void Abs::getexp(ostream& out, bool isapp, bool isleft) {
    if (isapp == true) out << '(';
    out << '\\';
    out << l;
    out << '.';
    r -> getexp(out, false, false);
    if (isapp == true) out << ')';
}

void Abs::gettree(ostream& out, int shift, list<int> l) {
    int len = 3;

    out << "Abs";

    l.push_back(shift + len);

    //out << (char) 203 << (char) 205 << (char) 205;
    out << "/--";
    out << ' ';
    out << Abs::l;

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
    out << "\\__";
    l.pop_back();
    r -> gettree(out, shift + len + 3, l);
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
