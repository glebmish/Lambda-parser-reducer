#pragma once

#include <list>
#include <map>
#include <streambuf>
#include <fstream>
#include <iostream>
using namespace std;

#include "../MemoryManagement/Pool.h"

class Node {
    public:

        virtual void getexp(ostream &out, bool isapp = false, bool isleft = false) = 0;
        virtual void gettree(ostream &out, bool isDebug = 0, int = 0, list<int> = list<int>()) = 0;

        virtual string saymyname() = 0;
        virtual int getvalue() = 0;

        virtual Node* reduce(Pool *pool) = 0;
        virtual bool isredex() = 0;
        virtual Node* substitute(Pool *pool, int, int, Node*) = 0;
        virtual Node* changeprior(Pool *pool, int, map<int, int> = map<int,int>()) = 0;

        virtual Node* copy(Pool *pool) = 0;
};
