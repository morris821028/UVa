#include <stdio.h>
int main() {
    int t, n, m, x, y, z;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        int ans = 0;
        while(m--) {
            scanf("%d", &x);
            z = 1;
            while(x--)
                scanf("%d", &y), z *= y, z %= n;
            ans += z, ans %= n;
        }
        printf("%d\n", ans);
    }
    return 0;
}
