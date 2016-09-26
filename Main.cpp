#include <string>
#include <istream>
#include <ostream>
using namespace std;

#include "Calculation/Calc.h"


int main() {
    istream &in = cin;
    ostream &out = cout;

    string s;
    getline(in, s);

    calc(out, s);

    return 0;
}
