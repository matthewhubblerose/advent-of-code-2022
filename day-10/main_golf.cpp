#include<iostream>
char i[5];int v,x=1,c,t,p;void a(){if(!p)puts("");putchar(".#"[x>p-2&x<p+2]);p=++c%40;t+=p==20?c*x:0;}int main(){while(std::cin>>i){a();if(*i&1)std::cin>>v,a(),x+=v;}std::cout<<t;}