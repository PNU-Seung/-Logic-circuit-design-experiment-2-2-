#include <bits/stdc++.h>
#define f for (i=0;i<N;++i)
#define y push_back
#define t py[i]
using namespace std;
main(void){
	int N,p,i,j;
	ifstream z("rank.inp");
	z>>N;
	vector<vector<int> >py(N);
	f{t.y(-2);
	for(j=0;z>>p&&p!=-1;++j)t.y(p);
	t[0]=j,t.y(-i-1);}
	f sort(t.begin()+1,t.end()-1);
	sort(py.begin(),py.end(),greater<vector<int> >());
	ofstream o("rank.out");
	f o<<-t[t[0]+1]<<endl;
}