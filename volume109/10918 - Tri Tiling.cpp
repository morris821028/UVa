#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
    int F[31]={1, 0}, G[31]={0, 1};
    for(int i = 2; i <= 30; i++){
        F[i] = F[i-2]+2*G[i-1];
        G[i] = F[i-1]+G[i-2];
    }
    int n;
    while(scanf("%d", &n)){
        if(n < 0)
            break;
        printf("%d\n", F[n]);
    }
    return 0;
}
