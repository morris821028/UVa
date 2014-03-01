#include <stdio.h>
#include <math.h>

int main() {
    int t, n;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        if(n <= 0) {
            puts("0");
            continue;
        }
        long long ans = 0;
        int j, k = n, l, r;
        for(j = 1; ;) {
            r = n/j, l = n/(j+1);
            ans += (long long)j*(r-l);
            k -= r-l;
            if(k == 0)  break;
            j = n/k;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
