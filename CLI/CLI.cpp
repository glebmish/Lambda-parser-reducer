#include <iostream>
#include <string>

#include "CLI.h"
#include "../Parsing/Parse.h"
using namespace std;

void cli(ostream &log) {
    string command = "";

    string last_command = "";
    string last_expression = "";
    Tree *lastParsedExpression;

    while (command != "exit") {
        string expression = "";

        cout << "--> ";

        cin >> command;
        
        if (command == ".") {
            if (last_command == "") {
                cout << "error: there was no commands yet\n";
                continue;
            } else {
                command = last_command;
                expression = " .";
            }
        } else 
            last_command = command;

        if (command == "print") {
            Tree *parsedExpression;

            if (expression == "")
                getline(cin, expression);

            if (expression == " .") {
                if (last_expression == "") {
                    cout << "error: there was no commands yet\n";
                    continue;
                } else {
                    expression = last_expression;
                    parsedExpression = lastParsedExpression;
                }
            } else {
                Tree current = Parse(expression).parse();
                parsedExpression = &current;

                last_expression = expression;
                lastParsedExpression = parsedExpression;
            }

            cout << parsedExpression->get_expression() << endl;
        }
    }
}

