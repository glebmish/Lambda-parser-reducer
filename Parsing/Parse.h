#pragma once

#include <string>
#include <iostream>
#include <map>
using namespace std;

#include "Tokenizer.h"
#include "../MemoryManagement/Tree.h"
#include "../Entities/Abs.h"
#include "../Entities/App.h"
#include "../Entities/Var.h"

class ParseError {
    int errorPos;
    char errorChar;
    string expected;

    public:

    ParseError(int errPos, char errCh, string expect): errorPos(errPos), errorChar(errCh), expected(expect) {}
    ParseError(int errPos, char errCh): errorPos(errPos), errorChar(errCh), expected("\0") {}

    void print() {
        cout << "Parse Error: Wrong character \'" << errorChar << "\' on position " << errorPos << "\n";
        if (expected != "\0")
            cout << '\'' << expected << "\' expected\n";
    }
};


//L ::= {T}+
//T ::= \x.L | (L) | x

class Parse {
    Tokenizer tokenizer;
    map<string, Var*> variableNameToObject;

    Node *parse_L(Pool *pool);
    Node *parse_T(Pool *pool);

    Node *parse_lambda(Pool *pool);
    Node *parse_variable(Pool *pool);
    Node *parse_brackets(Pool *pool);
    public:
    Parse(string expression): tokenizer(expression) {}

    Tree parse();
};
