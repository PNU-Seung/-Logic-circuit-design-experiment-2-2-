#include <iostream>
#include <deque>
#include <list>
#include <fstream>
#include <string>

using namespace std;

void cut(int begin, int end);
void shuffle(void);

list<int> card;

int main(void) {
	ifstream ifp("card.inp");
	int cardCount, instructionCount; // 카드 수, 작업 개수=1;
	ifp >> cardCount >> instructionCount;

	for (int i = 1; i < cardCount; i++) // card : 1~ 카드수
		card.push_back(i);

	string instruction;
	while (ifp >> instruction) {
		if (instruction == "Shuffle")
			shuffle();
		else if (instruction == "Cut") {
			int from, to;
			ifp >> from >> to;
			cut(from, to);
		}
		else {
			exit(-1); // Shuffle,Cut이 아닌 명령 => error
		}
	}ifp.close();

	ofstream ofp("card.out");
	list<int>::const_iterator iter = card.begin();
	for (int i = 0; i < card.size() / 2; i++)
		iter++;
	ofp << card.front() << " " <<(*iter) <<" "<< card.back() << endl;
	ofp.close();

	return 0;
}