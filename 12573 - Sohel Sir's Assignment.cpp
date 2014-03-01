#include <stdio.h>
#include <math.h>
int main() {
    scanf("%*d");
    long long x, y;
    int i;
    while(scanf("%lld %lld", &x, &y) == 2) {
        long long n = x-(y-2), sq;
        sq = (long long)sqrt(n);
        if(n == 0) {
            printf("%lld\n", x+1);
            continue;
        }
        int flag = 0;
        long long mn;
        for(i = 1; i <= sq; i++) {
            if(n%i == 0) {
                if(x%i+2 == y) {
                    if(!flag)   mn = i, flag = 1;
                    if(i < mn)  mn = i;
                }
                if(x%(n/i)+2 == y) {
                    if(!flag)   mn = n/i, flag = 1;
                    if(n/i < mn)  mn = n/i;
                }
            }
            if(flag && i > mn)  break;
        }
        if(flag)
            printf("%lld\n", mn);
        else
            puts("Impossible");
    }
    return 0;
}
