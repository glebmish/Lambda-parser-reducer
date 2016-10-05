#include <iostream>
#include <string>

#include "CLI.h"
#include "../Parsing/Parse.h"
using namespace std;

void get_next_command(string &command, string &last_command, Tree *&parsed_expression, Tree *&last_parsed_expression) {
    cin >> command;
    
    // '.' means to repeat last inputed command
    if (command == ".") {
        command = last_command;
        parsed_expression = last_parsed_expression;
        return;
    }
    last_command = command;

    // exit command used without expression
    // thus, the function should be terminated now
    if (command == "exit") {
        parsed_expression = last_parsed_expression;
        return;
    }

    string expression;
    
    // to skip leading whitespaces
    cin >> std::ws;
    getline(cin, expression);

    // '.' means to apply command to last inputed expression
    if (expression == ".") {
        parsed_expression = last_parsed_expression;
        return;
    }

    parsed_expression = Parse(expression).parse();

    // to avoid memory leak
    delete last_parsed_expression;
    last_parsed_expression = parsed_expression;
}

void process(string &command, Tree *parsed_expression) {
    if (command == "print")
        cout << parsed_expression->get_expression();

    else if (command == "tree") {
        vector<string> tree = parsed_expression->get_tree_view();
        for (size_t i = 0; i < tree.size(); ++i)
            cout << tree[i] << endl;
    }

    else if (command == "reduce") {
        int reductionsCounter = 0;

        while (parsed_expression->is_redex()) {
            parsed_expression->reduce();
            ++reductionsCounter;
        }

        cout << parsed_expression->get_expression() << endl;
        cout << reductionsCounter << " reductions";
    }

    // print every step of reduction
    else if (command == "steps") {
        int reductionsCounter = 0;

        cout << parsed_expression->get_expression() << endl;
        
        while (parsed_expression->is_redex()) {
            parsed_expression->reduce();
            cout << parsed_expression->get_expression() << endl;

            ++reductionsCounter;
        }

        cout << reductionsCounter << " reductions";
    }

    else
        cout << "unknown command";

    cout << endl;
}

void cli() {
    string command = "";

    string last_command = "";
    Tree *last_parsed_expression = NULL;

    while (command != "exit") {
        cout << "--> ";

        Tree *parsed_expression = NULL;
        try {
            get_next_command(command, last_command, parsed_expression, last_parsed_expression);  
        } catch (ParseError e) {
            e.print();
            continue;
        }

        // that way, there's no need to check parsed_expression on NULL and process any commands
        if (command == "exit")
            continue;

        // parsed_expression == NULL only if "." or "<command> ." were inputed before any other
        if (parsed_expression == NULL) {
            cout << "error: there is no previous command\n";
            continue;
        }
        
        process(command, parsed_expression);
   }
}


