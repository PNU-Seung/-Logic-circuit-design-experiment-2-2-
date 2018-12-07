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
	vector<pair<int, int>> checkNonOverLap(int start, int end, vector<pair<int, int>> overLapData);
}

list<Log> serverLog;
int main(void) {
	std::ifstream ifp("log.inp");
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

void timeSlot::calculator(int id, int start, int end) {
	vector<pair<int, int>> overLapData = checkOverLap(start, end);
	if (overLapData.empty()) {
		timeSlot::addNewslot(id, start, end);
	}
	else {
		for (pair<int, int> data : overLapData) {
			for (list<Log>::iterator iter = serverLog.begin(); iter != serverLog.end(); iter++) {
				if (data.first >= iter->ts && data.first <= iter->te) {
					if (data.first == iter->ts && data.second != iter->te) {
						splice(iter, data.first, data.second);
					}
					else if (data.first != iter->ts && data.second == iter->te) {
						splice(iter, iter->ts, data.first-1);
					}
					else if (data.first != iter->ts && data.second != iter->te) {
						timeSlot::splice(iter, iter->ts, data.first-1);
						timeSlot::splice(iter, data.first, data.second);
					}
					timeSlot::addUser(id, data.first, data.second);
				}
			}
		}
		
		vector<pair<int, int>> overNonLapData = checkNonOverLap(start, end, overLapData);
		for (pair<int, int> iter : overNonLapData) {
			timeSlot::addNewslot(id, iter.first, iter.second);
		}
		
	}

}

void timeSlot::splice(list<Log>::iterator iter, int start, int end)
{
	if (start == iter->ts) { //for bug check
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
	if (serverLog.empty())
		serverLog.push_back(data);
	else {
		for (list<Log>::iterator iter = serverLog.begin(); iter != serverLog.end(); iter++) {
			if (start < iter->ts) {
				serverLog.insert(iter, data);
				break;
			}
			
		}
		if (start > serverLog.back().te)
			serverLog.push_back(data);
	}
}

void timeSlot::addUser(int user, int start, int end)
{
	for (Log& iter : serverLog) {
		if (iter.ts >= start && iter.te <= end) {
			
			iter.user.push_back(user);
			sort(iter.user.begin(), iter.user.end());
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
		num.shrink_to_fit();
		
		overLapStart = std::find(num.begin(), num.end(), iter.ts);
		overLapEnd = std::find(num.begin(), num.end(), iter.te);
		
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
		else if (overLapStart == num.end() && overLapEnd == num.end()) {
			if (iter.ts < start && iter.te > end) {
				overlap.emplace_back(start, end);
				break;
			}
		}
		if (overLapEnd != num.end() && *overLapEnd == end)
			break;
	}

	return overlap;
}
vector<pair<int, int>> timeSlot::checkNonOverLap(int start, int end, vector<pair<int, int>> overLapData) {
	
	vector<pair<int, int>> nonOverLapData;
	
	vector<int> overLap;
	for (const pair<int, int> iter : overLapData) {
		overLap.push_back(iter.first);
		overLap.push_back(iter.second);
	}

	vector<int>::const_iterator iter = overLap.begin();
	for (int i = 0; i < overLap.size() / 2; i++) {
		if(*iter -start >= 1)
			nonOverLapData.emplace_back(start, *iter);
		start = *(++iter)+1;
		if(i != overLap.size()/2 -1 )
			iter++;
	}
	nonOverLapData.emplace_back(start, end);
	return nonOverLapData;
}