#include <stdio.h>

int main() {
    int n;
    while(scanf("%d", &n) == 1 && n) {
        long long sum = 0, ans = 0, x;
        while(n--) {
            scanf("%lld", &x);
            sum += x;
            if(sum < 0)
                ans -= sum;
            else
                ans += sum;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
