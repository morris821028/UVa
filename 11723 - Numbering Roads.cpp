#include <stdio.h>

int main() {
    int n, m, test = 0;
    while(scanf("%d %d", &n, &m) == 2) {
        if(n == 0 && m == 0)
            break;
        int ans = (n-m)/m + ((n-m)%m != 0 && n >= m);
        printf("Case %d: ", ++test);
        if(ans > 26)
            puts("impossible");
        else
            printf("%d\n", ans);
    }
    return 0;
}
