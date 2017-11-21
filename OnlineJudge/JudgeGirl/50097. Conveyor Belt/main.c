#include<stdio.h>
#include"transmission.h"
#define MAXSIZE 1048576
long long int belt[MAXSIZE];
int main(){
    int N,T;
    scanf("%d%d",&N,&T);
    for(int i=0;i<N;i++)
        scanf("%lld",&belt[i]);
    transmission(belt,N,T);
    for(int i=0;i<N;i++)
        printf("%lld%s",belt[i],i==N-1?"":" ");
    return 0;
}
