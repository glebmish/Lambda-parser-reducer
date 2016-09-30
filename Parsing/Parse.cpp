#include "Parse.h"

ParseError::ParseError(int errPos, char errCh, string expect): errorPos(errPos), errorChar(errCh), expected(expect) {}
ParseError::ParseError(int errPos, char errCh): errorPos(errPos), errorChar(errCh), expected("\0") {}

void ParseError::print() {
    cout << "Parse Error: Wrong character \'" << errorChar << "\' on position " << errorPos << "\n";
    if (expected != "\0")
        cout << '\'' << expected << "\' expected\n";
}

Tree Parse::parse() {
    Pool* pool = new Pool();
    Node *function = parse_L(pool);

    if (tokenizer.get_kind() != Tokenizer::ENOF) {
        throw ParseError(tokenizer.get_pos(), tokenizer.get_char(), "\\0");
    }

    return Tree(pool, function);
}

Node *Parse::parse_L(Pool *pool) {
    Node* leftFunction = parse_T(pool);

    if (leftFunction == NULL) 
        throw ParseError(tokenizer.get_pos(), tokenizer.get_char());
    
    while (tokenizer.get_kind() != Tokenizer::ENOF) {
        Node* rightFunction = parse_T(pool);

        if (rightFunction == NULL) 
            break;

        leftFunction = new(pool) App(leftFunction, rightFunction);
    }
    

    return leftFunction;
};

Node *Parse::parse_lambda(Pool *pool) {
    tokenizer.next();
    
    // should be this token:
    // \x.y
    //  ^
    if (tokenizer.get_kind() != Tokenizer::VAR) 
        throw ParseError(tokenizer.get_pos(), tokenizer.get_char(), "[a-z]");

    string variable = tokenizer.get_variable();

    // if there's outter argument with the same name
    // it will be saved to outterArgument variable
    // and restored later
    Var *outterArgument = NULL;
    if (variableNameToObject.count(variable))
        outterArgument = variableNameToObject[variable];

    Var *argument = new(pool) Var(variable);
    variableNameToObject[variable] = argument;
    
    tokenizer.next();
    
    // should be this token:
    // \x.y
    //   ^
    if (tokenizer.get_kind() != Tokenizer::POINT) 
        throw ParseError(tokenizer.get_pos(), tokenizer.get_char(), ".");
    
    tokenizer.next();

    Node* function = parse_L(pool);

    // restore outter argument with the same name
    // or delete current argument name frome names set
    if (outterArgument != NULL)
        variableNameToObject[variable] = outterArgument;
    else
        variableNameToObject.erase(variable);

    return new(pool) Abs(argument, function);
}

Node *Parse::parse_variable(Pool *pool) {
    if (tokenizer.get_kind() != Tokenizer::VAR) 
        throw ParseError(tokenizer.get_pos(), tokenizer.get_char(), "[a-z]");

    string variable = tokenizer.get_variable();

    tokenizer.next();

    // if there's variable with this name in the variables set
    // return if, else create new variable
    if (variableNameToObject.count(variable))
        return variableNameToObject[variable];
    else 
        return new(pool) Var(variable);
}

Node *Parse::parse_brackets(Pool *pool) {
    tokenizer.next();

    Node* function = parse_L(pool);
    
    // should be this token:
    // ( a )
    //       ^
    if (tokenizer.get_kind() != Tokenizer::CBRACKET) 
        throw ParseError(tokenizer.get_pos(), tokenizer.get_char(), ")");

    tokenizer.next();

    return function;
}


Node *Parse::parse_T(Pool *pool) {
    // token: \x.y
    //        ^
    if (tokenizer.get_kind() == Tokenizer::LAMBDA)
        return parse_lambda(pool);
    // token: x
    //        ^
    else if (tokenizer.get_kind() == Tokenizer::VAR)
        return parse_variable(pool);
    // token: ( a )
    //        ^
    else if (tokenizer.get_kind() == Tokenizer::OBRACKET)
        return parse_brackets(pool); 

    else
        return NULL;
}
