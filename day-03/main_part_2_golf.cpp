#include <iostream>
using namespace std;
auto b(string s){auto r=0ll;for(char c:s){r|=1ll<<(c>96?c-97:c-39);}return r;}
int main(){int r=0;string x,y,z;while(cin>>x>>y>>z){auto i=b(x)&b(y)&b(z);while(i){i>>=1;r++;}}cout<<r;}