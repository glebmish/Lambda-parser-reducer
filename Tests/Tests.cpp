#include <fstream>
#include <dirent.h>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

#include "../MemoryManagement/Tree.h"
#include "../Parsing/Parse.h"
using namespace std;

bool check_get_expression(Tree *parsed_expression, string right_answer) {
    string got_expression = parsed_expression->get_expression();

    return got_expression == right_answer;
}

bool test_get_expression(Tree *parsed_expression, ifstream &answer) {
    string get_expression_answer;

    getline(answer, get_expression_answer);
    return check_get_expression(parsed_expression, get_expression_answer);
}


bool check_get_tree_view(Tree *parsed_expression, vector<string> right_answer) {
    vector<string> got_tree_view = parsed_expression->get_tree_view();
    vector<string>::iterator ans_it = right_answer.begin(), 
                             got_it = got_tree_view.begin();

    map<string, string> answer_address_to_computed_adress;

    for (; ans_it != right_answer.end() && got_it != got_tree_view.end(); ++ans_it, ++got_it) {
        string ans_str_wo_adress = *ans_it,
               got_str_wo_adress = *got_it;

        size_t ans_address_position = ans_it->find("0x"),
            got_address_position = got_it->find("0x");
        if (ans_address_position != string::npos && got_address_position != string::npos) {
            string ans_var_adress = ans_it->substr(ans_address_position), 
                   got_var_adress = got_it->substr(got_address_position);

            ans_str_wo_adress = ans_it->erase(ans_address_position);
            got_str_wo_adress = got_it->erase(got_address_position);

            if (answer_address_to_computed_adress.count(ans_var_adress)) {
                if (answer_address_to_computed_adress[ans_var_adress] != got_var_adress)
                    return false;
            } else {
                answer_address_to_computed_adress[ans_var_adress] = got_var_adress;
            }
        }

        if (ans_str_wo_adress != got_str_wo_adress)
            return false;
    }

    if (ans_it != right_answer.end() || got_it != got_tree_view.end())
        return false;

    return true;
}

bool test_get_tree_view(Tree *parsed_expression, ifstream &answer) {
    vector<string> get_tree_view_answer;
    string cur_tree_string;
    
    getline(answer, cur_tree_string);
    while (cur_tree_string != "") {
        get_tree_view_answer.push_back(cur_tree_string);
        getline(answer, cur_tree_string);
    }

    return check_get_tree_view(parsed_expression, get_tree_view_answer);
}


bool check_full_reduce(Tree *parsed_expression, vector<string> right_answer) {
    vector<string> got_full_reduce;

    got_full_reduce.push_back(parsed_expression->get_expression());
    while (parsed_expression->is_redex()) {
        parsed_expression->reduce();
        got_full_reduce.push_back(parsed_expression->get_expression());
    }

    vector<string>::iterator got_it = got_full_reduce.begin(),
                             ans_it = right_answer.begin();

    for (; ans_it != right_answer.end() && got_it != got_full_reduce.end(); ++ans_it, ++got_it)
        if (*got_it != *ans_it)
            return false;

    if (ans_it != right_answer.end() || got_it != got_full_reduce.end())
        return false;

    return true;
}

bool test_full_reduce(Tree *parsed_expression, ifstream &answer) {
    vector<string> full_reduce_answer;
    string cur_reduce_string;
    
    getline(answer, cur_reduce_string);
    while (cur_reduce_string != "") {
        full_reduce_answer.push_back(cur_reduce_string);
        getline(answer, cur_reduce_string);
    }
    
    return check_full_reduce(parsed_expression, full_reduce_answer);
} 
 

bool test(string test_name, string expression, ifstream &answer) {
    bool result = true;

    Tree *parsed_expression = Parse(expression).parse();

    if (!test_get_expression(parsed_expression, answer)) {
        cout << "Test " << test_name << ": get_expression failed\n";
        result = false;
    }

    if (!test_get_tree_view(parsed_expression, answer)) {
        cout << "Test " << test_name << ": get_tree_view failed\n";
        result = false;
    }

   if (!test_full_reduce(parsed_expression, answer)) {
        cout << "Test " << test_name << ": full reduce failed\n";
        result = false;
   }
    
   return result;
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

bool cmp(string a, string b) {
    return atoi(a.c_str()) < atoi(b.c_str());
}

int main() {
    string tests_dir("./Tests/lambda_examples/");

    //vector<string> testList = get_tests_files(tests_dir);
    vector<string> testList;
    testList.push_back("1");
    sort(testList.begin(), testList.end(), cmp);
    
    for (unsigned i = 0; i < testList.size(); i++) {
        string inputFile = tests_dir + testList[i];
        string answerFile = inputFile + ".ans";

        ifstream input(inputFile.c_str());
        ifstream answer(answerFile.c_str());

        string expression;
        getline(input, expression);

        if (test(testList[i], expression, answer))
            cout << "Test " << testList[i] << ": passed.\n";
        else 
            cout << "Test " << testList[i] << ": failed.\n";
    }
}
