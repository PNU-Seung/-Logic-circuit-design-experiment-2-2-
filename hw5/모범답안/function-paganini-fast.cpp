#include <bits/stdc++.h>

using namespace std;

vector<string *> FuncName;
vector<vector<string>> Value;
int N;
int k1,k2;
int cnt=0;
string result[4]={" "," "," "," "};
typedef struct {
    int row;
    int column;
    } Point;
Point Comp(int row,int column) {
    for(int i=0; i<N; i++) {
        if(*FuncName[i]==Value[row][column]) {
            Point temp{i,1};
            return temp;
            }
        }
    }
void Func(stack <Point> &Address) {
    int row=Address.top().row;
    int column=Address.top().column;
    Address.pop();
    string Name=Value[row][0];
    string element;

    while(Value[row][column]!="$") {
        element=Value[row][column];
        if(element>="A"&&element<="Z") {
            Point Continue{row,column+1};
            Address.push(Continue);
            Point NewStart=Comp(row,column);
            Address.push(NewStart);
            return Func(Address);
            }
        cnt++;
        if(cnt==k1) {
            result[0]=Name;
            result[1]=element;
            }
        else if(cnt==k2) {
            result[2]=Name;
            result[3]=element;
            }
        column++;
        }

    if(!Address.empty()) {
        return Func(Address);
        }
    }
void Deadlock(){
    cout<<"DEADLOCK TRUE"<<endl;
    fstream out("function.out",ios::out);
    out<<"DEADLOCK"<<endl;
    out.close();
}


int main() {
    string DEAD;
    string element; //요소들
    fstream inp("function.inp"); //input
    inp>>N>>k1>>k2;
    for(int i=0; i<N; i++) {
        vector<string>row;
        while(1) {
            inp>>element;
            if(element=="$") {
                row.push_back("$");
                break;
                }
            row.push_back(element);
            }
        Value.push_back(row);
        }
    inp.close();

     for(int i=0; i<N; i++) {
        FuncName.push_back(&Value[i][0]);
        }
    /*
    DEADLOCK CHECK
    */
    for(int i=0;i<N;i++){
        DEAD=Value[i][Value[i].size()-2];
        if(DEAD>"A"&&DEAD<"Z"){
            Point check=Comp(i,Value[i].size()-2);
            for(int j=check.column;j<(Value[check.row].size()-1);j++){
                if(Value[check.row][j]>"A"&&Value[check.row][j]<"Z"){
                    Deadlock();
                    return 0;
                    }
            }
            }
        else
            continue;
    }
    stack <Point> Address;
    Point Start{0,1};
    Address.push(Start);
    Func(Address);
    fstream out("function.out",ios::out);
    if(result[0]==" ")
        out<<"NONE"<<endl;
    else{
        out<<result[0]<<'-'<<result[1]<<endl;
        }
    if(result[2]==" "){
        out<<"NONE"<<endl;
    }
    else{out<<result[2]<<'-'<<result[3];}
    out.close();
    return 0;
    }
