#include <string>
#include <fstream>
using namespace std;

#include "Calc.h"


int main() {

    string s = "\\m.\\n.\\f.\\x.m(\\m.\\f.\\x.m f(f x)) n f x s t q s";

    ofstream resOut("con");
    calc(resOut, s);

    return 0;
}
