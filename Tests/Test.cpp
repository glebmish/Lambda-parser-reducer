#include "Test.h"
using namespace std;

bool check(istream &answer, istream &outputRead) {
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

vector<string> get_tests_files(string tests_dir) {
	vector<string> inputFiles;
    
    DIR *dir;
	struct dirent *ent;

	dir = opendir(tests_dir.c_str());
	while ((ent = readdir(dir)) != NULL) {
		string tmp(ent->d_name);
		if (tmp[0] == '.' || tmp[tmp.size() - 2] == '.') 
			continue;

		inputFiles.push_back(tmp);
	}

	closedir(dir);
    return inputFiles;
}


void test(ostream &log) {
    string tests_dir = "./lambda_examples/";
    vector<string> testList = get_tests_files(tests_dir);

    for (unsigned i = 0; i < testList.size(); i++) {
        string inputFile = tests_dir + testList[i];
        string outputFile = inputFile + "tmp";
        string answerFile = inputFile + ".a";

        ifstream input(inputFile.c_str());
        ifstream answer(answerFile.c_str());
        ofstream output(outputFile.c_str());

        string exp;
        getline(input, exp);
        calc(output, exp);

        output.close();
        ifstream outputRead(outputFile.c_str());

        bool isEqual = check(answer, outputRead);
        if (isEqual)
            log << "Test " << i << " passed.\n";
        else 
            log << "Test " << i << " failed.\n";
    }
}
