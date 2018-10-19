#include <bits/stdc++.h>
using namespace std;
int main() {
 ifstream ip("rank.inp");
 ofstream op("rank.out");
 int N, sbuf;
 ip >> N;
 tuple<int, vector<int>, int> gl[N];
 vector<int> ibuf;
 for (int i=0; i<N; i++) {
  ip >> sbuf;
  while (sbuf != -1) {
   ibuf.push_back(sbuf);
   ip >> sbuf;
  }
  sort(ibuf.begin(), ibuf.end());
  gl[i] = make_tuple(ibuf.size(), ibuf, N-i);
  ibuf.clear();
 }
 sort(gl, gl+N);
 for (int j=N-1; j>=0; j--) {
  op << N-get<2>(gl[j])+1;
  if (j>0) op << endl;
 }
 ip.close();
 op.close();
 return 0;
}