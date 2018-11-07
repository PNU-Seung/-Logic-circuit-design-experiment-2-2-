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

	readDocument("CrimePunish.txt");  //������ ������ ��������� �о����
	printProgramTitle();              //���α׷� Ÿ��Ʋ�� �����
	interpretCommand();               //����ڷκ��� ��ɾ �о ó����

	return 0;
}

void printProgramTitle(){
	cout<<endl<<"[List�� �̿��� Index ����� ���α׷�(mIndex.cpp)]------------------------------"<<endl;
	cout<<"<CrimePunish.txt> : ��ü ������ ���� : "<<chapter.size()<<endl<<endl;
	printHelp();
	cout<<"-------------------------------------------------------------------------------"<<endl;
} // end of printProgram()

void printHelp(){
	cout<<"[����]"<<endl;
	cout<<"��ɾ� 1) help         : ���� ���"<<endl;
	cout<<"��ɾ� 2) quit         : ���α׷� ����"<<endl;
	cout<<"��ɾ� 3) pline �ٹ�ȣ : CrimePunish���� �ش� �ٹ�ȣ(1���� ����)�� ������ ���"<<endl;
	cout<<"     ��) >>pline 3   : CrimePunish�� 3��° ������ ���"<<endl;
	cout<<"��ɾ� 4) pword i j     : i��° ���忡�� j��° �ܾ ã�Ƽ� ����Ѵ�." << endl;
	cout<<"��ɾ� 5) fword word    : word�� ���Ե� ������ ��ȣ�� �� Ƚ���� ����Ѵ�." << endl;
	cout<<"��ɾ� 6) state k       : �ܾ��� ���� k�� �̻��� ������ ��� ����Ѵ�." << endl;
	cout << "��ɾ� 7) sortout k1 k2 : �� ������ ���������� �������� �� ��������, k1��° ����" << endl;
	cout <<"	  ���� k2��° ������� ������� ����Ѵ�." << endl;
} // end of printHelp( )

void printStatement(MyStatement statement){ //list<string>�� ������ ����ϴ� �Լ�
	cout<<statement.line<<" : ";
	for(list<string>::iterator iter = statement.wordList.begin(); iter != statement.wordList.end(); iter++){
		cout<<(*iter).c_str()<<" ";
	}
	cout<<endl;
} // end of printStaement( )

void interpretCommand(){ //����ڷκ��� ��ɾ �Է¹޾� ó���ϴ� �Լ�
	while(true){
		string command = "";
		cout<<endl<<">>";
		cin>>command;
		if (command == "quit") break; // quit�� ������ loop�� �ߴ��Ѵ�.
		else if (command == "help") printHelp();
		else if (command == "pline") {
			string lineString = "";
			int line;
			cin >> lineString;
			line = atoi(lineString.c_str());
			if (line == 0)cout << "�߸��� �ٹ�ȣ �Դϴ�." << endl;
			else {
				MyStatement statement;
				if (findStatement(line, statement)) {
					printStatement(statement);
				}
				else {
					cout << "�ش� �� ��ȣ�� ������ ã�� �� �����ϴ�." << endl;
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
					cout << "����" << endl;
			}
			else
				cout << "����" << endl;
		}
		else if (command == "fword"){
			string s;
			cin >> s;
			for (const MyStatement iter:chapter) {
				if (count(iter.wordList.begin(), iter.wordList.end(), s))
					cout << iter.line << "��° �ٿ��� " << count(iter.wordList.begin(), iter.wordList.end(), s) << "�� ���Խ��ϴ�" << endl;
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
			cout<<"�߸��� ��ɾ��Դϴ�. help�� Ȯ���ϼ���."<<endl;
		}
	}
}

void readDocument(string fileName){
	ifstream documentIfs(fileName.c_str());
	string word;
	MyStatement ms;
	while(!documentIfs.eof()){
		documentIfs>>word;
		if(word == "#"){ //������ ���� ���
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

bool findStatement(int line, MyStatement& result){ //line�� �ش��ϴ� ����(MyStatement)�� ��ȯ
	list<MyStatement>::iterator iter;
	for(iter = chapter.begin(); iter != chapter.end(); iter++){
		if(line==(*iter).line) {
			result = (*iter);
			break;
		}
	}
	if(iter != chapter.end())
		return true;	 //ã��
	else
		return false;    //��ã��
}
