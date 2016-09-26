#include <ostream>

void test(std::ostream &result, std::ostream &log = *(new std::ostream(0)));
