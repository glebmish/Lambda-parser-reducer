#include "Logger.h"
using namespace std;

scope_logger::scope_logger(ostream &l, string function, string file) : log(l), beginning(function + "() in " + file + ": ") {
    log << beginning << "Enter\n";
}

scope_logger::~scope_logger() {
    log << beginning << "Exit\n";
}

void scope_logger::print (std::string msg) {
    log << beginning << msg << "\n";
}
