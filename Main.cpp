#include <string>
#include <ostream>
#include <iostream>
using namespace std;

#include "CLI/CLI.h"
#include "./Logger/Logger.h"

int main(int argc, char *argv[]) {
    if (argc > 2) {
        cout << "Error: incorrect arguments\n";
        return -1;
    }
    
    ostream *log;
    if (argc == 2 && string(argv[1]) == "--log")
        log = &cout;
    else
        log = new ostream(0);

    LOG(*log);
    LOG_MESSAGE("logging enabled");

    cli(*log);

    return 0;
}
