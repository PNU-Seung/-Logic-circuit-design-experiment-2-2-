#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <list>
using namespace std;

typedef struct{
	int line;
	int wordListSize;
	list<string> wordList;
} MyStatement;

void printProgramTitle();
void printHelp();
void printStatement(MyStatement statement);
void interpretCommand();
void readDocument(string fileName);
bool findStatement(int line, MyStatement& result);

list <MyStatement> chapter;

int main(){

	readDocument("CrimePunish.txt");  //파일의 내용을 문장단위로 읽어들임
	printProgramTitle();              //프로그램 타이틀을 출력함
	interpretCommand();               //사용자로부터 명령어를 읽어서 처리함

	return 0;
}

void printProgramTitle(){
	cout<<endl<<"[List를 이용한 Index 만들기 프로그램(mIndex.cpp)]------------------------------"<<endl;
	cout<<"<CrimePunish.txt> : 전체 문장의 개수 : "<<chapter.size()<<endl<<endl;
	printHelp();
	cout<<"-------------------------------------------------------------------------------"<<endl;
} // end of printProgram()

void printHelp(){
	cout<<"[도움말]"<<endl;
	cout<<"명령어 1) help         : 도움말 출력"<<endl;
	cout<<"명령어 2) quit         : 프로그램 종료"<<endl;
	cout<<"명령어 3) pline 줄번호 : CrimePunish에서 해당 줄번호(1부터 시작)의 문장을 출력"<<endl;
	cout<<"     예) >>pline 3   : CrimePunish의 3번째 문장을 출력"<<endl;
	cout<<"명령어 4) pword i j     : i번째 문장에서 j번째 단어를 찾아서 출력한다." << endl;
	cout<<"명령어 5) fword word    : word가 포함된 문장의 번호와 그 횟수를 출력한다." << endl;
	cout<<"명령어 6) state k       : 단어의 수가 k개 이상인 문장을 모두 출력한다." << endl;
	cout << "명령어 7) sortout k1 k2 : 각 문장을 사전식으로 정렬했을 때 기준으로, k1번째 원소" << endl;
	cout <<"	  부터 k2번째 문장까지 순서대로 출력한다." << endl;
} // end of printHelp( )

void printStatement(MyStatement statement){ //list<string>의 내용을 출력하는 함수
	cout<<statement.line<<" : ";
	for(list<string>::iterator iter = statement.wordList.begin(); iter != statement.wordList.end(); iter++){
		cout<<(*iter).c_str()<<" ";
	}
	cout<<endl;
} // end of printStaement( )

void interpretCommand(){ //사용자로부터 명령어를 입력받아 처리하는 함수
	while(true){
		string command = "";
		cout<<endl<<">>";
		cin>>command;
		if (command == "quit") break; // quit이 나오면 loop을 중단한다.
		else if (command == "help") printHelp();
		else if (command == "pline") {
			string lineString = "";
			int line;
			cin >> lineString;
			line = atoi(lineString.c_str());
			if (line == 0)cout << "잘못된 줄번호 입니다." << endl;
			else {
				MyStatement statement;
				if (findStatement(line, statement)) {
					printStatement(statement);
				}
				else {
					cout << "해당 줄 번호의 문장을 찾을 수 없습니다." << endl;
				}
			}
		}
		else if (command == "pword") {
			unsigned int i = 0, j = 0;
			cin >> i >> j;
			list<MyStatement>::const_iterator chapterIterator = chapter.begin();
			if (i <= chapter.size()) {
				advance(chapterIterator, i - 1);
				list<string>::const_iterator wordIterator = chapterIterator->wordList.begin();
				if (j <= chapterIterator->wordList.size()) {
					advance(wordIterator, j - 1);
					cout << *wordIterator << endl;
				}
				else
					cout << "없음" << endl;
			}
			else
				cout << "없음" << endl;
		}
		else if (command == "fword"){
			string s;
			cin >> s;
			for (const MyStatement iter:chapter) {
				if (count(iter.wordList.begin(), iter.wordList.end(), s))
					cout << iter.line << "번째 줄에서 " << count(iter.wordList.begin(), iter.wordList.end(), s) << "번 나왔습니다" << endl;
			}
		}
		else if (command == "state") {
			int k;
			cin >> k;
			for (const MyStatement iter1 : chapter) {
				if (iter1.wordListSize >= k) {
					cout << iter1.line;
					for (const string iter2 : iter1.wordList)
						cout <<" "<<iter2;
					cout << endl;
				}
			}
		}
		else if (command == "sortout") {
			list<list<string>> newList;
			for (MyStatement iter : chapter)
				newList.push_back(iter.wordList);
			for (list<string>& iter : newList)
				iter.sort();
			unsigned int k1, k2;
			cin >> k1 >> k2;
			list<list<string>>::const_iterator k1Line = newList.begin();
			list<list<string>>::const_iterator k2Line = newList.begin();
			advance(k2Line, k2);
			for (list<string> iter : newList) {
				if (k1 >iter.size())
					k1 -= iter.size();
				else {
					list<string>::const_iterator wordIterator = iter.begin();
					advance(wordIterator, k1-1);
					for (list<string>::const_iterator it = wordIterator; it != iter.end(); it++)
						cout << " " << *it;
					cout << endl;
					break;
				}
				k1Line++;
			}

			for (++k1Line; k1Line != k2Line; k1Line++) {
				for (const string str : *k1Line)
					cout << " " << str;
				cout << endl;
			}
		}
		else{
			cout<<"잘못된 명령어입니다. help를 확인하세요."<<endl;
		}
	}
}

void readDocument(string fileName){
	ifstream documentIfs(fileName.c_str());
	string word;
	MyStatement ms;
	while(!documentIfs.eof()){
		documentIfs>>word;
		if(word == "#"){ //문장의 끝인 경우
			ms.line = chapter.size()+1;
			ms.wordListSize = ms.wordList.size();
			chapter.push_back(ms);
			ms.wordList.clear();
		}
		else ms.wordList.push_back(word);

		if(documentIfs.eof())break;
	}
	documentIfs.close();
}

bool findStatement(int line, MyStatement& result){ //line에 해당하는 문장(MyStatement)을 반환
	list<MyStatement>::iterator iter;
	for(iter = chapter.begin(); iter != chapter.end(); iter++){
		if(line==(*iter).line) {
			result = (*iter);
			break;
		}
	}
	if(iter != chapter.end())
		return true;	 //찾음
	else
		return false;    //못찾음
}
