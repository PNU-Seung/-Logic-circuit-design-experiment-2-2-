#include <bits/stdc++.h>
using namespace std;

void cut(list<int>& _cards, int begin, int end);
void shuffle(list<int>& _cards);

int main(void) {
	ifstream ifp("card.inp");
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
	advance(iter, (card.size() / 2) - 1);	// floor(N/2)번째를 가르키는 iterator

	ofp << card.front() << " " <<(*iter) <<" "<< card.back() << endl;
	ofp.close();

	return 0;
}

void shuffle(list<int>& _cards) {
	list<int>DeckA, DeckB;
	list<int>::iterator iter = _cards.begin();

	advance(iter, ((_cards.size()+1)/2)-1);	// ceiling(N/2)번째를 가르키는 iterator

	DeckA.splice(DeckA.begin(), _cards, _cards.begin(), ++iter); // Deck A =1~ ceil(N/2)
	DeckB.splice(DeckB.begin(), _cards, _cards.begin(), _cards.end()); // DeckB =ceil(N/2)+1 ~ N

	while (!DeckA.empty() || !DeckB.empty()) {	// DeckA와 DeckB가 비워질때까지 반복
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

	advance(iterBegin, begin - 1);
	advance(iterEnd, end - 1);

	_cards.splice(_cards.end(), _cards, iterBegin, ++iterEnd); //begin부터 end까지 잘라서 뒤로 붙이기.
}
