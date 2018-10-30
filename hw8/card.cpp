#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <numeric> // void iota(iter begin, iter end ,start num)

using namespace std;

void cut(list<int>& _cards, int begin, int end);
void shuffle(list<int>& _cards);

int main(void) {
	ifstream ifp("3.inp");
	int cardCount, instructionCount; // 카드 수, 명령 수(사용x);
	ifp >> cardCount >> instructionCount;

	list<int> card(cardCount);
	iota(card.begin(), card.end(), 1); // card : 1~ 카드수까지 할당.

	string instruction;
	while (ifp >> instruction) {
		if (instruction == "Shuffle")
			shuffle(card);
		else if (instruction == "Cut") {
			int from, to;
			ifp >> from >> to;
			cut(card, from, to);
		}
	}ifp.close();

	ofstream ofp("card.out");
	list<int>::const_iterator iter = card.begin();

	for (int i = 1; i < card.size() / 2; i++)
		iter++;

	ofp << card.front() << " " <<(*iter) <<" "<< card.back() << endl;
	ofp.close();

	return 0;
}

void shuffle(list<int>& _cards) {
	list<int>DeckA, DeckB;

	list<int>::iterator iter = _cards.begin();
	for (int i = 1; i < (_cards.size()+1)/2; i++)
		iter++;

	DeckA.splice(DeckA.begin(), _cards, _cards.begin(), ++iter); // 1~ ceil(N/2)
	DeckB.splice(DeckB.begin(), _cards, _cards.begin(), _cards.end()); // ceil(N/2)+1 ~ N

	while (!DeckA.empty() || !DeckB.empty()) {
		if (!DeckA.empty()) {
			_cards.push_back(DeckA.front());
			DeckA.pop_front();
		}
		if (!DeckB.empty()) {
			_cards.push_back(DeckB.front());
			DeckB.pop_front();
		}
	}
}
void cut(list<int>& _cards, int begin, int end) {
	list<int>::iterator iterBegin = _cards.begin();
	list<int>::iterator iterEnd = _cards.begin();
	for (int i = 1; i < begin; i++)
		iterBegin++;
	for (int i = 1; i < end; i++)
		iterEnd++;

	_cards.splice(_cards.end(), _cards, iterBegin, ++iterEnd);
}