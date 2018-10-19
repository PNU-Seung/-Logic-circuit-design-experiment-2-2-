#include <bits/stdc++.h>

using namespace std;

int main(void){
    ifstream input;
    ofstream output;
    bool deadlock[10]={0,};
    stack<int> memstack;
    string buf;
    int i, p=0, q=1, cnt=0;
    int N,k1,k2;
    int x[2]={-1,-1},y[2]={-1,-1};

    input.open("function.inp");
    output.open("function.out");

    input>>N>>k1>>k2;
    vector<vector<int>> flist(N);
    vector<vector<string>> fflist(N);

    for(int i=0; i<N; i++){
        input>>buf;
        while( buf != "$" ){
            fflist[i].push_back(buf);
            flist[i].push_back((buf[0]&64)&&!(buf[0]&32));
            input>>buf;
        }
        flist[i].push_back(-1);
    }

    while(true){
            if(flist[p][q] == 0){
                cnt++;
                if(cnt == k1){
                    x[0] = p;
                    y[0] = q;
                }
                else if(cnt == k2){
                    x[1] = p;
                    y[1] = q;
                }
                q++;
            }
            else if(flist[p][q] == 1){
                memstack.push(100*p+q+1);
                for(i=0; i<N; i++)
                    if(fflist[p][q] == fflist[i][0]){
                        if(deadlock[i] == true){
                            output<<"DEADLOCK\n";
                            return 0;
                        }
                        deadlock[i] = true;
                        p = i;
                        q = 1;
                        break;
                    }
            }
            else{
                if(memstack.empty())
                    break;
                deadlock[p]=false;

                p=memstack.top()/100;;
                q=memstack.top()%100;

                memstack.pop();
            }
    }

    if(x[0] == -1)
        output<<"NONE\n";
    else
        output<<fflist[x[0]][0]<<'-'<<fflist[x[0]][y[0]]<<'\n';
    if(x[1] == -1)
        output<<"NONE\n";
    else
        output<<fflist[x[1]][0]<<'-'<<fflist[x[1]][y[1]]<<'\n';
    output.close();
    input.close();
    return 0;
}