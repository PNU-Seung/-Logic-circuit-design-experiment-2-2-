#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stack>
#include <locale>
#include <utility>
#include <queue>

using namespace std;

vector<string> functionStatement;
queue< pair<string,string> > statement;

vector< vector<string> > function;

int callingFunction(vector<string> _function);
vector<string>& findFunction(string ch);

int main(void) {
	int N, k1, k2;
	ifstream ifp("3.inp");
	ifp >> N, ifp >> k1, ifp >> k2;
	string str;
	vector<string> vecstr;


	for (int i = 0; i < N; i++) {
		vecstr = vector<string>();
		ifp >> str; vecstr.push_back(str);
		while (ifp >> str && str != "$") {
			vecstr.push_back(str);
		}
		function.push_back(vecstr);
	}
	ifp.close();
	ofstream ofp("function.out");
	if (callingFunction(function.front()) == -1) {
		ofp << "DEADLOCK" << std::endl;
		return 0;
	}
	pair<string, string> k1str;
	pair<string, string> k2str;
	int i = 0;
	while(i < statement.size()) {
		if (i == k1-1)
			k1str = std::make_pair(statement.front().first,statement.front().second);
		if (i == k2-1)
			k2str = std::make_pair(statement.front().first, statement.front().second);
		statement.pop();
		i++;
	}
	if (i <= k1 - 1)
		ofp << "NONE" << std::endl;
	else
		ofp << k1str.first << "-" << k1str.second << std::endl;

	if (i <= k2 - 1)
		ofp << "NONE" << std::endl;
	else
		ofp << k2str.first << "-" << k2str.second << std::endl;

	ofp.close();
	return 0;
}
vector<string>& findFunction(string ch) {
	for (vector< vector<string> >::iterator iter = function.begin(); iter != function.end(); iter++) {
		if ((*iter).front() == ch)
			return (*iter);
	}
}

int callingFunction(vector<string> _function) {
	for (vector<string>::const_iterator iter = functionStatement.begin(); iter != functionStatement.end(); iter++)
	{
		if ((*iter) == _function.front())
			return -1;
	}

	functionStatement.push_back(_function.front());

	for (vector<string>::iterator iter = _function.begin() + 1; iter != _function.end(); iter++) {
		if (isupper( (*iter).front() )){
			if (callingFunction(findFunction((*iter))) == -1)
				return -1;
		}
		else
			statement.push(pair<string, string>((*_function.begin()),(*iter)));
	}
	functionStatement.pop_back();
	return 0;
}
