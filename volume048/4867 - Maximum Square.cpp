#include <stdio.h>
#include <string.h>
#define min(x, y) ((x) < (y) ? (x) : (y))
inline int ReadInt(int *x) {
    static char c, neg;
    while((c = getchar()) < '-')    {if(c == EOF) return EOF;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = getchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
int main() {
    int n, m;
    int i, j, A[1001], B[1001];
    while(scanf("%d %d", &n, &m) == 2) {
        memset(A, 0, sizeof(A));
        memset(B, 0, sizeof(B));
        if(n == 0 && m == 0)
            break;
        int *ta = A, *tb = B, *tc;
        int ans = 0, x, t;
        for(i = 1; i <= n; i++) {
            for(j = 1; j <= m; j++) {
                ReadInt(&x);
                if(x) {
                    ta[j] = ta[j-1];
                    ta[j] = min(ta[j], tb[j-1]);
                    ta[j] = min(ta[j], tb[j]);
                    ta[j]++;
                    if(ta[j] > ans)
                        ans = ta[j];
                } else
                    ta[j] = 0;
            }
            tc = ta, ta = tb, tb = tc;
        }
        printf("%d\n", ans);
    }
    return 0;
}
