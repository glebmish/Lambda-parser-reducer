#include <string>
#include <streambuf>
#include <fstream>
#include <iostream>
using namespace std;

#include "Node.h"
#include "Parse.h"
#include "Pool.h"

bool check(istream& ans, istream& curAns) {
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

void calc(ostream& out, string exp) {
	try {
		Tree x = Parse(exp).parse();

		out << "Expression:\n";
		x.getexp(out);
		out << "\n\n";

		out << "Tree:\n";
		x.gettree(out);
		out << "\n\n";

		out << "Reduced expression:\n";
		while (x.isredex()) {
			x.reduce();
			
		}
		x.getexp(out);
		out << "\n\n";

		out << "Tree:\n";
		x.gettree(out);
		out << "\n\n";

		x.clean();
		out << "Blocks in memory:\n" << PoolBlock::blocksInMemory << "\n\n";
	} catch (ParseError e) {
		e.print();
		out << "FAIL";
	}
}

void test(ofstream& log) {
	ifstream testsLink("./tests/tests.txt");

	int i = 0;
	while (++i && !testsLink.eof()) {

		fstream out("./tests/tmp.txt", ios_base::out);

		string nameProb;
		string nameAns;
		testsLink >> nameProb >> nameAns;

		ifstream prob(nameProb);
		ifstream ans(nameAns);

		string exp;
		getline(prob, exp);
		
		calc(out, exp);
		
		out.close();
		out.open("./tests/tmp.txt", ios_base::in);
		bool res = check(ans, out);
		if (res)
			log << "Test " << i << " passed.\n";
		else log << "Test " << i << " failed.\n";
	}
}

int main() {
	ofstream log("con");
	test(log);
	log.close();

	string s = "\\x.(\\y.\\z.y z) x";
	calc(ostream(cout.rdbuf()), s);

	return 0;
}