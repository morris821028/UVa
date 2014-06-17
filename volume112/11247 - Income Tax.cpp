#include <stdio.h>
#include <math.h>
int main() {
    long long m, x;
    while(scanf("%lld %lld", &m, &x) == 2 && m) {
        if(x == 100) {
            puts("Not found");
            continue;
        }
        long long ans = ceil((double)m/(1-x/100.0))+5;
        while(ans*(100-x) > (m-1)*100) {
            ans--;
        }
        if(ans <= m-1) puts("Not found");
        else    printf("%lld\n", ans);
    }
    return 0;
}
