#pragma once

#include <string>
using namespace std;

class tokenizer {
    string s;
    int pos;

    public:
    enum kind {
        LAMBDA,
        OBRACKET,
        CBRACKET,
        POINT,
        VAR,
        SPACE,
        ENOF,
        UNDEF
    };

    tokenizer() {}
    tokenizer(string ss) {
        s = ss;
        pos = 0;
        while (s[pos] == ' ')
            ++pos;
    }

    kind getKind();
    int getPos();
    string getString();
    char getChar();
    void Next();
};
