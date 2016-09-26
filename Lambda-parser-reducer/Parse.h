#pragma once

#include <string>
#include <iostream>
#include <map>
using namespace std;

#include "Tokenizer.h"
#include "Tree.h"
#include "Abs.h"
#include "App.h"
#include "Var.h"

class ParseError {
    int ErrorPos;
    char ErrorChar;
    string Expected;

    public:

    ParseError(int ep, char ec, string ex): ErrorPos(ep), ErrorChar(ec), Expected(ex) {}
    ParseError(int ep, char ec): ErrorPos(ep), ErrorChar(ec), Expected("\0") {}

    void print() {
        cout << "Parse Error: Wrong character \'" << ErrorChar << "\' on position " << ErrorPos << "\n";
        if (Expected != "\0")
            cout << '\'' << Expected << "\' expected\n";
    }
};


//L ::= {T}+
//T ::= \x.L | (L) | x

class Parse {
    tokenizer t;
    map<string, int> m;
    int freect;

    Node* parse_L(int k, Pool* pool);
    Node* parse_T(int k, Pool* pool);
    public:
    Parse(string s): t(s), freect(-1) {}

    Tree parse();
};
