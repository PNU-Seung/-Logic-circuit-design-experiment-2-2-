#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

class assignment {
	int index;
	int rank;
	vector<int> score;
public:
	assignment() {
		index = -1;
		rank = -1;
	}
	void setAssignment(int num) {
		index = num;
		rank = num+1;
	}
	void inputScore(int _score) {
		score.push_back(_score);
	}
	int getRank(void) const {
		return rank;
	}
	int getindex(void) const {
		return index+1;
	}
	void sortArray(void) {
		sort(score.begin(), score.end());
	}
	friend bool compare(class assignment c1, class assignment c2); // c1< c2 return bool
	friend void swapRank(class assignment& c1, class assignment& c2);
};

int main(void) {

	int N;
	ifstream fp;
	fp.open("rank.inp");
	fp >> N;
	class assignment* c = new assignment[N];
	int num;
	for (int i = 0; i < N; i++) {
		c[i].setAssignment(i);
		do {
			fp >> num;
			if (num == -1)
				break;
			c[i].inputScore(num);
		} while (true);
		c[i].sortArray();
	}
	fp.close();

	class assignment temp;
	for(int i = 0; i < N-1; i++)
		for (int j = N-1-1; j >= 0+i; j--) {
			if (compare(c[j], c[j + 1])) { // c1 < c2
				temp = c[j];
				c[j] = c[j + 1];
				c[j + 1] = temp;
				swapRank(c[j], c[j + 1]);
			}
		}
	ofstream ofp;
	ofp.open("rank.out");
	for (int i = 0; i < N; i++)
		ofp << c[i].getindex() << endl;
	ofp.close();

	delete[] c;
	return 0;
}
bool compare(class assignment c1, class assignment c2) { // c1< c2 return bool;
	if (c1.score.size() < c2.score.size())
		return true;
	else if (c1.score.size() > c2.score.size())
		return false;
	else if (c1.score.size() == c2.score.size()) {
		if (c1.score < c2.score)
			return true;
		else if (c1.score > c2.score)
			return false;
		else if (c1.score == c2.score)
			return (c1.index + 1) > (c2.index + 1);
		else
			exit(-1);
	}
}
void swapRank(class assignment& c1, class assignment& c2) {
	int temp = c1.rank;
	c1.rank = c2.rank;
	c2.rank = temp;
}
