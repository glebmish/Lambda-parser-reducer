#include "Calc.h"
using namespace std;

void calc(ofstream& out, string exp) {
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
