#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <queue>
using namespace std;

int main(void){
ifstream ifp("rumor.inp");
ofstream ofp("rumor.out");
int N, x, d;
ifp >> N >> x >> d;
vector<vector<int>> socialNetwork;
int rumor[N]; //can't build visual studio
fill_n(rumor, N, -1);
int num1, num2;
for(int i=0; i<N; i++){
    vector<int> friendlist;
    num2=0;
    socialNetwork.push_back(friendlist);
    while(ifp >> num1 && num1 != 0){
        if(num2 == 0)
            socialNetwork[i].push_back(-num1);
        else
            socialNetwork[i].push_back(num1);
        sort(socialNetwork[i].begin(), socialNetwork[i].end());
        num2++;
    }
}
sort(socialNetwork.begin(), socialNetwork.end());
reverse(socialNetwork.begin(), socialNetwork.end());
ifp.close();

queue<int> spread;
queue<int> next_spread;
spread.push(x);
rumor[x-1] = 0;
ofp << x << endl;
for(int day= 1; day < d+1; day++){
    while(not(spread.empty())){
		if(socialNetwork[spread.front() - 1].size()>1)
        for(vector<int>::iterator iter = socialNetwork[spread.front()-1].begin()+1; iter != socialNetwork[spread.front()-1].end();iter++){
            next_spread.push(*iter);
			if (rumor[(*iter) - 1] == -1) {
				rumor[(*iter) - 1] = day;
				ofp << (*iter) << endl;
			}
        }
        spread.pop();
    }
    while(not(next_spread.empty())){
        spread.push(next_spread.front());
        next_spread.pop();
    }
}

ofp.close();
return 0;
}
