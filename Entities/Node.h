#pragma once

#include <list>
#include <map>
#include <streambuf>
#include <fstream>
#include <iostream>
#include <vector>

#include "../MemoryManagement/Pool.h"

enum WrapEntity {
    _application,
    _abstraction,
    _none
};

enum Position {
    _left,
    _right
};

class Node {
    protected:

    string _entName,
           _horizontalFirst, 
           _horizontalSecond,
           _vertical;

    public:
        Node();

        virtual void get_expression(ostream &out, WrapEntity wentity = _none, Position position = _right) = 0;
        virtual std::vector<string> get_tree_view(int shift = 0) = 0;

        virtual string saymyname() = 0;
        virtual int getvalue() = 0;

        virtual Node* reduce(Pool *pool) = 0;
        virtual bool isredex() = 0;
        virtual Node* substitute(Pool *pool, int free, int who, Node *with) = 0;
        virtual Node* changeprior(Pool *pool, int prior, map<int, int> m = map<int,int>()) = 0;

        virtual Node* copy(Pool *pool) = 0;
};
