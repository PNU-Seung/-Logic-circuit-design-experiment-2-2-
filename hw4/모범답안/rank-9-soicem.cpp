#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>
using namespace std;
vector<vector<vector<int>>> t(51);
vector<int> m;
ofstream o("rank.out");
ifstream p("rank.inp");
int N,c=0,v,i=0,j=0;
int main(){
	p>>N;
	while (c++<N) {
        v=-2,i=0;
		while(p>>v&&v!=-1){m.push_back(v);i++;}
		m.push_back(-c);
		sort(m.begin(), m.end()-1);t[i].push_back(m);if(i>j) j=i;m.clear();
	}
	while(j){
	    sort(t[j].rbegin(),t[j].rend());
        for(vector<int> x:t[j--]){
            o <<-x[x.size()-1]<<endl;
        }
	}
	return 0;
}
