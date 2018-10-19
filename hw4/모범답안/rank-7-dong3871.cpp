#include <fstream>
#include <vector>
#include <algorithm>
#define pb push_back
using namespace std;
ifstream i("rank.inp");
ofstream o("rank.out");
int main(void)
{
	int n,v,c=0;
	i >> n;
	vector<vector<int>> r;
	while(c<n) {
		vector<int> g;
		while(i >> v && !(v==-1))
			g.pb(v);
		sort(g.begin(),g.end());
		g.pb(n-c);
		g.insert(g.begin(),g.size()-1);
		r.pb(g);
		c++;
	}
	sort(r.begin(),r.end());
    for(int i=n-1;i>=0;--i)
        o << n-r[i][r[i].size()-1]+1 << endl;
	return 0;
}