#include <stdio.h>

int main() {
    int n, i, j, k, a[30], b[30];
    while(scanf("%d", &n) == 1) {
        for(i = 0; i < n; i++)
            scanf("%d", &a[i]);
        for(i = 0; i < n; i++)
            scanf("%d", &b[i]);
        int ans = 0;
        for(i = 0; i < n; i++) {
            for(j = i; j < n; j++) {
                if(b[i] == a[j]) {
                    break;
                }
            }
            for(k = j; k > i; k--) {
                a[k] = a[k-1];
                ans++;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
