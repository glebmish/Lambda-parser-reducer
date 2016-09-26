#include <istream>
#include <dirent.h>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

#include "Test.h"
#include "../Calculation/Calc.h"
#include "../Logger/Logger.h"

bool check(istream &answer, istream &outputRead, ostream &log) {
    LOG(log);
    char ra_char, ca_char;

    while (!answer.eof() && !outputRead.eof()) {
        answer.get(ra_char);
        outputRead.get(ca_char);

        if (ra_char != ca_char) return false;
    }

    if (answer.eof() && outputRead.eof())
        return true;
    else 
        return false;
}

vector<string> get_tests_files(string tests_dir, ostream &log) {
    LOG(log);

	vector<string> inputFiles;
    
    DIR *dir;
	struct dirent *ent;

	dir = opendir(tests_dir.c_str());

    LOG_MESSAGE(tests_dir + " opened");

	while ((ent = readdir(dir)) != NULL) {
		string tmp(ent->d_name);
		if (tmp[0] == '.' || tmp[tmp.size() - 2] == '.') 
			continue;
        
		inputFiles.push_back(tmp);
	}

	closedir(dir);
    return inputFiles;
}

bool cmp(string a, string b) {
    return atoi(a.c_str()) < atoi(b.c_str());
}

void test(ostream &result, ostream &log) {
    LOG(log);
    string tests_dir("./Tests/lambda_examples/");

    vector<string> testList = get_tests_files(tests_dir, log);
    sort(testList.begin(), testList.end(), cmp);
    
    LOG_MESSAGE("tests in " + tests_dir + ": " + log_array(&testList[0], testList.size()));

    for (unsigned i = 0; i < testList.size(); i++) {
        LOG_MESSAGE("test " + testList[i]);

        string inputFile = tests_dir + testList[i];
        string outputFile = inputFile + ".tmp";
        string answerFile = inputFile + ".a";

        ifstream input(inputFile.c_str());
        ifstream answer(answerFile.c_str());
        ofstream output(outputFile.c_str());

        string exp;
        getline(input, exp);

        LOG_MESSAGE("lambda: " + exp);

        calc(output, exp);

        output.close();
        ifstream outputRead(outputFile.c_str());

        bool isEqual = check(answer, outputRead, log);
        if (isEqual) {
            LOG_MESSAGE("Test " + testList[i] + " passed.\n");
            result << "Test " << testList[i] << " passed.\n";
        } else { 
            LOG_MESSAGE("Test " + testList[i] + " failed.\n");
            result << "Test " << testList[i] << " failed.\n";
        }

        outputRead.close();
        remove(outputFile.c_str());
    }
}
