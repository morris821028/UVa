#include <stdio.h>
int main() {
    int t;
    int i, j, n, x, f0, f1;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        int f[100000] = {};
        int a[50005];
        for(i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            f[a[i]] = 1;
        }
        int ans = 2;
        for(i = 0; i < n; i++) {
            for(j = i+1; j < n; j++) {
                if(n-j+1 <= ans)
                    break;
                f0 = a[i], f1 = a[j];
                int cnt = 2;
                while(1) {
                    x = f0+f1;
                    f0 = f1;
                    f1 = x;
                    if(x > a[n-1] || f[x] == 0)
                        break;
                    cnt++;
                }
                if(cnt > ans)   ans = cnt;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
