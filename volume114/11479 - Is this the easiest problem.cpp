#include<stdio.h>
#define swap(x,y) {long long t=x; x=y; y=t;}
int main() {
    int T, C = 0;
    scanf("%d", &T);
    while(T--) {
        long long n[3];
        scanf("%lld %lld %lld", &n[0], &n[1], &n[2]);
        if(n[0] > n[2]) swap(n[0], n[2]);
        if(n[1] > n[2]) swap(n[1], n[2]);
        if(n[0] > n[1]) swap(n[0], n[1]);
        printf("Case %d: ",++C);
        if(n[0] + n[1] <= n[2]) puts("Invalid");
        else if(n[0] == n[2] && n[1] == n[2]) puts("Equilateral");
        else if(n[0] == n[1] || n[1] == n[2]) puts("Isosceles");
        else puts("Scalene");
    }
    return 0;
}
