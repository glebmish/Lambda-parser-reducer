#include <string>
#include <istream>
#include <ostream>
#include <fstream>
using namespace std;

#include "Calculation/Calc.h"
#include "Tests/FunctionalTest.h"
#include "./Logger/Logger.h"

int main(int argc, char *argv[]) {
    bool isTest = false;
    bool isLog = false;
    
    for (int i = 1; i < argc; ++i) {
        if (string(argv[i]) == "--test") {
            isTest = true;
        }

        if (string(argv[i]) == "--log") {
            isLog = true;
        }

    }
    
    ostream *log;
    if (isLog) {
        log = &cout;
    } else {
        log = new ostream(0);
    }

    LOG(*log);
    LOG_MESSAGE("flag --log is set");

    LOG_MESSAGE("flag --test is set");
    if (isTest) {
        test(cout, *log);
        return 0;
    }

    istream &in = cin;
    ostream &out = cout;

    string s;
    getline(in, s);

    LOG_MESSAGE("Lambda " + s + " have been read");

    calc(out, s);

    return 0;
}
