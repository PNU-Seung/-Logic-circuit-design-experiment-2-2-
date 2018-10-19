#include <bits/stdc++.h>
#define v vector<int>
#define f for(i=1;i<N;++i)
using namespace std;
ifstream k("rank.inp");
ofstream c("rank.out");
int N,d,j,i;
int main(){
  k>>N;
  vector<v >t(N++);
  f{v e(30,-1);
    for(k>>d,j=28;d!=-1;k>>d) e[j--]=d;
  	sort(e.begin()+j,e.end()-1);
    e[29]=N-i;
    t[i-1]=e;}
  sort(t.begin(),t.end(),greater<v >());
  f c<<N-t[i-1][29]<<endl;
}