#include "Test.h"
using namespace std;

bool check(ifstream& ans, ifstream& curAns) {
    char ansC, curAnsC;
    while (!ans.eof() && !curAns.eof()) {
        ans.get(ansC);
        curAns.get(curAnsC);
        if (ansC != curAnsC) return false;
    }
    if (ans.eof() && curAns.eof())
        return true;
    else return false;
}


void test(ofstream& log) {
    ifstream testsLink("./Tests/tests.txt");

    int i = 0;
    while (++i && !testsLink.eof()) {
        ofstream resOut("./Tests/tmp.txt");

        string nameProb;
        string nameAns;
        testsLink >> nameProb >> nameAns;

        ifstream prob(nameProb.c_str());
        ifstream ans(nameAns.c_str());

        string exp;
        getline(prob, exp);

        calc(resOut, exp);
        resOut.close();
        ifstream resIn("./Tests/tmp.txt");
        bool res = check(ans, resIn);
        if (res)
            log << "Test " << i << " passed.\n";
        else log << "Test " << i << " failed.\n";
    }
}

