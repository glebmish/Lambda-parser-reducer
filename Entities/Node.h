#pragma once

#include <list>
#include <map>
#include <streambuf>
#include <fstream>
#include <iostream>
#include <vector>

#include "../MemoryManagement/Pool.h"

enum Position {
    _left,
    _right
};

class Var;

class Node {
    protected:
    
    static const string _horizontalFirst, 
                 _horizontalSecond,
                 _vertical;

    public:
    string _entName;

    virtual void get_expression(ostream &out, string wrapEntity = "none", Position position = _right) = 0;
    virtual std::vector<string> get_tree_view(int shift = 0) = 0;

    virtual Node* reduce(Pool *pool) = 0;
    virtual Node* substitute(Pool *pool, Node *substituteTo, Var *substituteThis = NULL) = 0;
    virtual bool is_redex() = 0;

    virtual Node* copy(Pool *pool) = 0;
};
