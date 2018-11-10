#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <utility>
#include <algorithm>
#include <numeric>

using std::list;
using std::pair;
using std::vector;

struct Log {
	vector<int> user;
	int ts;
	int te;
};

namespace timeSlot {
	void calculator(int user, int start, int end);
	void splice(list<Log>::iterator iter, int start, int end);
	void addNewslot(int user, int start, int end);
	void addUser(int user, int start, int end);
	vector<pair<int,int>> checkOverLap(int start, int end);
}

list<Log> serverLog;
int main(void) {
	std::ifstream ifp("1.inp");
	std::ofstream ofp("log.out");
	int N, K;
	ifp >> N >> K;
	int u, s, e;
	for (int i = 0; i < N; i++) {
		ifp >> u >> s >> e;
		timeSlot::calculator(u, s, e);
	}

	int time;
	while (ifp >> time) {
		static list<Log>::const_iterator iter = serverLog.begin();
		for (; iter != serverLog.end(); iter++) {
			if (time < iter->ts) {
				ofp << 0 << std::endl;
				break;
			}
			else if (time >= iter->ts && time <= iter->te) {
				for (int userID : iter->user)
					ofp << userID << " ";
				ofp << std::endl;
				break;
			}
		}
	}
	ifp.close(), ofp.close();
	return 0;
}

void timeSlot::calculator(int user, int start, int end) {



}

void timeSlot::splice(list<Log>::iterator iter, int start, int end)
{
	if (start > iter->ts) {
		Log data;
		data.user = iter->user;
		data.ts = start;
		data.te = end;

		iter->ts = end+1;

		serverLog.insert(iter, data);
	}
	else if (end < iter->te) {
		Log data;
		data.user = iter->user;
		data.ts = start;
		data.te = end;

		iter->ts = end+1;

		serverLog.insert(iter, data);

	}
}

void timeSlot::addNewslot(int user, int start, int end)
{
	Log data;
	data.user.push_back(user);
	data.ts = start;
	data.te = end;

	for (list<Log>::iterator iter = serverLog.begin(); iter != serverLog.end(); iter++) {
		if (start < iter->ts) {
			serverLog.insert(iter, data);
			break;
		}
	}
}

void timeSlot::addUser(int user, int start, int end)
{
	for (Log iter : serverLog) {
		if (iter.ts == start && iter.te == end) {
			iter.user.push_back(user);
			sort(iter.user.begin(), iter.user.end());
			break;
		}
	}
}

vector<pair<int,int>> timeSlot::checkOverLap(int start, int end)
{
	vector<pair<int, int>> overlap;
	vector<int> num;
	vector<int>::iterator overLapStart, overLapEnd;
	for (const Log iter : serverLog) {
		
		num.resize(end - start + 1);
		std::iota(num.begin(), num.end(), start);
		overLapStart = std::find(num.begin(), num.end(), iter.ts); overLapEnd =std::find(num.begin(), num.end(), iter.te);
		
		if (overLapStart == num.end() && overLapEnd != num.end()){
			overlap.emplace_back(start, iter.te);
			start = iter.te + 1;
		}
		else if (overLapStart != num.end() && overLapEnd == num.end()) {
			overlap.emplace_back(iter.ts, end);
			break;
		}
		else if (overLapStart != num.end() && overLapEnd != num.end()) {
			overlap.emplace_back(iter.ts, iter.te);
			start = iter.te + 1;
		}
	}

	return overlap;
}
