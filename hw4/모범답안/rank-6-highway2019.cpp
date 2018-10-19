#include<bits/stdc++.h>
#define p push_back
#define r(x) x.begin(),x.end()-1
#define v vector<int>
#define s size()
using namespace std;
int i,N,k;
bool c(v x,v y){
v w(r(x));
v z(r(y));
if(x.s^y.s)return x.s>y.s;
if(w==z) return x.back()<y.back();
return x>y;}
main(){
ifstream f("rank.inp");
ofstream o("rank.out");
f>>N;
vector<v> a;
for(i=0;i<N;){
v t;
for(;;){f>>k;
if(k==-1)break;
t.p(k);}
t.p(++i);
sort(r(t));
a.p(t);}
sort(r(a)+1,c);
for(i=0;i<N;)o<<a[i++].back()<<endl;}