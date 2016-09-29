#pragma once

#include <ostream>
#include <vector>
#include <string>

#include "../MemoryManagement/Pool.h"

// this declaration used in substitute function
class Var;

class Node {
    protected:

    // this sting used in tree construction. Should be the same in all Node subclasses
    static const string _horizontalFirst, 
                 _horizontalSecond,
                 _vertical;

    public:
    // entity name (Abs, App or Var). Should be available through the base Node class
    string _entName;

    // functions for visual representing of expression
    virtual void get_expression(std::ostream &out, std::string wrapEntity = "none") = 0;
    virtual std::vector<string> get_tree_view(int shift = 0) = 0;

    // reduction related functions
    virtual Node* reduce(Pool *pool) = 0;
    virtual Node* substitute(Pool *pool, Node *substituteTo, Var *substituteThis = NULL) = 0;
    virtual bool is_redex() = 0;

    virtual Node* copy(Pool *pool) = 0;
};
