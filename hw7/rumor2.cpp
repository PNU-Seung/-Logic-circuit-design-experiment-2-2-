#include <iostream>
#include <queue>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	queue<int> rumorList; //save order and lastly print them.
	ifstream inp("rumor.inp");
	ofstream out("rumor.out");
	int pplNum, stNum, dayNum;
	inp >> pplNum >> stNum >> dayNum;
	vector<vector<int> > ppl(pplNum, vector<int>(0));
	int* check = new int[pplNum];
	for (int i = 0; i < pplNum; i++) {
		int centor, friends;
		inp >> centor >> friends;
		while (friends) {
			ppl[centor - 1].push_back(friends);
			inp >> friends;
		}
		sort(ppl[centor - 1].begin(), ppl[centor - 1].end());
		check[i] = 0;
	}
	int day = 1;
	vector<int> speaker;
	queue<int> listener, listener2;
	int nextspeaker;
	while (day <= dayNum) {
		if (day == 1) {//소문의 시작
			rumorList.push(stNum);
			check[stNum - 1] = 1;
			speaker = ppl[stNum - 1]; //startNum에 있는 놈을 소문의 근원지로 설정
			if (speaker.size() != 0) {//얘가 친구가 있을경우
				for (int i = 0; i < speaker.size(); i++) {//소문의 근원지가 자기 친구들한테 다 소문냈음
					check[speaker[i] - 1] = 1;
					rumorList.push(speaker[i]);
					listener.push(speaker[i]); //소문의 근원지의 친구들이 소문을 퍼트릴 준비를 함
				}
			}
			/*else {//얘가 친구가 없을 경우 그냥 실행시간 조금 줄어드는거밖에 없음
			   out << rumorList.front();
			   //return 0;
			}*/
			day++;//그러다보니 하루가 갔음
		}
		else {
			if (day % 2 == 0) {
				while (!listener.empty()) {
					nextspeaker = listener.front();
					speaker = ppl[nextspeaker - 1];//소문내기 바통받음
					for (int i = 0; i < speaker.size(); i++) {
						if (!check[speaker[i] - 1]) {
							check[speaker[i] - 1] = 1;
							rumorList.push(speaker[i]);
							listener2.push(speaker[i]);
						}
					}
					listener.pop();
				}
				day++;
			}
			else {
				while (!listener2.empty()) {
					nextspeaker = listener2.front();
					speaker = ppl[nextspeaker - 1];//소문내기 바통받음
					for (int i = 0; i < speaker.size(); i++) {
						if (!check[speaker[i] - 1]) {
							check[speaker[i] - 1] = 1;
							rumorList.push(speaker[i]);
							listener.push(speaker[i]);
						}
					}
					listener2.pop();
				}
				day++;
			}
		}
	}
	while (!rumorList.empty()) {
		out << rumorList.front() << endl;
		rumorList.pop();
	}
}