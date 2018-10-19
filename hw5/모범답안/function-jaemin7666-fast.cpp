#include <iostream>
#include <string>
#include <fstream>
#include <cctype>

using namespace std;

class func {
	string** p;
	size_t count;
	int len;
	int swit;
	string str;
public:
	func(void) : p(0), len(0), count(0), str("0"), swit(0) {}
	func(int len) : p(new string*[len]), len(len), count(0), str("0"), swit(0) {
		for(size_t i=0; i<len; ++i)
			p[i] = new string[32];
		for(int i=0; i<len; ++i)
			for(int k=0; k<32 && p[i][k]!="end"; ++k)
				p[i][k] = "0";
	}
	~func(void) { 
		if(p!=0) {
			for(int i=0; i<len; ++i) 
				delete [] p[i];
			delete [] p;
		}
	}
	void input(istream& is) {
		for(size_t i=0; i<len; ++i) {
			size_t k;
			for(k=0; (is >> p[i][k]) && p[i][k]!="$"; ++k)
				;
			p[i][k] = "end";
		}
	}
	bool deadlock(ofstream& ofs) {
		size_t k;
		for(k=1; k<32 && p[0][k]!="end" && !isupper(*p[0][k].data());++k)
			;
//		cout << p[0][k] << endl;
		if(p[0][k]=="end")
			return false;
		for(size_t i=1; i<len; ++i) {
			str = p[i][0];
//			cout << "destination : " << str << endl;
//			cout << "value : " << test_call_func(str) << endl;
			if(test_call_func(str, ofs)==0)
				return true;
		}
		return false;
	}
	int test_call_func(string s, ofstream& ofs) {
		size_t i;
		for(i=0; i<len && p[i][0]!=s; ++i)
			;
//			cout << "select : " << p[i][0] << endl;
		for(size_t j=1; j<32 && p[i][j]!="end"; ++j) {
			if(swit==1) return 0;
//			cout << "input : " << *p[i][j].data() << endl;
			if(isupper(*p[i][j].data())) {
//				cout << "return : " << p[i][j] << endl;
//				cout << "output : " << *p[i][j].data() << endl;
				if(p[i][j]==str) {
					ofs << "DEADLOCK" << endl;
					swit = 1;
					return 0;
				}
				test_call_func(p[i][j], ofs);
			}
		}
		return 1;
	}
	string call_func(string s, size_t k, ofstream& ofs) {
		size_t i;
		for(i=0; i<len && p[i][0]!=s; ++i)
			;
		for(size_t j=1; j<32 && p[i][j]!="end"; ++j) {
			if(isupper(*p[i][j].data())) {
				call_func(p[i][j], k, ofs);
				continue;
			}
			++count;
			if(count==k)
				ofs << s << "-" << p[i][j] << endl;
//			cout << p[i][j] << " " << count << endl;
		}
		return s;
	}
	string** ptr(void) const {return p;}
	size_t counting(void) const {return count;}
	void clear(void) { count=0; }
};

int print(string** p, int n) {
	for(int i=0; i<n; ++i) {
		for(int k=0; k<32 && p[i][k]!="end"; ++k)
			cout << p[i][k] << ' ';
		cout << endl;
	}
	return 1;
}

int main(void)
{
	int n;
	size_t k1, k2;
	
	ifstream ifs("function.inp");
	
	if(!ifs.is_open()) {
		cout << "input error." << endl;
		return 0;
	}
	
	ifs >> n >> k1 >> k2;
	
	func fc(n);
	
	fc.input(ifs);
	
//	print(fc.ptr(),n);
	
	ifs.close();
	
	ofstream ofs("function.out");
	if(fc.deadlock(ofs)==true)
		return 0;
	
	fc.call_func(fc.ptr()[0][0], k1, ofs);
	if(fc.counting() < k1)
		ofs << "NONE" << endl;
	
	fc.clear();	
	fc.call_func(fc.ptr()[0][0], k2, ofs);
	if(fc.counting() < k2)
		ofs << "NONE" << endl;
	
	ofs.close();
	return 0;
}