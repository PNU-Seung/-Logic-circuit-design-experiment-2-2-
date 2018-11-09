#include <iostream>
#include <fstream>
#include <list>
#include <vector>

using std::list;

struct Log {
	std::vector<int> user;
	int ts;
	int te;

};

namespace timeSlot {
	void calculator(int user, int start, int end);
	void splice(int start, int end);
	void addNewslot(int user, int start, int end);
	void addUser(int user, int start, int end);
	bool checkOverLap(int start, int end);
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

void timeSlot::splice(int start, int end)
{
}

void timeSlot::addNewslot(int user, int start, int end)
{
}

void timeSlot::addUser(int user, int start, int end)
{
}

bool timeSlot::checkOverLap(int start, int end)
{
	return false;
}
