#include <stdio.h>

int main() {
    int t, n, m;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        int tot = 1<<n;
        int tmp = m, cnt = 0;
        while(tmp)
            cnt += tmp&1, tmp >>= 1;
        tmp = (m == 0) ? (1<<n) : (m&-m);
        printf("%d %d\n", cnt+1, tot-tmp+1);
    }
    return 0;
}
