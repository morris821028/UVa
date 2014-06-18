#include <stdio.h>

int main() {
    int n;
    while(scanf("%d", &n) == 1) {
        int deg[90005] = {}, x, y, i;
        for(i = 1; i < n; i++) {
            scanf("%d %d", &x, &y);
            deg[x]++, deg[y]++;
        }
        int ans = 0;
        for(i = 0; i < n; i++) {
            if(deg[i] >= 2)
                ans++;
        }
        printf("%d\n", ans);
    }
    return 0;
}
