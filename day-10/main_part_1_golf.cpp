#include <iostream>
void a(int &c,int &t,int x){++c;t+=(c-20)%40?0:c*x;}
int main(){char i[5];int v,x=1,c=0,t=0;while(std::cin>>i){a(c,t,x);if(i[0]!='n'){std::cin>>v;a(c,t,x);x+=v;}}std::cout<<t;}
