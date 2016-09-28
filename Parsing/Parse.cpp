#include "Parse.h"

Tree Parse::parse() {
    Pool* pool = new Pool();
    Node *function = parse_L(pool);

    if (tokenizer.get_kind() != Tokenizer::ENOF) {
        delete function;
        throw ParseError(tokenizer.get_pos(), tokenizer.get_char(), "\\0");
    }

    return Tree(pool, function);
}

Node *Parse::parse_L(Pool *pool) {
    Node* leftFunction = parse_T(pool);

    if (leftFunction == NULL) 
        throw ParseError(tokenizer.get_pos(), tokenizer.get_char());
    
    try {
        while (tokenizer.get_kind() != Tokenizer::ENOF) {
            Node* rightFunction = parse_T(pool);
            
            if (rightFunction == NULL) 
                break;

            leftFunction = new(pool) App(leftFunction, rightFunction);
        }
    } catch (ParseError error) {
        delete leftFunction;
        throw error;
    }

    return leftFunction;
};

Node *Parse::parse_lambda(Pool *pool) {
    tokenizer.next();

    string variable = tokenizer.get_variable();

    Var *outterArgument = NULL;
    if (variableNameToObject.count(variable))
        outterArgument = variableNameToObject[variable];

    Var *argument = new(pool) Var(variable);
    variableNameToObject[variable] = argument;

    tokenizer.next();

    if (tokenizer.get_kind() != Tokenizer::POINT) 
        throw ParseError(tokenizer.get_pos(), tokenizer.get_char(), ".");

    tokenizer.next();

    Node* function = parse_L(pool);

    if (outterArgument != NULL)
        variableNameToObject[variable] = outterArgument;
    else
        variableNameToObject.erase(variable);

    return new(pool) Abs(argument, function);
}

Node *Parse::parse_variable(Pool *pool) {
    string variable = tokenizer.get_variable();

    tokenizer.next();

    if (variableNameToObject.count(variable))
        return variableNameToObject[variable];
    else 
        return new(pool) Var(variable);
}

Node *Parse::parse_brackets(Pool *pool) {
    tokenizer.next();

    Node* function = parse_L(pool);

    if (tokenizer.get_kind() != Tokenizer::CBRACKET) 
        throw ParseError(tokenizer.get_pos(), tokenizer.get_char(), ")");

    tokenizer.next();

    return function;
}


Node *Parse::parse_T(Pool *pool) {
    if (tokenizer.get_kind() == Tokenizer::LAMBDA)
        return parse_lambda(pool);

    else if (tokenizer.get_kind() == Tokenizer::VAR)
        return parse_variable(pool);

    else if (tokenizer.get_kind() == Tokenizer::OBRACKET)
        return parse_brackets(pool); 

    else
        return NULL;
}
