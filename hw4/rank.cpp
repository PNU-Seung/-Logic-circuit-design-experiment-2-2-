#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;
struct assignment {
	int index;
	vector<int> score;
	assignment() {}
};
bool compare(assignment c1,assignment c2){
	if (c1.score.size() == c2.score.size()) {
		if (c1.score == c2.score)return c1.index > c2.index;
		else return c1.score < c2.score ? 1 : 0;
	}
	else return c1.score.size() < c2.score.size() ? 1 : 0;
}
int main(void){int N;ifstream fp("rank.inp");
int N;
ifstream ip("rank.inp");
ip >> N;
assignment* c = new assignment[N];
int a;
for (int i = 0; i < N; i++) {
	c[i].index = i + 1;
	while (ip >> a && a != -1) { c[i].score.push_back(a); }
	sort(c[i].score.begin(), c[i].score.end());
}
ip.close();
assignment temp;
for (int i = 0; i < N - 1; i++)
	for (int j = N - 2; j >= i; j--) {
		if (compare(c[j], c[j + 1]))
			temp = c[j], c[j] = c[j + 1], c[j + 1] = temp;
	}
ofstream op("rank.out");
for (int i = 0; i < N; i++)op << c[i].index << endl;
op.close();
delete[] c;
return 0;
}