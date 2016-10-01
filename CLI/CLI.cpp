#include <iostream>
#include <string>

#include "CLI.h"
#include "../Parsing/Parse.h"
using namespace std;

void get_next_command(string &command, string &last_command, Tree *&parsed_expression, Tree *&last_parsed_expression) {
    cin >> command;
    
    if (command == ".") {
        command = last_command;
        parsed_expression = last_parsed_expression;
        return;
    }
   last_command = command;

    string expression;
    cin >> std::ws;
    getline(cin, expression);

    if (expression == ".") {
        parsed_expression = last_parsed_expression;
        return;
    }

    parsed_expression = Parse(expression).parse();

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

void cli(ostream &log) {
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
                   
        if (parsed_expression == NULL) {
            cout << "error: there is no previous command\n";
            continue;
        }
        
        process(command, parsed_expression);
   }
}


