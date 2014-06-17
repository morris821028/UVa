#include <stdio.h>
#include <math.h>

int main() {
    long long n, tn;
    while(scanf("%lld", &n) == 1 && n) {
        if(n < 0)   tn = -n;
        else        tn = n;
        long long sq = sqrt(tn), i, j, k;
        int ans = 1;
        for(i = -sq; i <= sq; i++) {
            if(i == 0 || i == 1 || i == -1)  continue;
            for(j = 1, k = 1; j < tn && j > -tn; j *= i, k++);
            k--;
            if(j == n) {
                if(k > ans)
                    ans = k;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
