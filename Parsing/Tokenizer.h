#pragma once

#include <string>
using namespace std;

class Tokenizer {
    string expression;
    int pos;

    public:
    enum Kind {
        LAMBDA,   // '\'
        OBRACKET, // '('
        CBRACKET, // ')'
        POINT,    // '.'
        VAR,      // variable contains of a-z chars
        ENOF,     // end of file
        UNDEF     // undefined token
    };

    Tokenizer() {}
    Tokenizer(string exp) {
        expression = exp;
        pos = 0;
        while (expression[pos] == ' ') // all spaces are ignored
            ++pos;
    }

    Kind get_kind();
    int get_pos();
    string get_variable();
    char get_char();
    void next();
};
