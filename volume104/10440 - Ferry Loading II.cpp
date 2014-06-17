#include <stdio.h>

int main() {
    int s[1440];
    int n, t, m, c;
    int i, j;
    scanf("%d", &c);
    while(c--) {
        scanf("%d %d %d", &n, &t, &m);
        t *= 2;
        int tot = 0, act = 0;
        for(i = 0; i < m; i++)
            scanf("%d", &s[i]);
        for(i = (m + n - 1)%n; i < m; i += n)
            act = tot > s[i] ? tot : s[i], tot = act + t;
        printf("%d %d\n", tot - t/2, (m + n - 1)/n);
    }
    return 0;
}
