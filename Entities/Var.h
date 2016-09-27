#pragma once

#include <string>
#include <iostream>
#include <streambuf>
#include <fstream>
using namespace std;

#include "Node.h"

class Var : public Node {
    int s;

    public:

    Var(int ss): s(ss) {}

    void *operator new (size_t n, Pool *pool);
    void operator delete (void* ptr, Pool *pool);

    void get_expression(ostream &out, WrapEntity wentity, Position position);
    void gettree(ostream &out, int shift = 0, list<int> l = list<int>());

    string saymyname();
    int getvalue();

    Node *reduce(Pool *pool);
    bool isredex();
    Node *substitute(Pool *pool, int free, int who, Node *with);
    Node *changeprior(Pool *pool, int prior, map<int, int> m = map<int,int>());

    Node *copy(Pool *pool);
};
