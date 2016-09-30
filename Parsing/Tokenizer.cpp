#include "Tokenizer.h"

Tokenizer::Kind Tokenizer::get_kind() {
    switch (expression[pos]) {
        case '\\': return LAMBDA;
        case '(': return OBRACKET;
        case ')': return CBRACKET;
        case '.': return POINT;
        case '\0': return ENOF;
        default: 
                   if (expression[pos] >= 'a' && expression[pos] <= 'z') return VAR;
                   else return UNDEF;
    }
}

int Tokenizer::get_pos() {
    return pos;
}

string Tokenizer::get_variable() {
    string variable;
    int tmp = pos;

    while (expression[tmp] >= 'a' && expression[tmp] <= 'z')
        variable += expression[tmp++];
    
    return variable;
}

char Tokenizer::get_char() {
    return expression[pos];
}

void Tokenizer::next() {
    if (get_kind() == ENOF) 
        return;
    
    Kind kind = get_kind();
    
    if (kind == VAR) {
        while (expression[pos] >= 'a' && expression[pos] <= 'z')
            ++pos;
    }
    else ++pos;

    while(expression[pos] == ' ') // all spaces are ignored
        ++pos;
}
