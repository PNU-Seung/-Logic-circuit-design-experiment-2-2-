#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

typedef unsigned int INT;

int main(void)
{
	int N, K;
	INT d, t;

	vector<INT> sg;
	vector<INT> login;
	vector<INT> logout;

	ifstream syslog("syslog.txt");
	if (!syslog.is_open()) {
		cerr << "Syslog Error. " << endl;
		return -1;
	}
	syslog >> N;
	while (syslog >> d) {
		d = (d << 14);
		while (syslog >> t && t != 0)
			sg.push_back(d + t);
	}
	syslog.close();
	ifstream s1("log.inp");
	if (!s1.is_open()) {
		cerr << "Error: inp file missing." << endl;
		return -1;
	}
	s1 >> K;
	for (int i = 0; i<K * 2; ++i) {
		s1 >> d;
		s1 >> t;
		d = (d << 14);
		login.push_back(d + t);
	}
	s1.close();
	ofstream ofs("log.out");
	for (int i = 0; i < K * 2; i = i + 2) {
		int count = 0;
		vector<INT>::iterator lower = lower_bound(sg.begin(), sg.end(), login[i]);
		vector<INT>::iterator upper = upper_bound(sg.begin(), sg.end(), login[i + 1]);
		ptrdiff_t cnt = distance(lower, upper);
		ofs << cnt << endl;
	}
	ofs.close();
	return 0;
}