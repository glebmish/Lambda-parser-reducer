#include <string>
#include <istream>
#include <ostream>
using namespace std;

#include "Calc.h"


int main() {
    istream &in = cin;
    ostream &out = cout;

    string s;
    in >> s;

    calc(out, s);

    return 0;
}
