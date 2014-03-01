#include <stdio.h>
#include <math.h>

int main() {
    int n, m, i;
    while(scanf("%d %d", &n, &m) == 2) {
        if(n == 0 && m == 0)
            break;
        int c = n-m, ans = 1;
        if(c < 0)   c *= -1;
        for(i = 2; i <= (int)sqrt(c); i++) {
            int cnt = 0;
            while(c%i == 0)
                c /= i, cnt++;
            ans *= cnt+1;
        }
        if(c != 1)
            ans *= 2;
        printf("%d\n", ans);
    }
    return 0;
}
