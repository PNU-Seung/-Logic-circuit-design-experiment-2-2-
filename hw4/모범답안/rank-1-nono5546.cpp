#include<bits/stdc++.h>
using namespace std;
int N, b, j;
int main() {
	fstream i("rank.inp"), o("rank.out", ios::out);
	i >> N;
	vector<vector<int>>V(N, vector<int>(13));
	for (j = 0; j < N; V[j][12] = ++j)
		for (b = 0; b != -1; i >> b, V[j][0]--)V[j][b + 1]++;
	sort(V.begin(), V.end());
	for (j = 0; j < N; j++)o << V[j][12] << '\n';
}