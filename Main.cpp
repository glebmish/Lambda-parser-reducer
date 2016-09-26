#include <string>
#include <istream>
#include <ostream>
using namespace std;

#include "Calculation/Calc.h"
#include "Tests/Test.h"

int main(int argc, char *argv[]) {
    if (argc > 1 && string(argv[1]) == string("test"))
        test(cout);

    istream &in = cin;
    ostream &out = cout;

    string s;
    getline(in, s);

    calc(out, s);

    return 0;
}
