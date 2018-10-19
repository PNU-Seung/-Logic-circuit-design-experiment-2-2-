#include <bits/stdc++.h>
using namespace std;
int main(){
    int N,k1,k2,pc=0,F,dead_flag=0;
    ifstream ipf("function.inp");
    ofstream opf("function.out");
    string tmp="";
    string tmp_k1="";
    string tmp_k2="";
    ipf>>N>>k1>>k2;
    vector<vector<string>> func(N);
    stack<int>  IR;
    stack<int> Return;
    for(int i=0;i<N;i++){
        tmp="";
        while(tmp.compare("$")){
            ipf>>tmp;
            func[i].push_back(tmp);
        }
    }
    IR.push(0);
    F=IR.top();
    while(!IR.empty()){
        pc++;
        if(func[F][pc]>="A"&&func[F][pc]<="Z"){
            Return.push(pc);
            for(int i=0;i<N;i++){
                if(!func[i][0].compare(func[F][pc])){
                    F=i;
                    break;
                }
            }
            IR.push(F);
            pc=0;
            if(IR.size()>N){
                dead_flag=1;
                break;
            }
            else
                continue;
        }
        if(!func[F][pc].compare("$")){
            IR.pop();
            if(!IR.empty())
                F=IR.top();
            if(!Return.empty())
                pc=Return.top();
            Return.pop();
            continue;
        }
        k1--;
        k2--;
        if(k1==0){
            tmp_k1=func[F][0]+"-"+func[F][pc];
        }
        if(k2==0){
            tmp_k2=func[F][0]+"-"+func[F][pc];
        }
    }
    if(dead_flag==1)
        opf<<"DEADLOCK";
    else{
        if(k1>0)
            opf<<"NONE"<<'\n';
        else
            opf<<tmp_k1<<'\n';
        if(k2>0)
            opf<<"NONE"<<'\n';
        else
            opf<<tmp_k2<<'\n';
    }
}