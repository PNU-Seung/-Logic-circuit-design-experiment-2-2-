#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;
struct assignment{int index;vector<int> score;assignment(){}};
bool compare(assignment c1,assignment c2){
if(c1.score.size()<c2.score.size())return 1;
else if(c1.score.size()>c2.score.size())return 0;
else if(c1.score.size()==c2.score.size()){
if(c1.score<c2.score)return 1;
else if(c1.score>c2.score)return 0;
else if(c1.score==c2.score)return(c1.index)>(c2.index);}}
int main(void){int N;ifstream fp("rank.inp");fp>>N;
assignment* c=new assignment[N];int num;
for(int i=0;i<N;i++){c[i].index=i+1;
while(fp>>num&&num!=-1){
c[i].score.push_back(num);}
sort(c[i].score.begin(),c[i].score.end());}fp.close();assignment temp;
for(int i=0;i<N-1;i++)
for(int j=N-2;j>=i;j--){
if(compare(c[j],c[j+1])){
temp=c[j];c[j]=c[j+1];c[j+1]=temp;}}
ofstream ofp("rank.out");
for(int i=0;i<N;i++)ofp<<c[i].index<<endl;
ofp.close();
delete[] c;
return 0;}
